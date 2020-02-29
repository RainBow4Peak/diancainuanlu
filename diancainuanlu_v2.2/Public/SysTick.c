#include "system.h"
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include  "adc.h"
#include "SysTick.h"
#include "usart.h"
#include "time.h"

static u8  fac_us=0;							//usÑÓÊ±±¶³ËÊı
static u16 fac_ms=0;							//msÑÓÊ±±¶³ËÊı


/*******************************************************************************
* º¯ Êı Ãû         : RCC_Configuration
* º¯Êı¹¦ÄÜ		   : ³õÊ¼Ê±ÖÓ» ¯º¯Êı
* Êä    Èë         : ÎŞ
* Êä    ³ö         : ÎŞ
*******************************************************************************/
void RCC_Configuration(void)
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB
                           | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD  | RCC_APB2Periph_GPIOE
                           | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG  | RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72M/6=12,ADC×î´óÊ±¼ä²»ÄÜ³¬¹ı14M
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //Ê¹ÄÜDMA´«Êä
}

//³õÊ¼»¯ÑÓ³Ùº¯Êı
//SYSTICKµÄÊ±ÖÓ¹Ì¶¨ÎªAHBÊ±ÖÓµÄ1/8
//SYSCLK:ÏµÍ³Ê±ÖÓÆµÂÊ
void SysTick_Init(u8 SYSCLK)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us=SYSCLK/8;
    fac_ms=(u16)fac_us*1000;
}


//ÑÓÊ±nus
//nusÎªÒªÑÓÊ±µÄusÊı.
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD=nus*fac_us; 					//Ê±¼ä¼ÓÔØ
    SysTick->VAL=0x00;        					//Çå¿Õ¼ÆÊıÆ÷
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//¿ªÊ¼µ¹Êı
    do
    {
        temp=SysTick->CTRL;
    } while((temp&0x01)&&!(temp&(1<<16)));		//µÈ´ıÊ±¼äµ½´ï
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//¹Ø±Õ¼ÆÊıÆ÷
    SysTick->VAL =0X00;      					 //Çå¿Õ¼ÆÊıÆ÷
}

//ÑÓÊ±nms
//×¢ÒânmsµÄ·¶Î§
//SysTick->LOADÎª24Î»¼Ä´æÆ÷,ËùÒÔ,×î´óÑÓÊ±Îª:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLKµ¥Î»ÎªHz,nmsµ¥Î»Îªms
//¶Ô72MÌõ¼şÏÂ,nms<=1864
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD=(u32)nms*fac_ms;				//Ê±¼ä¼ÓÔØ(SysTick->LOADÎª24bit)
    SysTick->VAL =0x00;							//Çå¿Õ¼ÆÊıÆ÷
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//¿ªÊ¼µ¹Êı
    do
    {
        temp=SysTick->CTRL;
    } while((temp&0x01)&&!(temp&(1<<16)));		//µÈ´ıÊ±¼äµ½´ï
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//¹Ø±Õ¼ÆÊıÆ÷
    SysTick->VAL =0X00;       					//Çå¿Õ¼ÆÊıÆ÷
}

void Systerm_Config(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //ÖĞ¶ÏÓÅÏÈ¼¶·Ö×é ·Ö2×é
    RCC_Configuration(); //Ê±ÖÓÅäÖÃ
    TIM4_Init(20-1,36000-1);//¶¨Ê±Æ÷
    My_EXTI_Init();//ÖĞ¶ÏµÄ³õÊ¼»¯

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//

    GPIO_Init1();
    USART1_Init(115200);
    ADCx_Init();



}
