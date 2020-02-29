#include "stm32f10x.h"
#include "led.h"
#include "key.h"
void HYM8563_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(void);
void IIC_NAck(void);
unsigned IIC_Wait_Ack(void);
void IIC_Send_Byte(unsigned char txd);
unsigned char IIC_Read_Byte(unsigned char ack);
void HYM8563_Read_time(void);
void HYM8563_Write_time(void);
void HYM8563_Write_OneByte(unsigned addr,unsigned data);
unsigned char Hextobcd(unsigned char Data);
unsigned char bcdtohex(unsigned char k);
unsigned char Seconds=0x02,	Minute=0x03,Hour=0x00,Date=0x05,Week=0x06,	Month=0x07,Years=0x08;	//?	

unsigned char Hour1,Hour2,Minute1,Minute2,Seconds1,Seconds2;
unsigned char Temperature1_Digital,Temperature2_Digital;
unsigned char Time1_Disp,Time2_Disp,Time3_Disp,Power_Disp,Open_Disp;
unsigned char Close_Disp,Fan1_Disp,Fan2_Disp,Watt0_Disp,Watt1_Disp,Watt2_Disp;
unsigned char  Watt3_Disp,Label1_Disp,Label2_Disp,Label3_Disp;
unsigned char Temperature1_Disp,Temperature2_Disp,Hot_Disp;
unsigned char Insulation_Disp,AntiFreeze_Disp,FaultDisp;
unsigned char Key1_Disp,Key2_Disp,Key3_Disp,Key4_Disp,Key5_Disp;

 
unsigned char READ_SDA;
unsigned char port_SDA;
unsigned char HYM8563_Address[16]={0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf};
unsigned char Dec_Hex[22]={0x3f,0x00,0x18,0x00,0x36,0x80,0x3c,0x80,0x19,0x80,0x2d,0x80,0x2f,0x80,0x38,0x00,0x3f,0x80,0x3d,0x80,0x00,0x00};
unsigned char data[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //???



//SDA方向
void	SDA_OUT()	{
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;   
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
        GPIO_Init(GPIOB, &GPIO_InitStructure); 
}  //SDA高电平 开漏输出
void	SDA_IN()	{

        GPIO_InitTypeDef GPIO_InitStructure;
     
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
        GPIO_Init(GPIOB, &GPIO_InitStructure);
}   //SDA低电平 上拉输入
//SCL方向
void	SCL_OUT()	{
	      GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;   
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
        GPIO_Init(GPIOB, &GPIO_InitStructure);
}   //SCL高电平 推挽输出

void SDA_DATA_OUT(uint8_t a)//输出模式下,输出高低电平
{
    if(a==1)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_11);
    }
    else if(a==0)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_11);
    }
}
uint8_t SDA_DATA_IN(void)//输入模式下,读取引脚是高电平还是电平
{
   // uint8_t a;
	unsigned char a;
    a=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    return a;
}
void SCL_DATA_OUT(uint8_t a)//输出模式下,输出高低电平
{
    if(a==1)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_10);
    }
    else if(a==0)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_10);
    }
}

void HYM8563_Init(void)
{
SDA_OUT();  //SDA输出
SCL_OUT();   //SCL输出
SDA_DATA_OUT(1);
SCL_DATA_OUT(1);
HYM8563_Write_OneByte(0x00,0x08);
HYM8563_Write_OneByte(0x01,0x1f);
HYM8563_Write_OneByte(0x0d,0x82); //32Hz
HYM8563_Write_OneByte(0x0e,0x00); //定时器时钟频率4096HZ
DIO=1;
	CLK=1;
	STB=1;
  indate(dissetmode);
	STB=1;
  display(0x00);	
}
//产生IIC起始信号
void IIC_Start(void)
{
SDA_OUT();      //SDA输出
SDA_DATA_OUT(1);
SCL_DATA_OUT(1);
delay_us(4);
SDA_DATA_OUT(0);//START:when CLK is high,DATA change form high to low
delay_us(4);
SCL_DATA_OUT(0);
}
//产生IIC终止信号
void IIC_Stop(void)
{
SDA_OUT();     //SDA输出
SCL_DATA_OUT(0);
SDA_DATA_OUT(0);//STOP:when CLK is high DATA change form low to high
delay_us(4);
SCL_DATA_OUT(1);
SDA_DATA_OUT(1);
delay_us(4);
}
 
void IIC_Ack(void)
{
SCL_DATA_OUT(0);
SDA_OUT();
SDA_DATA_OUT(0);
delay_us(2);
SCL_DATA_OUT(1);
delay_us(2);
SCL_DATA_OUT(0);
}
//不产生ACK应答
void IIC_NAck(void)
{
SCL_DATA_OUT(0);
SDA_OUT();
SDA_DATA_OUT(1);
delay_us(2);
SCL_DATA_OUT(1);
delay_us(2);
SCL_DATA_OUT(0);
}
//等待应答信号到来
//返回值：1，接收应答失败
//0，接收应答成功
unsigned IIC_Wait_Ack(void)
{
unsigned ucErrTime=0;
SDA_IN(); //SDA设置为输入
SDA_DATA_OUT(1);
delay_us(1);
SCL_DATA_OUT(1);
delay_us(1);
	
while(SDA_DATA_IN())
{
ucErrTime++;
if(ucErrTime>250)
{
IIC_Stop();
return 1;
}
}
SCL_DATA_OUT(0);//时钟输出0
return 0;
}
//IIC发送一个字节
//返回从机有无应答
//1,有应答
//0,无应答
void IIC_Send_Byte(unsigned char txd)
{
unsigned t;
SDA_OUT();
SCL_DATA_OUT(0);//拉低时钟开始数据传输
for(t=0;t<8;t++)
{
port_SDA=(txd&0x80)>>7;
	if (!port_SDA)
  { SDA_DATA_OUT(0);}
  else
	{ SDA_DATA_OUT(1); }
txd<<=1;
delay_us(2); //这三个延时都是必须的
SCL_DATA_OUT(1);
delay_us(2);
SCL_DATA_OUT(0);
delay_us(2);
}
}
//读1个字节，ack=1,发送ACK,ack=0,发送nACK
unsigned char IIC_Read_Byte(unsigned char ack)
{
unsigned char i,receive=0;
SDA_IN();//SDA设置为输入
	
for(i=0;i<8;i++ )
{
SCL_DATA_OUT(0);
delay_us(2);
SCL_DATA_OUT(1);
receive<<=1;
	
if(SDA_DATA_IN())receive++;
delay_us(1);
}
if (!ack)
IIC_NAck();//发送nACK
else
IIC_Ack(); //发送ACK
return receive;
}
//读时间数据
/*
一次读出年月日时分秒数据
Seconds	秒
Minute	分
Hour	时
Date	日
Week	星期
Month	月
Years	年
*/
void HYM8563_Read_time() //采用写地址读数据模式
{
	
IIC_Start();	//产生IIC起始信号
IIC_Send_Byte(0XA2);	//发送写命令
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(0x02); //发送秒地址
IIC_Wait_Ack();	//等待应答信号到来
IIC_Start();
IIC_Send_Byte(0XA3); //进入接收模式 读命令
IIC_Wait_Ack();	//等待应答信号到来
Seconds=IIC_Read_Byte(1);
Minute=(IIC_Read_Byte(1)&0x7f);
Hour=IIC_Read_Byte(1)&0x3f;
Date=IIC_Read_Byte(1)&0x3f;
Week=IIC_Read_Byte(1)&0x07;
Month=IIC_Read_Byte(1)&0x9f;
Years=IIC_Read_Byte(0);
IIC_Stop();//产生一个停止条件
if(Seconds>=0x80)	//VL标志 vl=1 电压过低 不保证准确时钟
{//可重置时钟
Seconds&=0x7f;
}
  Hour2=(Hour&0x0f);  //小时的个位
  Hour1=((Hour>>4)&0x0f); //小时的十位
  Minute2=(Minute&0x0f);  //分钟的个位
  Minute1=((Minute>>4)&0x0f);  //分钟的十位
  //Seconds2=(Seconds&0x0f);  //秒的个位
  //Seconds1=((Seconds>>4)&0x0f);  //秒的十位
if (Hour1>=2&&Hour2>=5)
  { Hour1=0;
    Hour2=0;}
if (Minute1>=6&&Minute2>=1)
  { Minute1=0;
    Minute2=0;}
   STB=0;		
}


void HYM8563_Write_time()
{
//时间准换为BCD码后再进行写入时钟
Seconds=Hextobcd(Seconds&0x7f);
Minute=Hextobcd(Minute&0x7f);
Hour=Hextobcd(Hour&0x3f);
Week=Hextobcd(Week&0x07);
Month=Hextobcd(Month&0x9f);
IIC_Start();	//产生IIC起始信号
IIC_Send_Byte(0XA2);	//发送写命令
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(0x02); //发送秒地址
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(Seconds);	//秒
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(Minute);	//分
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(Hour);	//时
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(Date);	//日
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(Week);	//周
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(Month);	//月
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(Years);	//年
IIC_Wait_Ack();	//等待应答信号到来
IIC_Stop();//产生一个停止条件
}
void HYM8563_Write_OneByte(unsigned addr,unsigned data)
{
IIC_Start();	//产生IIC起始信号
IIC_Send_Byte(0XA2);	//发送写命令
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(addr); //发送地址
IIC_Wait_Ack();	//等待应答信号到来
IIC_Send_Byte(data); //发送字节
IIC_Wait_Ack();	//等待应答信号到来
IIC_Stop();//产生一个停止条件
}
unsigned char Hextobcd(unsigned char Data)
{
unsigned char k=0;
while (Data>=10)
{
k+=16;
Data-=10;
}
k+=Data;
return(k);
}
unsigned char bcdtohex(unsigned char k)
{
unsigned char i=0,w=0,n=0;
i=(k>>4)&0x0f;
for(w=0;w<i;w++)
n+=10;
n+=k&0x0f;
return(n);
}



