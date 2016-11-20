#include <stdlib.h>
#include "hal.h"
#include "chprintf.h"
#include "shellcommands.h"
#include "helpers.h"

#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "exti.h"
#include "pwm.h"

void cmd_status(BaseSequentialStream *chp, int argc, char *argv[])
{
    int loopcount = 1;
    int delay = 250;

    if (argc > 0)
        loopcount = strtol(argv[0], NULL, 0);
    if (argc > 1)
        delay = strtol(argv[1], NULL, 0);

    if(loopcount > 1)
        chprintf(chp, "\033[2J\033[H");

    while (loopcount-- > 0)
    {
        /* Seems i2c semaphore is signalled lates, wait for it... */
        if (chBSemWaitTimeout(&i2cReadyReadSem, MS2ST(1000)) == MSG_TIMEOUT)
        {
            chprintf(chp, "Semaphore timeout!\n\r");
            break;
        }

        chprintf(chp, "Conv counters:     %d %d\n\r", adcValues->adcCount,
                                                         i2cValues->i2cCount);
        chprintf(chp, "Ext temp:          %.2f C   \n\r", i2cValues->extTemp);
        chprintf(chp, "Voltage:           %.2f V   \n\r", adcValues->supplyVoltage);
        chprintf(chp, "Inputs:            1 %s 2 %s 3 %s 4 %s    \n\r", (palReadLine(LINE_IN1) ? "hi" : "lo"),
                                                                        (palReadLine(LINE_IN2) ? "hi" : "lo"),
                                                                        (palReadLine(LINE_IN3) ? "hi" : "lo"),
                                                                        (palReadLine(LINE_IN4) ? "hi" : "lo") );
        chprintf(chp, "Outputs:           1 %d%% 2 %d%%    \n\r", pwmGetChannel(TK_PWM_OUT1, 100),
                                                                  pwmGetChannel(TK_PWM_OUT2, 100) );

        if (loopcount > 0)
        {
            chThdSleepMilliseconds(delay);
            chprintf(chp, "\033[H");
        }
    }
}

