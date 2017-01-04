#include "hal.h"
#include "gps.h"
#include "exti.h"
#include "helpers.h"

static SerialConfig gpsReceiveConfig =
{
    /* speed */ 9600,
    /* CR1 */ 0,
    /* CR2 */ 0,
    /* CR3 */ 0
};

static THD_FUNCTION(gpsPPSThread, arg)
{
    (void)arg;
    event_listener_t elGpsPPS;
    eventflags_t flags;

    chEvtRegister(&gpsPPSEvent, &elGpsPPS, 0);

    while (!chThdShouldTerminateX())
    {
        chEvtWaitAny(EVENT_MASK(0));

        flags = chEvtGetAndClearFlags(&elGpsPPS);

        if (flags & 1)
        {
            // PRINT("[GPS] PPS event\n\r");
        }
    }

    chThdExit(MSG_OK);
}

static THD_FUNCTION(gpsReceiveThread, arg)
{
    (void)arg;
    uint8_t rxBuf[NMEA_MAX_SIZE];
    int count = 0;

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
            PRINT((char *)rxBuf);
            // dump((char *)rxBuf, count);
            count = 0;
        }

        chThdSleepMilliseconds(50);
    }

    chThdExit(MSG_OK);
}

void startGpsThread(void)
{
    chEvtObjectInit(&gpsPPSEvent);
    extChannelEnable(&EXTD1, GPIOA_PA8_GPS1PPS);
    sdStart(&SD1, &gpsReceiveConfig);
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(128), "gps pps", NORMALPRIO+1, gpsPPSThread, NULL);
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), "gps nmea", NORMALPRIO+1, gpsReceiveThread, NULL);
}
