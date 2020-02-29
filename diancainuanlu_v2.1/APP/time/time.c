#include "time.h"
#include "led.h"
#include "key.h"
#include "wifi.h"
#include "usart.h"
 #include <stdlib.h>
u8 Time_flag;
u8 Data[200];//��������
u16 User_id=0;//�û�ID
u16 Data_len=0;//���ݳ���
u8 Data_ok =0;//����׼����
u16 Send_Flag=0;
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
	u32 index;
	u8 len;
	u8 i = 0;
	u8 b =0;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
		Send_Flag++;
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
		if(Wifi_TimuOut_Num>=200)
		{Send_Again=1;
		Wifi_TimuOut_Num=0;}
		Send_Num++;
		if(Data_ok == 0)//��������������ݰ�
		{
			User_id = 0;
			Data_len = 0;
		}
		//����ظ���
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



