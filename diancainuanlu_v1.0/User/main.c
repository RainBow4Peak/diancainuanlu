/*******************************************************************************
*                 
*                 		       ���пƼ�
--------------------------------------------------------------------------------
* ʵ �� ��		 : ʹ�ÿ⺯������һ��LED
* ʵ��˵��       : 
* ���ӷ�ʽ       : 
* ע    ��		 : LED�����ļ���led.c��
*******************************************************************************/

#include "stm32f10x.h"
#include "led.h"
#include "uart.h"
u8 Disp_Model_Flag;
int main(void)
{   
	RCC_Configuration();
	GPIO_Init1();
  HYM8653_Init();
	DIO=1;
	CLK=1;
	STB=1;
  indate(dissetmode);
	display(0xff);
	
 Disp_Model_Flag=1;
	
	while(1)	
	{
		
		USART_SendData(USART1,0x55aa);//���͵�ǰ�ַ�
	 
		if(Disp_Model_Flag==0)
		{
			HYM8563_Read_time();//����д��ַ������ģʽ
		   LED_Disp(); 
		}
		Key_Control();
		if(Disp_Model_Flag==1)
		{
		  
			LED_Set_Disp();
			//HYM8563_Write_time();  
		}
		
			
			
   //display2(0xCC,0x14);
   //display(0xff);
  }
}
