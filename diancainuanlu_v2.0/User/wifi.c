#include "stm32f10x.h"
#include "usart.h"
#include <stdlib.h>
#include <wifi.h>
#include "SysTick.h"

//Wifi模式
char *Set_Mode="AT+CWMODE_DEF=2";
char *RST="AT+RST";
char *Set_Name="AT+CWSAP_DEF=\"AAASSSDDD\",\"12345678\",1,3";
char *Set_Parameter="AT+CIPAP=\"192.168.3.1\",\"192.168.3.1\",\"255.255.255.0\"";
char *Mult_Mode="AT+CIPMUX=1";
char *Open_Server="AT+CIPSERVER=1,8080";
u8 Send_Again=1;

u16 Send_Num=0;
//AT+CIPSEND=0,5
u8 Timer0_start=0,Send_START=0,Send_Again_Num=0;
u16 Wifi_TimuOut_Num=0;
u8 FLAG = 0x00;
u8 Find(char *a);
/*******************************************************************************
* 函数名 : Second_AT_Command
* 描述   : 发送AT指令函数
* 输入   : 发送数据的指针、希望接收到的应答数据指针、发送等待时间(单位：S)
* 输出   :
* 返回   :
* 注意   :
*******************************************************************************/

void Second_AT_Command(char *b,char *a,u8 flag)
{

    u8 i;
    u32 count;
	if(!Find(a))
	{CLR_Buf1();}
	else{
		FLAG = flag;
		CLR_Buf1();
		return;
	}
    i = 0;
//GPRS_TimuOut_Num=0;
    Send_START  = 1;
    while(i == 0)
    {
        if(!Find(a))
        {
            if(Timer0_start == 0)
            {
                for (; *b!='\0'; b++)
                {
                    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
                    USART_SendData(USART1,*b);
                }
                UART1_SendLR();
                Timer0_start = 1;
            }
        }
        else
        {
            i = 1;
            Timer0_start = 0;
            FLAG = flag;
            Send_Again_Num=0;
        }
        if(Wifi_TimuOut_Num>500)
        {
            Send_START  = 0;
            Wifi_TimuOut_Num = 0;
            Timer0_start = 0;
            Send_Again_Num=0;
            break;
        }

    }

    CLR_Buf1();
}

/*******************************************************************************
* 函数名 : Second_AT_Command
* 描述   : 发送AT指令函数
* 输入   : 发送数据的指针、希望接收到的应答数据指针、发送等待时间(单位：S)
* 输出   :
* 返回   :
* 注意   :
*******************************************************************************/

void Send_AT_Data_INIT(char *b,char *a,u8 flag)
{
		if(!Find(a))
		{
			Second_AT_Command(b,a,flag);
		}
}

