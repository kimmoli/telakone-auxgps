#include <stdlib.h>
#include <string.h>
#include "hal.h"
#include "chprintf.h"
#include "shellcommands.h"
#include "gps.h"

void cmd_gps(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc == 1 && strncmp(argv[0], "show", 2) == 0)
        chEvtBroadcastFlags(&gpsEvent, GPSEVENT_DEBUGON);
    else if (argc == 1 && strncmp(argv[0], "hide", 2) == 0)
        chEvtBroadcastFlags(&gpsEvent, GPSEVENT_DEBUGOFF);
    else if (argc == 1 && strncmp(argv[0], "setrtc", 2) == 0)
        chEvtBroadcastFlags(&gpsEvent, GPSEVENT_SETRTC);
    else
        chprintf(chp, "gps show hide setrtc\n\r");
}

