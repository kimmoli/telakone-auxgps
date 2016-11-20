#include <string.h>
#include "hal.h"
#include "adc.h"
#include "i2c.h"
#include "analog_data.h"

AnalogValueData analogValues[ANALOG_VALUE_COUNT];

static void addValue(AnalogValueData *av, int type, char *token, char *unit, void *value)
{
    av->type = type;
    strcpy(av->token, token);
    strcpy(av->unit, unit);
    av->value = value;
}

static int dataInitialized = 0;

void initAnalogValueData(void)
{
    if (dataInitialized)
        return;

    addValue(&analogValues[0],  ANALOG_VALUE_INT,   "__SL_G_U_A", "",   (void *) &adcValues->adcCount );
    addValue(&analogValues[3],  ANALOG_VALUE_FLOAT, "__SL_G_UVS", " V", (void *) &adcValues->supplyVoltage );
    addValue(&analogValues[7],  ANALOG_VALUE_INT,   "__SL_G_U_I", "",   (void *) &i2cValues->i2cCount );
    addValue(&analogValues[8],  ANALOG_VALUE_FLOAT, "__SL_G_UTE", " C", (void *) &i2cValues->extTemp );

    dataInitialized = 1;
}

