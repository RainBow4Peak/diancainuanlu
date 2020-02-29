#include "usart.h"
#include "time.h"
 #include <stdlib.h>
 
char Uart1_Buf[Buf1_Max];//串口1接收缓存
u32 First_Int = 0;
u8 Copy_Start = 0;//开始拷贝内存标志
u8 Please_Deal=0;//请求处理标识
u32 Index= NULL ;//开始拷贝的起始地址
u32 Offset = 0;//拷贝的地址偏移量
u8 Flag = 0;
u8 Open = 1;
/*******************************************************************************
* 函 数 名         : USART1_Init
* 函数功能		   : USART1初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/ 
void USART1_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}
/*******************************************************************************
* 函 数 名         : USART1_IRQHandler
* 函数功能		   : USART1中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 r,Res ;
	u32 temp3;
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
//	{
//		r =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
//		USART_SendData(USART1,r);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
//	} 
//	USART_ClearFlag(USART1,USART_FLAG_TC);
	 if (USART_GetFlagStatus(USART1, USART_FLAG_PE) != RESET)  
       {  
           USART_ReceiveData(USART1);  
         USART_ClearFlag(USART1, USART_FLAG_PE);  
       }  
          
       if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)  
       {  
           USART_ReceiveData(USART1);  
         USART_ClearFlag(USART1, USART_FLAG_ORE);  
       }  
          
        if (USART_GetFlagStatus(USART1, USART_FLAG_FE) != RESET)  
       {  
           USART_ReceiveData(USART1);  
          USART_ClearFlag(USART1, USART_FLAG_FE);  
       }  
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
        {     
            USART_ClearFlag(USART1, USART_FLAG_RXNE);  
            USART_ClearITPendingBit(USART1, USART_IT_RXNE);   
   
			r =USART_ReceiveData(USART1);
		
					
	   // USART_SendData(USART1,r);
			Uart1_Buf[First_Int] = r;  	  //将接收到的字符串存到缓存中
					if(Flag == 0 && Open == 1)
					{
												if(r == 'I')
												{
													Flag = 1;
													Open = 0;
												}
												else
												{
													Flag = 0;
												}
				  }
					if(Flag == 1 && Open == 1)
					{
												if(r == 'P')
												{
														Flag = 2;
													Open = 0;
												}
												else
												{
													Flag = 0;
												}
				 }
					if(Flag == 2 && Open == 1)
					{
												if(r == 'D')
												{
														Flag = 3;
													Open = 0;
												}
												else
												{
													Flag = 0;
												}
				 }
					if(Flag == 3 && Open == 1)
					{
												if(r == ',')
												{
														Flag = 4;
													Open = 0;
												}
												else
												{
													Flag = 0;
												}
				 }
			First_Int++;  
					
					
					
					//缓存指针向后移动
			if(First_Int > Buf1_Max)       		//如果缓存满,将缓存指针指向缓存的首地址
	  
	    {
				First_Int = 0;
			} 	
		
			
				}
				if(Please_Deal == 0 && Copy_Start == 1)
				{
					temp3 = Index - (u32)&Uart1_Buf + 4 + Offset;
					if(temp3 < Buf1_Max)
					{
						Data[Offset] = Uart1_Buf[temp3];
					}
					else
					{
						Data[Offset] = Uart1_Buf[temp3 - Buf1_Max];
					}
					//memcpy(Data+Offset,Index+5+Offset,1);
					Offset += 1;
					if(r == '\0')//检测到结束符
					{
						Uart1_Buf[Index-(u32)&Uart1_Buf +1 ] = 'x';
						Index = NULL;
						Offset = 0;
						Copy_Start = 0;
						Please_Deal = 1;
					}
					if(Offset >199)//最大长度为200个字节
					{
						Uart1_Buf[Index-(u32)&Uart1_Buf +1 ] = 'x';
						Index = NULL;
						Offset = 0;
						Copy_Start = 0;
						Please_Deal = 1;
						//CLR_Buf1();
					}
				}
				if(Copy_Start != 1 && Flag == 4)
				{
					Flag =0;
					//Index = strstr(Uart1_Buf,"IPD,");
					Index = (u32)&Uart1_Buf+(First_Int - 5);
					Copy_Start = 1;
				}
				
				Open = 1;
} 	

 /*******************************************************************************
* 函数名  : UART3_SendString
* 描述    : USART1发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART1_SendString(char* s)
{
	u8 i=0;
	while(*s)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
		USART_SendData(USART1 ,*s++);//发送当前字符
 }
}

/*******************************************************************************
* 函数名 : CLR_Buf1
* 描述   : 清除串口1缓存数据
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void CLR_Buf1(void)
{
	u16 k;
	for(k=0;k<Buf1_Max;k++)      //将缓存内容清零
	{
		Uart1_Buf[k] = 0x00;
	}
    First_Int = 0;              //接收字符串的起始存储位置
}
/*******************************************************************************
* 函数名 : Find
* 描述   : 判断缓存中是否含有指定的字符串
* 输入   : 
* 输出   : 
* 返回   : unsigned char:1 找到指定字符，0 未找到指定字符 
* 注意   : 
*******************************************************************************/

u8 Find(char *a)
{ 
  if(strstr(Uart1_Buf,a)!=NULL)
	    return 1;
	else
			return 0;
}
