#ifndef TK_EXTI_H
#define TK_EXTI_H

extern event_source_t inputEvent;

typedef struct
{
    bool inputState;
    int inputCount;
} InputValues_t;

extern InputValues_t *inputvalues[4];

void extiTKInit(void);

#endif
