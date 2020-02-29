#ifndef _key_H
#define _key_H


#include "system.h"
 
#define KEY_LEFT_Pin    GPIO_Pin_4    //定义K_LEFT管脚
#define KEY_DOWN_Pin    GPIO_Pin_5    //定义K_DOWN管脚
#define KEY_RIGHT_Pin   GPIO_Pin_6   //定义K_RIGHT管脚
#define KEY_UP_Pin      GPIO_Pin_7  //定义KEY_UP管脚
#define KEY_Midd_Pin    GPIO_Pin_3  //定义KEY_UP管脚

//#define KEY_Port (GPIOE) //定义端口
#define KEY_UP_Port (GPIOA) //定义端口


//使用位操作定义
#define K_UP PAin(7)
#define K_DOWN PAin(5)
#define K_LEFT PAin(4)
#define K_RIGHT PAin(6)
#define K_Midd PAin(3)

//使用读取管脚状态库函数定义 
//#define K_UP      GPIO_ReadInputDataBit(KEY_UP_Port,KEY_UP_Pin)
//#define K_DOWN    GPIO_ReadInputDataBit(KEY_Port,KEY_DOWN_Pin)
//#define K_LEFT    GPIO_ReadInputDataBit(KEY_Port,KEY_LEFT_Pin)
//#define K_RIGHT   GPIO_ReadInputDataBit(KEY_Port,KEY_RIGHT_Pin)


//定义各个按键值  
#define KEY_UP 5
#define KEY_DOWN 3
#define KEY_LEFT 2
#define KEY_RIGHT 4  
#define KEY_Midd 1


extern void KEY_Init(void);
extern void Key1_Init(void);
extern void Key_Beep(void);
extern void Fan_Flahs(void);
extern void Key1_Control(void);
extern void Key2_Control(void);
extern void Hot_Warm(void);
extern void All_Day_Warm(void);
extern void All_Day_Cold(void);
extern void All_Day_Time(void);
extern int Judgment_Time(unsigned char a1,unsigned char a2,unsigned char b1,unsigned char b2);
extern void Work_Time1(void);
extern void Work_Time2(void);
extern void Work_Time3(void);
extern void Set_Timing_Time(void);
extern void Set_Temp(void);
extern void Set_System_Time(void);
extern void Set_Time1(void);
extern void Set_Time2(void);
extern void Set_Time3(void);
extern u8 Time_Mode,Work_Time_Flag;

extern u8 key_1,key_2,key_3,key_4,key_5;
extern u8 AT,ST,DT;
extern u8 Delay_count1, Delay_count2;
extern u8 FMQ_flag;
extern u8 Work;
extern u8 k;
extern u8 p;
extern u8 key2_flag1,key2_flag2,key2_flag3;
extern u8 keymode,Time_mode;
extern u8 Disp_Model_Flag,Keymode_Exit;
extern u8 Real_Temprature;
#endif
