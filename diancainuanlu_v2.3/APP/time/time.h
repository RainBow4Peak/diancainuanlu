#ifndef _time_H
#define _time_H
#define BUF  200

#include "system.h"

extern u8 Time_flag;

extern void TIM4_Init(u16 per,u16 psc);
extern void Time_Work_Mode(void);
extern u8 Data[BUF];//��������
extern u16 User_id;//�û�ID
extern u16 Data_len;//���ݳ���
extern u8 Data_ok;//�����Ƿ�׼����
#endif
