#ifndef _led_H
#define _led_H
#include "stm32f10x.h"
#include "system.h"
#include "global.h"





struct STRUCT_LED_PIN_VALUE* getLedPinValueStruct();


extern void RCC_Configuration(void);
extern void SysTick_Init(u8 SYSCLK);
extern void delay_us(u32 nus);
extern void delay_ms(u16 nms);
//extern void IWDG_Init(u8 pre,u16 rlr);
/*  数码管引脚定义 */

#define DIO PBout(13)
#define STB PBout(14)
#define CLK PBout(15)

#define FMQ PBout(7)  //蜂鸣器
#define UJ1 PBout(6)  //继电器的控制
#define UJ2 PBout(5)
#define UJ3 PBout(4)
#define UJ4 PBout(3)

#define seg 14
#define grid 8
#define key 4
#define dismodel 1


#define dissetmode 0x44
#define writedatamode_z 0x40
#define writeledmode_z 0x41
#define readkeymode 0x42
#define readswmode 0x43
#define writedatamode_g 0x44
#define writeledmode_g 0x45
#define startaddress 0xc0
#define disconmode 0x8c
#define datacount 2*grid
extern unsigned char HYM8563_Address[16];
extern unsigned char data[16];
extern unsigned char Dec_Hex[22];


extern void GPIO_Init1(void);
extern void indate(unsigned char p);
extern void display(unsigned char disa);
extern void display2(unsigned char address,unsigned char disa);
extern void LED_Disp(void);
extern void LED_Set_Disp(void);
extern void My_EXTI_Init(void);
extern void delay(unsigned int xms);

/*  时钟引脚定义 */

#define SDA PBout(11)  //A6
#define SCL PBout(10)  //A7


extern void HYM8563_Init(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
//extern void	delay_us(unsigned char N);
extern void IIC_Ack(void);
extern void IIC_NAck(void);
extern unsigned IIC_Wait_Ack(void);
extern void IIC_Send_Byte(unsigned char txd);
extern unsigned char IIC_Read_Byte(unsigned char ack);
extern void HYM8563_Read_time(void);
extern void HYM8563_Write_time(void);
extern void HYM8563_Write_OneByte(unsigned addr,unsigned data);
extern unsigned char Hextobcd(unsigned char Data);
extern unsigned char bcdtohex(unsigned char k);
extern unsigned char Seconds,	Minute,Hour,Date,Week,Month,Years;
extern unsigned char Hour1,Hour2,Minute1,Minute2,Seconds1,Seconds2;
extern unsigned char READ_SDA;
extern unsigned char port_SDA;


#endif
