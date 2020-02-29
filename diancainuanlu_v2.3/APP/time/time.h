#ifndef _time_H
#define _time_H
#define BUF  200

#include "system.h"

extern u8 Time_flag;

extern void TIM4_Init(u16 per,u16 psc);
extern void Time_Work_Mode(void);
extern u8 Data[BUF];//接收数据
extern u16 User_id;//用户ID
extern u16 Data_len;//数据长度
extern u8 Data_ok;//数据是否准备好
#endif
