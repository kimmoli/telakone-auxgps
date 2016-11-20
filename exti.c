#include "hal.h"
#include "exti.h"

static void inputExtIrqHandler(EXTDriver *extp, expchannel_t channel);

event_source_t inputEvent;

static const EXTConfig extcfg =
{
  {
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};

void inputExtIrqHandler(EXTDriver *extp, expchannel_t channel)
{
    extChannelDisable(extp, channel);
    chSysLockFromISR();

    chEvtBroadcastFlags(&inputEvent, channel);

    chSysUnlockFromISR();
    extChannelEnable(extp, channel);
}

void extiTKInit(void)
{
    chEvtObjectInit(&inputEvent);

    extStart(&EXTD1, &extcfg);

    extChannelEnable(&EXTD1, GPIOC_PC0_IN1);
    extChannelEnable(&EXTD1, GPIOC_PC1_IN2);
    extChannelEnable(&EXTD1, GPIOC_PC2_IN3);
    extChannelEnable(&EXTD1, GPIOC_PC3_IN4);
}
