#ifndef __usart_H
#define __usart_H

#include "system.h" 


#define Buf1_Max 60

void USART1_Init(u32 bound);
extern char Uart1_Buf[Buf1_Max];

#endif


