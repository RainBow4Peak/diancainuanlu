#ifndef __usart_H
#define __usart_H

#include "system.h" 


#define Buf1_Max 512

void USART1_Init(u32 bound);
extern char Uart1_Buf[Buf1_Max];
extern void UART1_SendString(char* s);
extern void CLR_Buf1(void);
extern char Uart1_Buf_cp[Buf1_Max];
extern u8 Please_Deal;//请求处理标识
#endif


