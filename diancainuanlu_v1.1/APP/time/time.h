#ifndef _time_H
#define _time_H

#include "system.h"

extern u8 Time_flag,Tempreture_Num,Fan_Glitter_Num,Led_Glitter_Num;
extern u16 FMQ_Num,Flash_Num;

extern void TIM4_Init(u16 per,u16 psc);
extern void Time_Work_Mode(void);
#endif
