#include "hal.h"
#include "exti.h"
#include "gps.h"

event_source_t inputEvent;
static virtual_timer_t inputDebounce_vt[4];
static void inputDebounce_cb(void *arg);
InputValues_t *inputvalues[4];

static ioline_t inputIOs[4] = { LINE_IN1, LINE_IN2, LINE_IN3, LINE_IN4 };

static void inputHandler(void *arg)
{
    chSysLockFromISR();

    if (!chVTIsArmedI(&inputDebounce_vt[(int)arg]))
    {
        chVTSetI(&inputDebounce_vt[(int)arg], MS2ST(100), inputDebounce_cb, arg);
    }

    chSysUnlockFromISR();
}

void inputDebounce_cb(void *arg)
{
    int ch = (int)arg;

    chSysLockFromISR();

    if (palReadLine(inputIOs[ch]) == PAL_LOW && inputvalues[ch]->inputState == TRUE)
    {
        inputvalues[ch]->inputCount++;
        inputvalues[ch]->inputState = FALSE;
        chEvtBroadcastFlagsI(&inputEvent, ch);
    }
    if (palReadLine(inputIOs[ch]) == PAL_HIGH && inputvalues[ch]->inputState == FALSE)
    {
        inputvalues[ch]->inputState = TRUE;
        chEvtBroadcastFlagsI(&inputEvent, ch);
    }

    chSysUnlockFromISR();
}

static void gpsppsHandler(void *arg)
{
    (void) arg;

    chSysLockFromISR();
    chEvtBroadcastFlagsI(&gpsEvent, 1);
    chSysUnlockFromISR();
}

void extiTKInit(void)
{
    chEvtObjectInit(&inputEvent);

    for (int i=0;i<4;i++)
    {
        inputvalues[i] = chHeapAlloc(NULL, sizeof(InputValues_t));
        inputvalues[i]->inputState = FALSE;
        inputvalues[i]->inputCount = 0;
        chVTObjectInit(&inputDebounce_vt[i]);
        palEnableLineEvent(inputIOs[i], PAL_EVENT_MODE_BOTH_EDGES);
        palSetLineCallback(inputIOs[i], inputHandler, (void *)i);
    }

    palEnableLineEvent(LINE_GPS1PPS, PAL_EVENT_MODE_RISING_EDGE);
    palSetLineCallback(LINE_GPS1PPS, gpsppsHandler, NULL);
}

