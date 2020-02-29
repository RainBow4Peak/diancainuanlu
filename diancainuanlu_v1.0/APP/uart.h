#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"

#define Buf3_Max 60 					  //����1���泤��
#define Buf2_Max 200 					  //����2���泤��
#define USART3_REC_MAXLEN 200	//���������ݳ���
#define UART3_SendLR() UART3_SendString("\r\n")

extern char Uart3_Buf[Buf3_Max];//����1���ջ���
extern char Uart2_Buf[Buf2_Max];//����2���ջ���
extern u8 First_Int ;
extern vu8 Timer0_start;	//��ʱ��0��ʱ����������
extern vu8 Uart2_Start;	//����2��ʼ��������
extern vu8 Uart2_End;	  //����2�������ݽ���


void USART3_Init_Config(u32 bound);
void UART3_SendString(char* s);
void USART2_Init_Config(u32 bound);
void UART2_SendString(char* s);
void UART2_SendLR(void);
void CLR_Buf3(void);
void Timer4_Init_Config(void);
//����1���ͻس�����


//											 USART_SendData(USART1,0X0D);\
//											 
//											 USART_SendData(USART1,0X0A)
//����2���ͻس�����
#define UART2_SendLR() UART2_SendString("\r\n")
//											 USART_SendData(USART2,0X0D);\
//											 USART_SendData(USART2,0X0A)
#endif
