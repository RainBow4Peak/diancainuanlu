#include "time.h"
#include "led.h"
#include "key.h"
#include "wifi.h"
#include "usart.h"
 #include <stdlib.h>
u8 Time_flag;
u8 Data[200];//接收数据
u16 User_id=0;//用户ID
u16 Data_len=0;//数据长度
u8 Data_ok =0;//数据准备好
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
	u32 index;
	u8 len;
	u8 i = 0;
	u8 b =0;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
		Time_flag=1;
		if (beep_flag==1)
		{
		  beep_num++;
			if(beep_num>=20)
			{
				beep_num=0;
				beep_flag=0;
		FMQ=0;
			}
		}
		if (Send_Again == 0)
		{Wifi_TimuOut_Num++;}
		if(Wifi_TimuOut_Num>=500)
		{Send_Again=1;
		Wifi_TimuOut_Num=0;}
		Send_Num++;
		if(Data_ok == 0)//如果处理完了数据包
		{
			User_id = 0;
			Data_len = 0;
		}
		//处理回复包
		if(Please_Deal == 1)
		{

			  index = strstr(Data,",");
			  len = index - (u32)&Data;
			  while(len > 0)
				{
					User_id = (Data[len - 1]-0x30) + 10 * i;
					len -= 1;
					i +=1;
				}
				index = strstr(Data,":");
			  len = BUF - (index - (u32)&Data) - 1;
				memcpy(Data,index+1,len);
				while(Data[i] != '\0')
				{
						i++;
				}
				Data_len = i;
			  Please_Deal = 0;
				Data_ok = 1;
				
				
				
		}
	}

	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	
}



