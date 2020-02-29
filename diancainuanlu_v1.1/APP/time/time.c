#include "time.h"
#include "led.h"
#include "key.h"

u8 Time_flag,Tempreture_Num,Fan_Glitter_Num,Led_Glitter_Num;
u16 FMQ_Num, Flash_Num;
/*******************************************************************************
* �� �� ��         : TIM4_Init
* ��������		   : TIM4��ʼ������
* ��    ��         : per:��װ��ֵ
					 psc:��Ƶϵ��
* ��    ��         : ��
*******************************************************************************/
void TIM4_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //������ʱ���ж�
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//��ʱ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��	
}

/*******************************************************************************
* �� �� ��         : TIM4_IRQHandler
* ��������		   : TIM4�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void TIM4_IRQHandler(void)
{
		
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
		Time_flag=1;
		Tempreture_Num++;
		Fan_Glitter_Num++;
		
		Led_Glitter_Num++;
		if ((key_1==1) || (key_2==1)|| (key_3==1)|| (key_4==1)|| (key_5==1))
		{
		  FMQ_Num++;
		
		}
		
			Flash_Num++;
	
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	
}



void Time_Work_Mode(void)
{
			Time1_Start_Hour=((Time1_Start_Hour1<<4)|Time1_Start_Hour2);
			Time1_Start_Min=((Time1_Start_Min1<<4)|Time1_Start_Min2);
			Time1_Stop_Hour=((Time1_Stop_Hour1<<4)|Time1_Stop_Hour2);
			Time1_Stop_Min=((Time1_Stop_Min1<<4)|Time1_Stop_Min2);		
      Work=0;
if(Hour>Time1_Start_Hour)
{ 	
Work=1;
}
if(Hour==Time1_Start_Hour)
{ 
if(Minute>=Time1_Start_Min)	
{ 
Work=1;
}
}
if(Hour>Time1_Stop_Hour)
{ 	
Work=0;
}
if(Hour==Time1_Stop_Hour)
{ 
if(Minute>=Time1_Stop_Min)	
{ 
Work=0;
}
}

if(Time1_Stop_Hour<Time1_Start_Hour)
{
Work=1;
if(Hour>Time1_Stop_Hour)
{ 	
Work=0;
}
if(Hour==Time1_Stop_Hour)
{ 
if(Minute>=Time1_Stop_Min)	
{ 
Work=0;
}
}
if(Hour>Time1_Start_Hour)
{ 	
Work=1;
}
if(Hour==Time1_Start_Hour)
{ 
if(Minute>=Time1_Start_Min)	
{ 
Work=1;
}
}
}

if(Time1_Stop_Hour==Time1_Start_Hour)
{
if(Time1_Stop_Min<Time1_Start_Min)
{
Work=1;
if(Hour>Time1_Stop_Hour)
{ 	
Work=0;
}
if(Hour==Time1_Stop_Hour)
{ 
if(Minute>=Time1_Stop_Min)	
{ 
Work=0;
}
}
if(Hour>Time1_Start_Hour)
{ 	
Work=1;
}
if(Hour==Time1_Start_Hour)
{ 
if(Minute>=Time1_Start_Min)	
{ 
Work=1;
}
}
}
}
//if((Time1_Stop_Hour<=Time1_Start_Hour)&&(Time1_Stop_Min<Time1_Start_Min))
//{ 	
//Work=1;
//if((Hour>=Time1_Stop_Hour)&&(Minute>=Time1_Stop_Min))
//{ 
//Work=0;
//}	
//}
if((Time1_Stop_Hour==Time1_Start_Hour)&&(Time1_Stop_Min==Time1_Start_Min))
{ 	
Work=1;
}
if(Time_mode==1)
{ 	
Work=1;
}
}
