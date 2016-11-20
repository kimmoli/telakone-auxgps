#ifndef TK_ADC_H
#define TK_ADC_H

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   1

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      4

extern event_source_t adcConvStart;
extern binary_semaphore_t adcReadyReadSem;

typedef struct
{
    float supplyVoltage;
    long adcCount;
} AdcValues_t;

extern AdcValues_t *adcValues;

void adcTKInit(void);
void adcTKStartConv(void);

#endif // TK_ADC_H
