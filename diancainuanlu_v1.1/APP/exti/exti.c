#include "exti.h"
#include "led.h"
#include "stm32f10x.h"
#include "key.h"
#include "usart.h"
#include "time.h"
u8 key_1,key_2,key_3,key_4,key_5;
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
		if(PAin(3)==0)
		{
			key_5=1;
		}	
	}
	EXTI_ClearITPendingBit(EXTI_Line3); //����ж�
}
void EXTI4_IRQHandler(void)
{
 Keymode_Exit=1;
	Flash_Num=0;
	FMQ_Num=0;
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{
		delay_ms(10);
		if(PAin(4)==0)
		{
			key_4=1;
				key4_Num=1;
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
		
	 Flash_Num=0;
	  FMQ_Num=0;
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
	{
		  
	  	key1_Num=(~key1_Num)&0x01;
	  if(key1_Num==0)
		{
		  Keymode_Exit=0;
		
		}
		delay_ms(10);
		if(PAin(7)==0)  //K_UP==0
		{	
		key_1=1;
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line7);
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
		
		delay_ms(10);
		if(PAin(6)==0)
		{
	Keymode_Exit=1;	
		key_2=1;
		key2_Num++;
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line6);
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
		delay_ms(10);
		if(PAin(5)==0)
		{
			Keymode_Exit=1;	
		  key_3=1;
			key3_Num=1;
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line5);	
}



