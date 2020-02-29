#ifndef _key_H
#define _key_H


#include "system.h"
 
#define KEY_LEFT_Pin    GPIO_Pin_4    //定义K_LEFT管脚
#define KEY_DOWN_Pin    GPIO_Pin_5    //定义K_DOWN管脚
#define KEY_RIGHT_Pin   GPIO_Pin_6   //定义K_RIGHT管脚
#define KEY_UP_Pin      GPIO_Pin_7  //定义KEY_UP管脚
#define KEY_Midd_Pin    GPIO_Pin_3  //定义KEY_UP管脚

#define KEY_UP_Port (GPIOA) //定义端口


//使用位操作定义
#define K_UP PAin(7)
#define K_DOWN PAin(5)
#define K_LEFT PAin(4)
#define K_RIGHT PAin(6)
#define K_Midd PAin(3)


//定义各个按键值  
#define KEY_UP 5
#define KEY_DOWN 3
#define KEY_LEFT 2
#define KEY_RIGHT 4  
#define KEY_Midd 1


extern void KEY_Init(void);

extern	u8 beep_flag;
extern	u8 beep_num;

#endif
