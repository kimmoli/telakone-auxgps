#include "hal.h"
#include "adc.h"

event_source_t adcConvStart;
binary_semaphore_t adcReadyReadSem;

AdcValues_t *adcValues;

static void adccb1(ADCDriver *adcp, adcsample_t *buffer, size_t n);
static void gptadccb(GPTDriver *gpt_ptr);

const ADCConversionGroup adcgrpcfg1 =
{
    /* Circular */ FALSE,
    /* numbr of channeld */ ADC_GRP1_NUM_CHANNELS,
    /* conversion end callback*/ adccb1,
    /* conversion error callback */ NULL,
    /* ADC CR1 */ 0,
    /* ADC CR2 */ ADC_CR2_SWSTART,
    /* ADC SMPR1 */ 0,
    /* ADC SMPR2 */ ADC_SMPR2_SMP_AN0(ADC_SAMPLE_56),
    /* ADC SQR1 */ ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
    /* ADC SQR2 */ 0,
    /* ADC SQR3 */ ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0)
};

const GPTConfig gptadccfg =
{
    1000,      // timer clock: 1 kHz ~ 1 ms
    gptadccb,  // Timer callback function
    0,
    0
};

static adcsample_t adcSamples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

/*
 * ADC end conversion callback, ADC1
 */
void adccb1(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
    (void) buffer;
    (void) n;
    int i;

    /* Note, only in the ADC_COMPLETE state because the ADC driver fires an intermediate callback when the buffer is half full.*/
    if (adcp->state == ADC_COMPLETE)
    {
        /* Calculates the average values from the ADC samples.*/
        adcsample_t adcAvgSupplyVoltage = 0;

        for (i = 0; i < ADC_GRP1_BUF_DEPTH; i++)
        {
            adcAvgSupplyVoltage += adcSamples1[ i * ADC_GRP1_NUM_CHANNELS];
        }

        adcAvgSupplyVoltage /= ADC_GRP1_BUF_DEPTH;

        adcValues->supplyVoltage = ADC_MEAS12V_SCALE * (float)adcAvgSupplyVoltage;

        adcValues->adcCount++;

        osalSysLockFromISR();
        chBSemSignalI(&adcReadyReadSem);
        osalSysUnlockFromISR();
    }
}

void gptadccb(GPTDriver *gpt_ptr)
{
    (void) gpt_ptr;

    osalSysLockFromISR();
    chEvtBroadcastI(&adcConvStart);
    adcStartConversionI(&ADCD1, &adcgrpcfg1, adcSamples1, ADC_GRP1_BUF_DEPTH);
    osalSysUnlockFromISR();
}

void adcTKInit(void)
{
    adcValues = chHeapAlloc(NULL, sizeof(AdcValues_t));
    adcValues->adcCount = 0;

    chEvtObjectInit(&adcConvStart);
    chBSemObjectInit(&adcReadyReadSem, true);

    adcStart(&ADCD1, NULL);
//    adcSTM32EnableTSVREFE();
}

void adcTKStartConv(void)
{
    gptStart(&GPTD6, &gptadccfg);
    gptStartContinuous(&GPTD6, 100); /* 100 ms */
}

