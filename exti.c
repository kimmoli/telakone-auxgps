#include "hal.h"
#include "exti.h"
#include "gps.h"

static void inputExtIrqHandler(EXTDriver *extp, expchannel_t channel);
static void gpsPPSIrqHandler(EXTDriver *extp, expchannel_t channel);

event_source_t inputEvent;

static const EXTConfig extcfg =
{
  {
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},  // Px0
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},  // Px1
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},  // Px2
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, inputExtIrqHandler},  // Px3
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px4
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px5
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px6
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px7
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, gpsPPSIrqHandler},   // Px8
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px9
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px10
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px11
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px12
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px13
    {EXT_CH_MODE_DISABLED, NULL},                                                           // Px14
    {EXT_CH_MODE_DISABLED, NULL}                                                            // Px15
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

void gpsPPSIrqHandler(EXTDriver *extp, expchannel_t channel)
{
    extChannelDisable(extp, channel);
    chSysLockFromISR();

    chEvtBroadcastFlags(&gpsEvent, 1);

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
