#include "hal.h"
#include "pwm.h"
// #include "hal_community.h"

const PWMConfig pwmcfgOutput =
{
    1000000,                                  /* 1 MHz PWM clock frequency.   */
    500,                                      /* PWM period 500 us, 2kHz */
    NULL,
    {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_DISABLED, NULL},
        {PWM_OUTPUT_DISABLED, NULL},
    },
    0,
    0
};

void pwmSetChannel(int ch, int range, int value)
{
    switch (ch)
    {
        case TK_PWM_OUT1:
            pwmEnableChannelI(&PWMD9, 0,  PWM_FRACTION_TO_WIDTH(&PWMD9, range, value)); break;
        case TK_PWM_OUT2:
            pwmEnableChannelI(&PWMD9, 1,  PWM_FRACTION_TO_WIDTH(&PWMD9, range, value)); break;
        default:
            ;
    }
}

int pwmGetChannel(int ch, int range)
{
    int width = 0;
    int period = 1;

    switch (ch)
    {
        case TK_PWM_OUT1:
            width = PWMD9.tim->CCR[0];
            period = PWMD9.period;
            break;
        case TK_PWM_OUT2:
            width = PWMD9.tim->CCR[1];
            period = PWMD9.period;
            break;
        default:
            ;
    }
    return (range * width) / period;
}

void pwmTKInit(void)
{
    pwmStart(&PWMD9, &pwmcfgOutput);
}

