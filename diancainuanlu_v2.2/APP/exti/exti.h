#ifndef _exti_H
#define _exti_H


#include "system.h"

void My_EXTI_Init(void);

typedef struct STRUCT_BUTTON_STATE {
    int keyNum;
    int clickCount;
}BUTTON_STATE;

extern BUTTON_STATE buttonState;

#endif
