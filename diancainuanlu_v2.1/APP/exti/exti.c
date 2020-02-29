#include "exti.h"
#include "led.h"
#include "stm32f10x.h"
#include "key.h"
#include "usart.h"
#include "time.h"

BUTTON_STATE buttonState;


/*******************************************************************************
* 函 数 名         : My_EXTI_Init
* 函数功能		   : 外部中断初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);//选择GPIO管脚用作外部中断线路
	//清除中断标志位
	EXTI_ClearITPendingBit(EXTI_Line3);
	EXTI_ClearITPendingBit(EXTI_Line4);
	EXTI_ClearITPendingBit(EXTI_Line5);
	EXTI_ClearITPendingBit(EXTI_Line6);
	EXTI_ClearITPendingBit(EXTI_Line7);
	//设置外部中断体的成员	
	EXTI_InitStructure.EXTI_Line=EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;	
	//NVIC 配置
	//EXTI3 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//EXTI0中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x80;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器	
	//EXTI4 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//EXTI0中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x40;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	//EXTI5 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x20;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
}

/*******************************************************************************
* 函 数 名         : EXTI4_IRQHandler
* 函数功能		   : 外部中断4函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
	{
		delay_ms(10);
			beep_flag=1;
		FMQ=1;
		if(PAin(3)==0)
		{			
			buttonState.keyNum = 5;
			buttonState.clickCount = 1;
		}	
	}
	EXTI_ClearITPendingBit(EXTI_Line3); //清除中断
}
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{
		delay_ms(10);
			beep_flag=1;
		FMQ=1;
		if(PAin(4)==0)
		{		
			buttonState.keyNum = 4;
			buttonState.clickCount = 1;
		}	
	}
	EXTI_ClearITPendingBit(EXTI_Line4); //清除中断
}

/*******************************************************************************
* 函 数 名         : EXTI9_5_IRQHandler
* 函数功能		   : 外部中断5函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
	{		  
		delay_ms(10);
		beep_flag=1;
		FMQ=1;
		if(PAin(7)==0)  
		{	
			buttonState.keyNum = 1;
			buttonState.clickCount = 1;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line7);
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{	
		delay_ms(10);
			beep_flag=1;
		FMQ=1;
		if(PAin(6)==0)
		{
			buttonState.keyNum = 2;
			buttonState.clickCount = 1;
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line6);
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
		delay_ms(10);
			beep_flag=1;
		FMQ=1;
		if(PAin(5)==0)
		{	
			buttonState.keyNum = 3;
			buttonState.clickCount= 1;
		}	
	}
	EXTI_ClearITPendingBit(EXTI_Line5);	
}



