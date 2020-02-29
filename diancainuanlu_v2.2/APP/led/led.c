#include "led.h"
#include "key.h"







struct STRUCT_LED_PIN_VALUE* getLedPinValueStruct() {

    ledPinValue.Label_Time1=0;//��ʱһ Label
    ledPinValue.Label_Time2=0;//��ʱ�� Label
    ledPinValue.Label_Time3=0;//��ʱ�� Label
    ledPinValue.Label_Power=0;//��Դ Label �� icon
    ledPinValue.Label_Open=0;//�� Label
    ledPinValue.Label_Close=0;//�� Label
    ledPinValue.Label_Temperature_Set=0;//�����¶� Label
    ledPinValue.Label_Temperature_Real=0;//ʵ���¶� Label
    ledPinValue.Fan_Point=0;
    ledPinValue.Fan_Angle1=0;
    ledPinValue.Fan_Angle2=0;
    ledPinValue.Fan_Angle3=0;
    ledPinValue.Fan_Angle4=0;
    ledPinValue.Fan_Angle5=0;
    ledPinValue.Fan_Angle6=0;
    ledPinValue.Fan_Angle7=0;
    ledPinValue.Fan_Angle8=0;
    ledPinValue.Fan_Angle9=0;
    ledPinValue.Watt=0;//���� Label
    ledPinValue.Watt1=0;//���ʼ�1
    ledPinValue.Watt2=0;//���ʼ�2
    ledPinValue.Watt3=0;//���ʼ�3
    ledPinValue.Watt4=0;//���ʼ�4
    ledPinValue.Watt5=0;//���ʼ�5
    ledPinValue.Watt6=0;//���ʼ�6
    ledPinValue.Watt7=0;//���ʼ�7
    ledPinValue.Watt8=0;//���ʼ�8
    ledPinValue.Icon_Logo=0; //���ů¯ Label
    ledPinValue.Icon_Time=0; //Сʱ�ӵ� Icon
    ledPinValue.Icon_Temperature=0;//���϶� Icon
    ledPinValue.Icon_Hot=0;
    ledPinValue.Icon_Insulation=0;
    ledPinValue.Icon_AntiFreeze=0;
    ledPinValue.Icon_Fault=0;
    ledPinValue.Digit_Colon=0;

    return &ledPinValue;
}

void delay(unsigned int xms)
{
    unsigned int x,y;
    for(x=xms; x>0; x--)
        for(y=110; y>0; y--);
}
/*******************************************************************************
* �� �� ��         : GPIO_Init1
* ��������		   : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void GPIO_Init1(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_10|GPIO_Pin_11;  //ѡ����Ҫ���õ�IO��
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
    GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //ѡ����Ҫ���õ�IO��
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
    GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */

    PBout(12)=1;   
    PBout(13)=1;
    PBout(14)=1;
    PBout(15)=1;

}

/*******************************************************************************
* �� �� ��         : indate
* ��������		       : LED������ʾ
* ��    ��         : ��Ҫ��ʾ������
* ��    ��         : ��
*******************************************************************************/
void indate(unsigned char p)
{
    unsigned int i;
    STB=0;
    for(i=0; i<8; i++)
    {
        CLK=0;
        if((p&0x01)!=0)
        {
            DIO=1;
        }
        else
        {
            DIO=0;
        }
        CLK=1;
        p=p>>1;
    }
}

/*******************************************************************************
* �� �� ��         : display
* ��������		       : LED������ʾ
* ��    ��         : ��Ҫ��ʾ������
* ��    ��         : ��
*******************************************************************************/

void display(unsigned char disa)
{
    unsigned int i;
    DIO=1;
    CLK=1;
    STB=1;
    indate(writedatamode_z);
    STB=1;
    indate(startaddress);

    for(i=0; i<datacount; i++)
    {
        indate(disa);
    }
    STB=1;
    indate(disconmode);
    STB=1;
}

void display2(unsigned char address,unsigned char disa)
{
    DIO=1;
    CLK=1;
    STB=1;
    indate(writedatamode_g);
    STB=1;
    indate(address);
    indate(disa);
    STB=1;
}


void LED_Disp(void)
{
    unsigned char i;

    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    data[8] = 0;
    data[9] = 0;
    data[10] = 0;
    data[11] = 0;
    data[12] = 0;
    data[13] = 0;
    data[14] = 0;
    data[15] = 0;

    data[0]|= (ledPinValue.Watt6?0x80:0x00)|(ledPinValue.Watt7?0x40:0x00)|(ledPinValue.Watt8?0x20:0x00)|(ledPinValue.Icon_Hot?0x18:0x00);
    data[1]|=(ledPinValue.Watt?0x20:0x00)|(ledPinValue.Watt1?0x10:0x00)|(ledPinValue.Watt2?0x08:0x00)|(ledPinValue.Watt3?0x04:0x00)|(ledPinValue.Watt4?0x02:0x00)|(ledPinValue.Watt5?0x01:0x00);
    data[2]|=(ledPinValue.Fan_Angle4?0x80:0x00)|(ledPinValue.Fan_Angle3?0x40:0x00)|(ledPinValue.Fan_Angle2?0x20:0x00)|(ledPinValue.Fan_Angle1?0x10:0x00)|(ledPinValue.Label_Temperature_Real?0x08:0x00);
    data[3]|=(ledPinValue.Fan_Point?0x20:0x00)|(ledPinValue.Fan_Angle9?0x10:0x00)|(ledPinValue.Fan_Angle8?0x08:0x00)|(ledPinValue.Fan_Angle7?0x04:0x00)|(ledPinValue.Fan_Angle6?0x02:0x00)|(ledPinValue.Fan_Angle5?0x01:0x00);
    
		ledPinValue.Digit_Hour_High=ledPinValue.Digit_Hour_High*2;
    data[4]|=Dec_Hex[ledPinValue.Digit_Hour_High+1]|(ledPinValue.Label_Time1?0x40:0x00)|(ledPinValue.Label_Open?0x20:0x00)|(ledPinValue.Label_Time2?0x10:0x00)|(ledPinValue.Label_Close?0x08:0x00);
    data[5]|=Dec_Hex[ledPinValue.Digit_Hour_High];
    ledPinValue.Digit_Hour_Low=ledPinValue.Digit_Hour_Low*2;
    data[6]|=Dec_Hex[ledPinValue.Digit_Hour_Low+1]|(ledPinValue.Icon_Logo?0x60:0x00)|(ledPinValue.Icon_Time?0x10:0x00)|(ledPinValue.Digit_Colon?0x08:0x00);
    data[7]|=Dec_Hex[ledPinValue.Digit_Hour_Low];
    ledPinValue.Digit_Minute_High=ledPinValue.Digit_Minute_High*2;
    data[8]|=Dec_Hex[ledPinValue.Digit_Minute_High+1]|(ledPinValue.Label_Time3?0x70:0x00)|(ledPinValue.Label_Temperature_Set?0x08:0x00);
    data[9]|=Dec_Hex[ledPinValue.Digit_Minute_High];
    ledPinValue.Digit_Minute_Low=ledPinValue.Digit_Minute_Low*2;
    data[10]|=Dec_Hex[ledPinValue.Digit_Minute_Low+1]|(ledPinValue.Label_Power?0x70:0x00);
    data[11]|=Dec_Hex[ledPinValue.Digit_Minute_Low];
    ledPinValue.Digit_Temperature_High=ledPinValue.Digit_Temperature_High*2;
    data[12]|=Dec_Hex[ledPinValue.Digit_Temperature_High+1]|(ledPinValue.Icon_Insulation?0x60:0x00)|(ledPinValue.Icon_AntiFreeze?0x18:0x00);
    data[13]|=Dec_Hex[ledPinValue.Digit_Temperature_High];
    ledPinValue.Digit_Temperature_Low=ledPinValue.Digit_Temperature_Low*2;
    data[14]|=Dec_Hex[ledPinValue.Digit_Temperature_Low+1]|(ledPinValue.Icon_Fault?0x60:0x00)|(ledPinValue.Icon_Temperature?0x10:0x00);
    data[15]|=Dec_Hex[ledPinValue.Digit_Temperature_Low];
    

    for(i=0; i<16; i++)
        display2(HYM8563_Address[i],data[i]);

}



