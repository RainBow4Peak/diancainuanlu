#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"

#define Buf3_Max 60 					  //串口1缓存长度
#define Buf2_Max 200 					  //串口2缓存长度
#define USART3_REC_MAXLEN 200	//最大接收数据长度
#define UART3_SendLR() UART3_SendString("\r\n")

extern char Uart3_Buf[Buf3_Max];//串口1接收缓存
extern char Uart2_Buf[Buf2_Max];//串口2接收缓存
extern u8 First_Int ;
extern vu8 Timer0_start;	//定时器0延时启动计数器
extern vu8 Uart2_Start;	//串口2开始接收数据
extern vu8 Uart2_End;	  //串口2接收数据结束


void USART3_Init_Config(u32 bound);
void UART3_SendString(char* s);
void USART2_Init_Config(u32 bound);
void UART2_SendString(char* s);
void UART2_SendLR(void);
void CLR_Buf3(void);
void Timer4_Init_Config(void);
//串口1发送回车换行


//											 USART_SendData(USART1,0X0D);\
//											 
//											 USART_SendData(USART1,0X0A)
//串口2发送回车换行
#define UART2_SendLR() UART2_SendString("\r\n")
//											 USART_SendData(USART2,0X0D);\
//											 USART_SendData(USART2,0X0A)
#endif
