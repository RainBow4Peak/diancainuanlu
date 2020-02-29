#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "global.h"

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



unsigned char READ_SDA;
unsigned char port_SDA;
unsigned char HYM8563_Address[16]= {0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf};
unsigned char Dec_Hex[22]= {0x3f,0x00,0x18,0x00,0x36,0x80,0x3c,0x80,0x19,0x80,0x2d,0x80,0x2f,0x80,0x38,0x00,0x3f,0x80,0x3d,0x80,0x00,0x00};
unsigned char data[16]= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //???



//SDA����
void	SDA_OUT()	{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}  //SDA�ߵ�ƽ ��©���
void	SDA_IN()	{

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}   //SDA�͵�ƽ ��������
//SCL����
void	SCL_OUT()	{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}   //SCL�ߵ�ƽ �������

void SDA_DATA_OUT(uint8_t a)//���ģʽ��,����ߵ͵�ƽ
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
uint8_t SDA_DATA_IN(void)//����ģʽ��,��ȡ�����Ǹߵ�ƽ���ǵ�ƽ
{
    // uint8_t a;
    unsigned char a;
    a=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    return a;
}
void SCL_DATA_OUT(uint8_t a)//���ģʽ��,����ߵ͵�ƽ
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
    SDA_OUT();  //SDA���
    SCL_OUT();   //SCL���
    SDA_DATA_OUT(1);
    SCL_DATA_OUT(1);
    HYM8563_Write_OneByte(0x00,0x08);
    HYM8563_Write_OneByte(0x01,0x1f);
    HYM8563_Write_OneByte(0x0d,0x82); //32Hz
    HYM8563_Write_OneByte(0x0e,0x00); //��ʱ��ʱ��Ƶ��4096HZ
    DIO=1;
    CLK=1;
    STB=1;
    indate(dissetmode);
    STB=1;
    display(0x00);
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
    SDA_OUT();      //SDA���
    SDA_DATA_OUT(1);
    SCL_DATA_OUT(1);
    delay_us(4);
    SDA_DATA_OUT(0);//START:when CLK is high,DATA change form high to low
    delay_us(4);
    SCL_DATA_OUT(0);
}
//����IIC��ֹ�ź�
void IIC_Stop(void)
{
    SDA_OUT();     //SDA���
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
//������ACKӦ��
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
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//0������Ӧ��ɹ�
unsigned IIC_Wait_Ack(void)
{
    unsigned ucErrTime=0;
    SDA_IN(); //SDA����Ϊ����
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
    SCL_DATA_OUT(0);//ʱ�����0
    return 0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1,��Ӧ��
//0,��Ӧ��
void IIC_Send_Byte(unsigned char txd)
{
    unsigned t;
    SDA_OUT();
    SCL_DATA_OUT(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0; t<8; t++)
    {
        port_SDA=(txd&0x80)>>7;
        if (!port_SDA)
        {
            SDA_DATA_OUT(0);
        }
        else
        {
            SDA_DATA_OUT(1);
        }
        txd<<=1;
        delay_us(2); //��������ʱ���Ǳ����
        SCL_DATA_OUT(1);
        delay_us(2);
        SCL_DATA_OUT(0);
        delay_us(2);
    }
}
//��1���ֽڣ�ack=1,����ACK,ack=0,����nACK
unsigned char IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����

    for(i=0; i<8; i++ )
    {
        SCL_DATA_OUT(0);
        delay_us(2);
        SCL_DATA_OUT(1);
        receive<<=1;

        if(SDA_DATA_IN())receive++;
        delay_us(1);
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}
//��ʱ������
/*
һ�ζ���������ʱ��������
Seconds	��
Minute	��
Hour	ʱ
Date	��
Week	����
Month	��
Years	��
*/
void HYM8563_Read_time() //����д��ַ������ģʽ
{

    IIC_Start();	//����IIC��ʼ�ź�
    IIC_Send_Byte(0XA2);	//����д����
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(0x02); //�������ַ
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Start();
    IIC_Send_Byte(0XA3); //�������ģʽ ������
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���

    sysParam.Seconds=IIC_Read_Byte(1);
    sysParam.Minute=(IIC_Read_Byte(1)&0x7f);
    sysParam.Hour=IIC_Read_Byte(1)&0x3f;
    sysParam.Date=IIC_Read_Byte(1)&0x3f;
    sysParam.Week=IIC_Read_Byte(1)&0x07;
    sysParam.Month=IIC_Read_Byte(1)&0x9f;
    sysParam.Years=IIC_Read_Byte(0);
    IIC_Stop();//����һ��ֹͣ����
    if(sysParam.Seconds>=0x80)	//VL��־ vl=1 ��ѹ���� ����֤׼ȷʱ��
    {   //������ʱ��
        sysParam.Seconds&=0x7f;
    }
		    sysParam.Hour_Low=(sysParam.Hour&0x0f);  //Сʱ�ĸ�λ
    sysParam.Hour_High=((sysParam.Hour>>4)&0x0f); //Сʱ��ʮλ
    sysParam.Minute_Low=(sysParam.Minute&0x0f);  //���ӵĸ�λ
    sysParam.Minute_High=((sysParam.Minute>>4)&0x0f);  //���ӵ�ʮλ
    if (sysParam.Hour_High>=2&&sysParam.Hour_Low>=5)
    {   sysParam.Hour_High=0;
        sysParam.Hour_Low=0;
    }
    if (sysParam.Minute_High>=6&&sysParam.Minute_Low>=1)
    {   sysParam.Minute_High=0;
        sysParam.Minute_Low=0;
    }
    STB=0;
}


void HYM8563_Write_time()
{
//ʱ��׼��ΪBCD����ٽ���д��ʱ��
    Seconds=Hextobcd(Seconds&0x7f);
    Minute=Hextobcd(Minute&0x7f);
    Hour=Hextobcd(Hour&0x3f);
    Week=Hextobcd(Week&0x07);
    Month=Hextobcd(Month&0x9f);
    IIC_Start();	//����IIC��ʼ�ź�
    IIC_Send_Byte(0XA2);	//����д����
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(0x02); //�������ַ
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(Seconds);	//��
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(Minute);	//��
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(Hour);	//ʱ
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(Date);	//��
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(Week);	//��
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(Month);	//��
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(Years);	//��
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Stop();//����һ��ֹͣ����
}
void HYM8563_Write_OneByte(unsigned addr,unsigned data)
{
    IIC_Start();	//����IIC��ʼ�ź�
    IIC_Send_Byte(0XA2);	//����д����
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(addr); //���͵�ַ
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Send_Byte(data); //�����ֽ�
    IIC_Wait_Ack();	//�ȴ�Ӧ���źŵ���
    IIC_Stop();//����һ��ֹͣ����
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
    for(w=0; w<i; w++)
        n+=10;
    n+=k&0x0f;
    return(n);
}



