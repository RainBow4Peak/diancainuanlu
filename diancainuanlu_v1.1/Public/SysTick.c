#include "system.h"
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include  "adc.h"
#include "SysTick.h"
#include "usart.h"
#include "time.h"

static u8  fac_us=0;							//usÑÓÊ±±¶³ËÊý			   
static u16 fac_ms=0;							//msÑÓÊ±±¶³ËÊý


/*******************************************************************************
* º¯ Êý Ãû         : RCC_Configuration
* º¯Êý¹¦ÄÜ		   : ³õÊ¼Ê±ÖÓ» ¯º¯Êý
* Êä    Èë         : ÎÞ
* Êä    ³ö         : ÎÞ
*******************************************************************************/
void RCC_Configuration(void)
{

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB
					| RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD  | RCC_APB2Periph_GPIOE
					| RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG  | RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1, ENABLE);    
				
		RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72M/6=12,ADC×î´óÊ±¼ä²»ÄÜ³¬¹ý14M
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //Ê¹ÄÜDMA´«Êä
  }

//³õÊ¼»¯ÑÓ³Ùº¯Êý
//SYSTICKµÄÊ±ÖÓ¹Ì¶¨ÎªAHBÊ±ÖÓµÄ1/8
//SYSCLK:ÏµÍ³Ê±ÖÓÆµÂÊ
void SysTick_Init(u8 SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;					
	fac_ms=(u16)fac_us*1000;				   
}								    


//ÑÓÊ±nus
//nusÎªÒªÑÓÊ±µÄusÊý.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//Ê±¼ä¼ÓÔØ	  		 
	SysTick->VAL=0x00;        					//Çå¿Õ¼ÆÊýÆ÷
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//¿ªÊ¼µ¹Êý	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//µÈ´ýÊ±¼äµ½´ï   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//¹Ø±Õ¼ÆÊýÆ÷
	SysTick->VAL =0X00;      					 //Çå¿Õ¼ÆÊýÆ÷	 
}

//ÑÓÊ±nms
//×¢ÒânmsµÄ·¶Î§
//SysTick->LOADÎª24Î»¼Ä´æÆ÷,ËùÒÔ,×î´óÑÓÊ±Îª:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLKµ¥Î»ÎªHz,nmsµ¥Î»Îªms
//¶Ô72MÌõ¼þÏÂ,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//Ê±¼ä¼ÓÔØ(SysTick->LOADÎª24bit)
	SysTick->VAL =0x00;							//Çå¿Õ¼ÆÊýÆ÷
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//¿ªÊ¼µ¹Êý  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//µÈ´ýÊ±¼äµ½´ï   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//¹Ø±Õ¼ÆÊýÆ÷
	SysTick->VAL =0X00;       					//Çå¿Õ¼ÆÊýÆ÷	  	    
} 

void Systerm_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é ·Ö2×é
	RCC_Configuration();
	TIM4_Init(20-1,36000-1);
	My_EXTI_Init();
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_Init1();
	USART1_Init(9600);
	ADCx_Init();
		
	KEY_Init();

}
