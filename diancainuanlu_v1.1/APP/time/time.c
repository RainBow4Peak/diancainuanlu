#include "time.h"
#include "led.h"
#include "key.h"

u8 Time_flag,Tempreture_Num,Fan_Glitter_Num,Led_Glitter_Num;
u16 FMQ_Num, Flash_Num;
/*******************************************************************************
* 函 数 名         : TIM4_Init
* 函数功能		   : TIM4初始化函数
* 输    入         : per:重装载值
					 psc:分频系数
* 输    出         : 无
*******************************************************************************/
void TIM4_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //开启定时器中断
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_Cmd(TIM4,ENABLE); //使能定时器	
}

/*******************************************************************************
* 函 数 名         : TIM4_IRQHandler
* 函数功能		   : TIM4中断函数
* 输    入         : 无
* 输    出         : 无
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
