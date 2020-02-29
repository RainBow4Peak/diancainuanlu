#ifndef _key_H
#define _key_H


#include "system.h"
 
#define KEY_LEFT_Pin    GPIO_Pin_4    //����K_LEFT�ܽ�
#define KEY_DOWN_Pin    GPIO_Pin_5    //����K_DOWN�ܽ�
#define KEY_RIGHT_Pin   GPIO_Pin_6   //����K_RIGHT�ܽ�
#define KEY_UP_Pin      GPIO_Pin_7  //����KEY_UP�ܽ�
#define KEY_Midd_Pin    GPIO_Pin_3  //����KEY_UP�ܽ�

#define KEY_UP_Port (GPIOA) //����˿�


//ʹ��λ��������
#define K_UP PAin(7)
#define K_DOWN PAin(5)
#define K_LEFT PAin(4)
#define K_RIGHT PAin(6)
#define K_Midd PAin(3)


//�����������ֵ  
#define KEY_UP 5
#define KEY_DOWN 3
#define KEY_LEFT 2
#define KEY_RIGHT 4  
#define KEY_Midd 1


extern void KEY_Init(void);

extern	u8 beep_flag;
extern	u8 beep_num;

#endif
