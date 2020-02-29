#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "time.h"

#define Temp_Diff1 5
#define Temp_Diff2 10
#define Temp_Diff3 15

u8 beep_flag,beep_num;


/*******************************************************************************
* �� �� ��         : KEY_Init
* ��������		   : ������ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //����ṹ�����
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStructure.GPIO_Pin=KEY_UP_Pin|KEY_DOWN_Pin|KEY_LEFT_Pin|KEY_RIGHT_Pin|KEY_Midd_Pin;	   //ѡ����Ҫ���õ�IO��
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //���ô�������
    GPIO_Init(KEY_UP_Port,&GPIO_InitStructure);		  /* ��ʼ��GPIO */

}



