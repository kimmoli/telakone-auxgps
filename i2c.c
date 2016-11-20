#include "hal.h"
#include "i2c.h"
#include "adc.h"
#include <math.h>
#include "helpers.h"

binary_semaphore_t i2cReadyReadSem;
I2cValues_t *i2cValues;

const I2CConfig i2cconfig =
{
    /* op mode */ OPMODE_I2C,
    /* speed */ 100000,
    /* fast dc */ STD_DUTY_CYCLE
};

static msg_t updateExtTemperature(void);
static bool i2cBusReset(void);

static int i2cEnabled;

static THD_FUNCTION(i2cThread, arg)
{
    (void)arg;

    msg_t ret = MSG_OK;
    event_listener_t elAdc;

    chEvtRegister(&adcConvStart, &elAdc, 9);

    while (!chThdShouldTerminateX())
    {
        chEvtWaitOne(EVENT_MASK(9));

        if (i2cEnabled)
        {
            ret |= updateExtTemperature();
        }

        if (ret == MSG_OK)
            i2cValues->i2cCount++;

        chBSemSignal(&i2cReadyReadSem);
    }

    chThdExit(MSG_OK);
}


msg_t updateExtTemperature(void)
{
    uint8_t rxBuf[2];
    msg_t ret;

    i2cMasterTransmit(&I2CD1, TK_I2C_LM75_ADDR, (uint8_t[]){LM75_TEMPREG}, 1, NULL, 0);
    ret = i2cMasterReceive(&I2CD1, TK_I2C_LM75_ADDR, rxBuf, sizeof(rxBuf));

    if (ret == MSG_OK)
    {
        i2cValues->extTemp = (float)(int16_t)( (rxBuf[0] << 8) | (rxBuf[1] & 0xE0) ) / 256;
    }
    else
    {
        i2cValues->extTemp = (float)0.0;
    }

    return ret;
}

void i2cTKInit(void)
{
    while (!i2cBusReset()) { }

    i2cStart(&I2CD1, &i2cconfig);
    chBSemObjectInit(&i2cReadyReadSem, true);

    i2cValues = chHeapAlloc(NULL, sizeof(I2cValues_t));
    i2cValues->i2cCount = 0;

    i2cEnabled = true;
}

void startI2cThread(void)
{
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(256), "i2c", NORMALPRIO+1, i2cThread, NULL);
}

/*
 * I2C Bus Reset - Analog Devices AN-686 Solution 1.
 */

bool i2cBusReset(void)
{
    int count = 0;
    bool ret = false;

    /* Configure I2C pins to GPIO */
    palSetPadMode(GPIOB, GPIOB_PB6_I2C1SCL, PAL_STM32_MODE_OUTPUT | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(GPIOB, GPIOB_PB7_I2C1SDA, PAL_STM32_MODE_OUTPUT | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST);
    chThdSleepMilliseconds(1);

    /* Try to make signals high */
    palSetPad(GPIOB, GPIOB_PB6_I2C1SCL);
    palSetPad(GPIOB, GPIOB_PB7_I2C1SDA);
    chThdSleepMilliseconds(1);

    /* If SDA is low, clock SCL until SDA is high */
    while (palReadPad(GPIOB, GPIOB_PB7_I2C1SDA) == PAL_LOW && count < 50)
    {
        palClearPad(GPIOB, GPIOB_PB6_I2C1SCL);
        chThdSleepMilliseconds(1);
        palSetPad(GPIOB, GPIOB_PB6_I2C1SCL);
        chThdSleepMilliseconds(1);
        count++;
    }

    /* Generate a stop condition */
    palClearPad(GPIOB, GPIOB_PB6_I2C1SCL);
    chThdSleepMilliseconds(1);
    palClearPad(GPIOB, GPIOB_PB7_I2C1SDA);
    chThdSleepMilliseconds(1);
    palSetPad(GPIOB, GPIOB_PB6_I2C1SCL);
    chThdSleepMilliseconds(1);
    palSetPad(GPIOB, GPIOB_PB7_I2C1SDA);
    chThdSleepMilliseconds(1);

    /* Return true, if SDA is now high */
    ret = (palReadPad(GPIOB, GPIOB_PB7_I2C1SDA) == PAL_HIGH);

    palSetPadMode(GPIOB, GPIOB_PB6_I2C1SCL, PAL_STM32_MODE_ALTERNATE | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_ALTERNATE(4));
    palSetPadMode(GPIOB, GPIOB_PB7_I2C1SDA, PAL_STM32_MODE_ALTERNATE | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_ALTERNATE(4));

    if (count > 0)
        PRINT(" - I2C was stuck, and took %d cycles to reset.\n\r", count);

    chThdSleepMilliseconds(10);

    return ret;
}
