#include "exti.h"
#include "led.h"
#include "stm32f10x.h"
#include "key.h"
#include "usart.h"
#include "time.h"

BUTTON_STATE buttonState;


/*******************************************************************************
* �� �� ��         : My_EXTI_Init
* ��������		   : �ⲿ�жϳ�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//����ѡ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);//ѡ��GPIO�ܽ������ⲿ�ж���·
	//����жϱ�־λ
	EXTI_ClearITPendingBit(EXTI_Line3);
	EXTI_ClearITPendingBit(EXTI_Line4);
	EXTI_ClearITPendingBit(EXTI_Line5);
	EXTI_ClearITPendingBit(EXTI_Line6);
	EXTI_ClearITPendingBit(EXTI_Line7);
	//�����ⲿ�ж���ĳ�Ա	
	EXTI_InitStructure.EXTI_Line=EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;	
	//NVIC ����
	//EXTI3 NVIC ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//EXTI0�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x80;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���	
	//EXTI4 NVIC ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//EXTI0�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x40;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	//EXTI5 NVIC ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x20;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
}

/*******************************************************************************
* �� �� ��         : EXTI4_IRQHandler
* ��������		   : �ⲿ�ж�4����
* ��    ��         : ��
* ��    ��         : ��
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
	EXTI_ClearITPendingBit(EXTI_Line3); //����ж�
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
	EXTI_ClearITPendingBit(EXTI_Line4); //����ж�
}

/*******************************************************************************
* �� �� ��         : EXTI9_5_IRQHandler
* ��������		   : �ⲿ�ж�5����
* ��    ��         : ��
* ��    ��         : ��
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



