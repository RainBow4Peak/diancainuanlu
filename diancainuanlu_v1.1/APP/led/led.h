#ifndef _led_H
#define _led_H
#include "stm32f10x.h"
#include "system.h"

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
extern unsigned char Hour1,Hour2,Minute1,Minute2,Seconds1,Seconds2;
extern unsigned char Temperature1_Digital,Temperature2_Digital;
extern unsigned char Time1_Disp,Time2_Disp,Time3_Disp,Power_Disp,Open_Disp;
extern unsigned char Close_Disp,Fan1_Disp,Fan2_Disp,Watt0_Disp,Watt1_Disp,Watt2_Disp;
extern unsigned char  Watt3_Disp,Label1_Disp,Label2_Disp,Label3_Disp;;
extern unsigned char Temperature1_Disp,Temperature2_Disp,Hot_Disp;
extern unsigned char Insulation_Disp,AntiFreeze_Disp,FaultDisp;
extern unsigned char Key1_Disp,Key2_Disp,Key3_Disp,Key4_Disp,Key5_Disp;

extern unsigned char Time1_Start_Hour,Time1_Start_Min,Time1_Stop_Hour,Time1_Stop_Min,Time1_Temp;
extern unsigned char Time2_Start_Hour,Time2_Start_Min,Time2_Stop_Hour,Time2_Stop_Min,Time2_Temp;
extern unsigned char Time3_Start_Hour,Time3_Start_Min,Time3_Stop_Hour,Time3_Stop_Min,Time3_Temp;

extern unsigned char Time1_Start_Hour1,Time1_Start_Min1,Time1_Stop_Hour1,Time1_Stop_Min1,Time1_Temp1; 
extern unsigned char Time1_Start_Hour2,Time1_Start_Min2,Time1_Stop_Hour2,Time1_Stop_Min2,Time1_Temp2;  
extern unsigned char Time2_Start_Hour1,Time2_Start_Min1,Time2_Stop_Hour1,Time2_Stop_Min1,Time2_Temp1; 
extern unsigned char Time2_Start_Hour2,Time2_Start_Min2,Time2_Stop_Hour2,Time2_Stop_Min2,Time2_Temp2;  
extern unsigned char Time3_Start_Hour1,Time3_Start_Min1,Time3_Stop_Hour1,Time3_Stop_Min1,Time3_Temp1; 
extern unsigned char Time3_Start_Hour2,Time3_Start_Min2,Time3_Stop_Hour2,Time3_Stop_Min2,Time3_Temp2;

extern unsigned char Warm_Temp,Warm_Temp1,Warm_Temp2;
extern unsigned char Cold_Temp,Cold_Temp1,Cold_Temp2;
extern unsigned char Temp1,Temp2;
	
extern unsigned char Hour1_Set,Hour2_Set,Minute1_Set,Minute2_Set,Temp1_Set,Temp2_Set;

extern void GPIO_Init1(void);
extern void indate(unsigned char p);
extern void display(unsigned char disa);
extern void display2(unsigned char address,unsigned char disa);
extern void LED_Disp(void);
extern void LED_Set_Disp(void);
extern void Key_Control(void);
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
//unsigned char Seconds=0x02,	Minute=0x03,Hour=0x00,Date=0x05,Week=0x06,	Month=0x07,Years=0x08;	//?	
extern unsigned char Seconds,	Minute,Hour,Date,Week,Month,Years;	
extern unsigned char Hour1,Hour2,Minute1,Minute2,Seconds1,Seconds2;
extern unsigned char READ_SDA;
extern unsigned char port_SDA;


extern u8 m;
extern int AddKey1(unsigned char a1,unsigned char a2);
extern int AddKey2(unsigned char a1,unsigned char a2);
extern int AddKey3(unsigned char a1,unsigned char a2);
extern int ReduKey1(unsigned char a1,unsigned char a2);
extern int ReduKey2(unsigned char a1,unsigned char a2);
extern int ReduKey3(unsigned char a1,unsigned char a2);
extern void power_disp(u8 Num);

/*  按键引脚定义 */
//#define Open_Close PAout(3)
//#define Set_Key PAin(4)
//#define Add_Key PAin(5)
//#define Sub_Key PAin(6)


extern u8 Disp_Model_Flag;


/*  Flash定义 */
extern u8 Write_Flash(u16 *buff, u8 len);
extern void Read_Flash(u16 *buff, u8 len);
extern u8 key1_Num,key2_Num,key3_Num,key4_Num,key5_Num;

#endif
