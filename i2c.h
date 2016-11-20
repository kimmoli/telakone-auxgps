#ifndef TK_I2C_H
#define TK_I2C_H

#define TK_I2C_LM75_ADDR 0x48
#define LM75_TEMPREG 0x00

typedef struct
{
    float extTemp;
    long i2cCount;
} I2cValues_t;

extern binary_semaphore_t i2cReadyReadSem;
extern I2cValues_t *i2cValues;

extern void i2cTKInit(void);
extern void startI2cThread(void);

#endif

