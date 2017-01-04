#include "hal.h"
#include "gps.h"
#include "exti.h"
#include "helpers.h"

static THD_FUNCTION(gpsThread, arg)
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
            PRINT("[GPS] PPS event\n\r");
        }
    }

    chThdExit(MSG_OK);
}

void startGpsThread(void)
{
    chEvtObjectInit(&gpsPPSEvent);
    extChannelEnable(&EXTD1, GPIOA_PA8_GPS1PPS);
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(128), "GPS", NORMALPRIO+1, gpsThread, NULL);
}
