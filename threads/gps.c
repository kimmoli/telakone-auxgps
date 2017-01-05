#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "hal.h"
#include "gps.h"
#include "exti.h"
#include "helpers.h"

#define NMEA_ID_RMC         1
#define NMEA_ID_VTG         2
#define NMEA_ID_GGA         3
#define NMEA_ID_GSA         4
#define NMEA_ID_GSV_GPS     5
#define NMEA_ID_GSV_GLONASS 6
#define NMEA_ID_GLL         7
#define NMEA_ID_TXT         8

#define MAX_GSA_SATELLITES  12

struct msg_mapper_t
{
    char     msg_ID[6];
    int32_t  int_ID;
};

static const struct msg_mapper_t msg_map[] =
{
    { "GPRMC", NMEA_ID_RMC },
    { "GNRMC", NMEA_ID_RMC },
    { "GPVTG", NMEA_ID_VTG },
    { "GPGGA", NMEA_ID_GGA },
    { "GPGSA", NMEA_ID_GSA },
    { "GNGSA", NMEA_ID_GSA },
    { "GPGSV", NMEA_ID_GSV_GPS },
    { "GLGSV", NMEA_ID_GSV_GLONASS },
    { "GPGLL", NMEA_ID_GLL },
    { "GNGLL", NMEA_ID_GLL },
    { "GPTXT", NMEA_ID_TXT }
};

struct gsa_data_t
{
    int32_t    mode;                     // 'M' or 'A' (Manual or Automatic)
    int32_t    fix_status;               // 1 - 3 ( 1 = No fix, 2 = 2D fix, 3 =  3D fix )
    int32_t    num_sats;                 // Number of satellites in the next list
    int32_t    sats[MAX_GSA_SATELLITES]; // Satellite IDs in channels 1-12
    float      pdop;                     // Position dilution of precision
    float      hdop;                     // Horizontal dilution of precision
    float      vdop;                     // Vertical dilution of precision
};

static SerialConfig gpsReceiveConfig =
{
    /* speed */ 9600,
    /* CR1 */ 0,
    /* CR2 */ 0,
    /* CR3 */ 0
};

static struct gsa_data_t  gsa_gps;

static void ParseGPSData( const char data[], struct gps_output_params_t *gps_output );
static void ParseRMC ( const char data[], struct gps_output_params_t *gps_output );
static void ParseGSA ( const char data[], struct gsa_data_t *gsa_data );
static void ParseVTG ( const char data[], struct gps_output_params_t *gps_output );

static uint8_t get_pos_mode ( char m );
static void    get_epoch_sec_ms (const char *UTC_time, const char *UTC_date, uint32_t *sec, uint32_t *ms );
static float   get_coordinate( const char **src, size_t degree_field_len );
static void    get_next_field( int32_t index, const char **src, char *dest );

struct gps_output_params_t gps_output;
event_source_t gpsEvent;

static THD_FUNCTION(gpsPPSThread, arg)
{
    (void)arg;
    event_listener_t elGps;
    eventflags_t flags;
    uint32_t prev_secs = 0;
    bool gpsDebug = false;
    bool gpsSetRTC = false;

    chEvtRegister(&gpsEvent, &elGps, 0);

    while (!chThdShouldTerminateX())
    {
        chEvtWaitAny(EVENT_MASK(0));

        flags = chEvtGetAndClearFlags(&elGps);

        if (flags & GPSEVENT_DEBUGON)
        {
            gpsDebug = true;
        }
        if (flags & GPSEVENT_DEBUGOFF)
        {
            gpsDebug = false;
        }
        if (flags & GPSEVENT_SETRTC)
        {
            gpsSetRTC = true;
        }

        if (flags & GPSEVENT_1PPS)
        {
            if ((gpsDebug || gpsSetRTC) && gps_output.UTC_sec != prev_secs)
            {
                struct tm *timp;
                time_t utc_sec;

                utc_sec = gps_output.UTC_sec;
                timp = localtime(&utc_sec);

                if (getenv("tz") != NULL)
                    timp->tm_hour += strtol(getenv("tz"), NULL, 10);

                if (gpsSetRTC)
                {
                    RTCDateTime timespec;
                    rtcConvertStructTmToDateTime(timp, 0, &timespec);
                    rtcSetTime(&RTCD1, &timespec);

                    gpsSetRTC = false;
                }

                if (gpsDebug)
                {
                    PRINT("GPS Fix=%d, Lat=%.6f Lon=%.6f Speed=%.1f Time=%s\r",
                          gps_output.fix_status,
                          gps_output.latitude,
                          gps_output.longitude,
                          gps_output.speed,
                          asctime(timp));
                }

                prev_secs = gps_output.UTC_sec;
            }
        }
    }

    chThdExit(MSG_OK);
}

static THD_FUNCTION(gpsReceiveThread, arg)
{
    (void)arg;
    uint8_t rxBuf[NMEA_MAX_SIZE];
    int count = 0;
    memset( &gps_output, 0, sizeof ( gps_output ) );

    while (!chThdShouldTerminateX())
    {
        msg_t charbuf;
        do
        {
            charbuf = chnGetTimeout(&SD1, MS2ST(100));

            if (charbuf != Q_TIMEOUT)
            {
                rxBuf[count++] = charbuf;

                if (count >= NMEA_MAX_SIZE)
                {
                    DEBUG("Overflow\n\r");
                    count = 0;
                }
            }
        }
        while (charbuf != Q_TIMEOUT && charbuf != 0x0a);

        if (count > 0)
        {
            rxBuf[count] = '\0';
            ParseGPSData((char *)rxBuf, &gps_output);
            count = 0;
        }

        chThdSleepMilliseconds(50);
    }

    chThdExit(MSG_OK);
}

void startGpsThread(void)
{
    chEvtObjectInit(&gpsEvent);
    extChannelEnable(&EXTD1, GPIOA_PA8_GPS1PPS);
    sdStart(&SD1, &gpsReceiveConfig);
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), "gps pps", NORMALPRIO+1, gpsPPSThread, NULL);
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), "gps nmea", NORMALPRIO+1, gpsReceiveThread, NULL);
}

/* GPS Parsing functions */

static void ParseGPSData( const char data[], struct gps_output_params_t *gps_output )
{
    int32_t  msg_tag = 0;
    uint32_t i;

    // Identify message
    for ( i = 0u; i < ( sizeof(msg_map)/sizeof(struct msg_mapper_t) ); i++ )
    {
        // Skip '$' in comparison
        if ( strncmp( &data[1], msg_map[i].msg_ID, 5u ) == 0 )
        {
            msg_tag = msg_map[i].int_ID;
            break;
        }
    }

    // When calling sub-parser, advance data[] to start of the Data Fields
    switch ( msg_tag )
    {
    case NMEA_ID_RMC:
        ParseRMC ( &data[7], gps_output );
        break;

    case NMEA_ID_VTG:
        ParseVTG ( &data[7], gps_output );
        break;

    case NMEA_ID_GSA:
        ParseGSA ( &data[7], &gsa_gps );
        gps_output->pdop = gsa_gps.pdop;
        gps_output->fix_status = gsa_gps.fix_status;
        gps_output->num_sats_used = gsa_gps.num_sats;
        break;

    default:
        break;
    }
}

static void ParseRMC ( const char data[], struct gps_output_params_t *gps_output )
{
    char UTC_time[15];
    char UTC_date[10];
    const char *ptr = data;

    memset( UTC_time, 0, sizeof(UTC_time) );
    memset( UTC_date, 0, sizeof(UTC_date) );

    // Take first field
    get_next_field( 1, &ptr, UTC_time );

    if ( *ptr == 'A' )
    {
        // Data is valid
        get_next_field( 2, &ptr, NULL );
        gps_output->latitude = get_coordinate ( &ptr, 2u );
        if ( *ptr == 'S' )
        {
            // Change to negative for south latitude
            gps_output->latitude = -gps_output->latitude;
        }
        get_next_field( 2, &ptr, NULL );
        gps_output->longitude = get_coordinate ( &ptr, 3u );
        if ( *ptr == 'W' )
        {
            // Change to negative for west longitude
            gps_output->longitude = -gps_output->longitude;
        }
        // Get date (fourth field from current position)
        get_next_field( 4, &ptr, UTC_date );
    }
    else
    {
        // Just take date (eighth field from current position)
        get_next_field( 8, &ptr, UTC_date );
    }

    get_epoch_sec_ms ( UTC_time, UTC_date, &gps_output->UTC_sec, &gps_output->UTC_ms );

    // Get positioning mode (third field from current position)
    get_next_field( 3, &ptr, NULL );
    gps_output->pos_mode = get_pos_mode ( *ptr );
}

static void ParseGSA ( const char data[], struct gsa_data_t *gsa_data )
{
    const char *ptr = data;
    int32_t i = 0;

    gsa_data->mode = ( int32_t )( *ptr );
    ptr = ptr + 2;
    gsa_data->fix_status = ( int32_t )( *ptr - '0' );

    // Take the rest of the data if fix status is ok ('2' or '3')
    if ( ( gsa_data->fix_status == 2 ) || ( gsa_data->fix_status == 3 ) )
    {
        gsa_data->num_sats = 0;
        ptr = ptr + 2;
        while ( i < MAX_GSA_SATELLITES )
        {
            if ( *ptr != ',' )
            {
                gsa_data->sats[i] = ( int32_t )strtol( ptr, NULL, 10 );
                gsa_data->num_sats++;
            }
            else
            {
                gsa_data->sats[i] = 0;
            }
            get_next_field( 2, &ptr, NULL );
            i++;
        }
        gsa_data->pdop = strtof( ptr, NULL );
        get_next_field( 2, &ptr, NULL );
        gsa_data->hdop = strtof( ptr, NULL );
        get_next_field( 2, &ptr, NULL );
        gsa_data->vdop = strtof( ptr, NULL );
    }
}

static void ParseVTG ( const char data[], struct gps_output_params_t *gps_output )
{
    const char *ptr = data;

    // Get speed km/h mode (seventh field from current position)
    get_next_field( 7, &ptr, NULL );
    gps_output->speed = ( float )strtof( ptr, NULL );
}

static uint8_t get_pos_mode ( char m )
{
    uint8_t retval = 0u;

    if ( m == 'A' )
    {
        retval = 1u;
    }
    if ( m == 'D' )
    {
        retval = 2u;
    }

    return (retval);
}

static void get_epoch_sec_ms ( const char *UTC_time, const char *UTC_date, uint32_t *sec, uint32_t *ms )
{
    // Date in format 'ddmmyy'
    // Time in format 'hhmmss.sss'
    struct tm time_struct; /*lint !e960 Allow re-use of "C-90 reserved identifier 'tm'" */
    int32_t retval;
    int32_t msecs;

    retval = sscanf ( UTC_date, "%02d%02d%02d", &time_struct.tm_mday, &time_struct.tm_mon, &time_struct.tm_year );
    retval += sscanf ( UTC_time, "%02d%02d%02d.%03ld", &time_struct.tm_hour, &time_struct.tm_min, &time_struct.tm_sec, &msecs );

    if ( retval == 7 )
    {
        time_struct.tm_mon--;
        time_struct.tm_year = time_struct.tm_year + 100;
        /* NOTE: timegm should not be used because of portability */
        *sec = ( uint32_t )mktime ( &time_struct );
        *ms = ( uint32_t )msecs;
    }
}

static float get_coordinate( const char **src, size_t degree_field_len )
{
    // Latitude in format ‘ddmm.mmmm’ (degrees and minutes) : degree_field_len = 2
    // Longitude in format ‘dddmm.mmmm’ (degrees and minutes) : degree_field_len = 3

    float retval;
    float temp;
    char degrees[10];
    char minutes[15];
    const char *lp = *src;
    const char *ptr;
    uint32_t i;

    memset ( degrees, 0, sizeof(degrees) );
    memset ( minutes, 0, sizeof(minutes) );

    // Copy degrees part according to given field length
    strncpy( degrees, lp, degree_field_len );
    // Minutes part: copy until ',' encountered (amount of decimals may vary).
    ptr = &lp[degree_field_len];
    i = 0u;
    while ( *ptr != ',' )
    {
        minutes[i] = *ptr;
        ptr++;
        i++;
    }

    temp = strtof( minutes, NULL );
    temp = ( float ) ( temp / 60.0 );
    retval = strtof( degrees, NULL );
    retval = retval + temp;

    // Advance to next field
    *src = *src + (degree_field_len + i + 1u);

    return ( retval );
}

static void get_next_field( int32_t index, const char **src, char *dest )
{
    int32_t i;
    const char *lp = *src;
    int32_t end_of_sentence = 0;

    // Scan to requested field (1 means the currently pointed)
    for ( i = 0; i < (index-1); i++ )
    {
        while ( ( *lp != ',' ) && ( *lp != '*' ) )
        {
            lp++;
        }
        if ( *lp == '*' )
        {
            // End of the sentence
            end_of_sentence = 1;
            break;
        }
        else
        {
            lp++;
        }
    }

    if ( ( end_of_sentence == 0 ) && ( dest != NULL ) )
    {
        while ( ( *lp != ',' ) && ( *lp != '*' ) )
        {
            *dest = *lp;
            dest++;
            lp++;
        }
        lp++;
    }

    *src = lp;
}
