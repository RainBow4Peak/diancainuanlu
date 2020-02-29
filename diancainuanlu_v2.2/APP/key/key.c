#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "time.h"

#define Temp_Diff1 5
#define Temp_Diff2 10
#define Temp_Diff3 15

u8 beep_flag,beep_num;


/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : 按键初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStructure.GPIO_Pin=KEY_UP_Pin|KEY_DOWN_Pin|KEY_LEFT_Pin|KEY_RIGHT_Pin|KEY_Midd_Pin;	   //选择你要设置的IO口
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//下拉输入
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //设置传输速率
    GPIO_Init(KEY_UP_Port,&GPIO_InitStructure);		  /* 初始化GPIO */

}



