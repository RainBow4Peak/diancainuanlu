#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "time.h"

#define Temp_Diff1 5
#define Temp_Diff2 10
#define Temp_Diff3 15

u8 Time_Mode,Work_Time_Flag;
u8 AT,ST,DT;

 u8 Delay_count1, Delay_count2;
u8 FMQ_flag;
u8 Work;
u8 k;
u8 p;
u8 key2_flag1,key2_flag2,key2_flag3;
u8 keymode,Time_mode,Keymode_Exit;
u8 Disp_Model_Flag,Real_Temprature;


void Fan_Flahs(void);
void Fan_Flahs(void)
{
		if(Fan_Glitter_Num>=9)
		Fan_Glitter_Num=0;
		if (Real_Temprature==1)
		{
switch(Fan_Glitter_Num%9)
	{
case 0:  display2(0xC2,0x88);
		 display2(0xC3,0x20);break;
case 1:  display2(0xC2,0x48);
		display2(0xC3,0x20);break;
case 2:  display2(0xC2,0x28);
		display2(0xC3,0x20);break;
case 3:  display2(0xC2,0x18);
		display2(0xC3,0x20);break;
		case 4:  display2(0xC3,0x30);break;
case 5:  display2(0xC3,0x28);break;
case 6:  display2(0xC3,0x24);break;
case 7:  display2(0xC3,0x22);break;
case 8:  display2(0xC3,0x21);break;
	}
}	
	if (Real_Temprature==0)
		{
switch(Fan_Glitter_Num%9)
	{
case 0:  display2(0xC2,0x80);
		 display2(0xC3,0x20);break;
case 1:  display2(0xC2,0x40);
		display2(0xC3,0x20);break;
case 2:  display2(0xC2,0x20);
		display2(0xC3,0x20);break;
case 3:  display2(0xC2,0x10);
		display2(0xC3,0x20);break;
		case 4:  display2(0xC3,0x30);break;
case 5:  display2(0xC3,0x28);break;
case 6:  display2(0xC3,0x24);break;
case 7:  display2(0xC3,0x22);break;
case 8:  display2(0xC3,0x21);break;
	}
}	


}


 
/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : 按键初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=KEY_UP_Pin|KEY_DOWN_Pin|KEY_LEFT_Pin|KEY_RIGHT_Pin|KEY_Midd_Pin;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//下拉输入  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //设置传输速率
	GPIO_Init(KEY_UP_Port,&GPIO_InitStructure);		  /* 初始化GPIO */
	
}



void Key_Beep(void)
{

if((key_1==1)||(key_2==1)||(key_3==1)||(key_4==1)||(key_5==1))	 
       { 
	 
        FMQ=1;
       	if(FMQ_Num>=10)
				{
					FMQ_Num=0;
					FMQ=0;
					key_1=0;
					key_2=0;
					key_3=0;
					key_4=0;
					key_5=0;
				}
      }
}

void Key1_Init(void)
{
if(key1_Num==0)  
{	
        Open_Disp=0x00;
       	data[4]&=0xdf;
        Close_Disp=0x08;
       	Temperature1_Disp=0x00;
       	data[8]&=0xf7;
        Temperature2_Disp=0x08;
	        Real_Temprature=1;
		Time1_Disp=0x00;  
	data[4]&=0xbf;			 
Time2_Disp=0x00;
	data[4]&=0xef;			 
Time3_Disp=0x00; 	
	data[8]&=0x8f;				 
       	Watt0_Disp=0x00;
        Watt1_Disp=0x00;
				  Watt2_Disp=0x00; 
				 data[1]&=0xc0; 
        Watt3_Disp=0x00;
				data[0]&=0x1f;
	Hot_Disp=0x00;
	data[0]&=0x07;
	data[1]&=0xc0;
Insulation_Disp=0x00;
  data[12]&=0x9f;
AntiFreeze_Disp=0x00;
  data[12]&=0xe7;				 
	Fan1_Disp=0x00;
        Fan2_Disp=0x00;
	data[2]&=0x0f;
	data[3]&=0xc0;				 
      UJ1=0;
    UJ2=0; 
    UJ3=0;  
	  UJ4=0;
	  key2_Num=0;
     //   LED_Disp();
}
}





void Key1_Control(void)
{

    if(key1_Num==1)
     {

      UJ1=1; 
			 
				if (UJ1==1)
			 {
	       Fan_Flahs();	
       }				  
			 HYM8563_Read_time();
			 if(Keymode_Exit==0)
			 {
			Temp2=AT%10;  //温度的个位
      Temp1=AT/10; //温度的十位	
			 } 
			 Time_Work_Mode();
if(Work==1)
{ 
	    Open_Disp=0x20; 
      Close_Disp=0x00;	
      data[4]&=0xf7;
	if(keymode==0) 	
	{	
		if(UJ2==1)
		{
			Hot_Disp=0x18;
    Insulation_Disp=0x00;
		data[12]&=0x9f;	
    AntiFreeze_Disp=0x00;
    data[12]&=0xe7;
				FaultDisp=0x00;
	data[14]&=0x9f;
		}
		else
		{
				Watt0_Disp=0x00;
        Watt1_Disp=0x00;
				  Watt2_Disp=0x00; 
				 data[1]&=0xc0; 
        Watt3_Disp=0x00;
				data[0]&=0x1f;
				UJ1=1;
       	UJ2=0;  
				 	UJ3=0;  
				 	UJ4=0;
		Hot_Disp=0x00;
		data[0]&=0xe7;	
    Insulation_Disp=0x60;
    AntiFreeze_Disp=0x00;
    data[12]&=0xe7;
		}
        }
    if(keymode==1) 
     {
    	Insulation_Disp=0x00;
  data[12]&=0x9f;
AntiFreeze_Disp=0x18;
      }
		
		 		m=((Warm_Temp1<<4)|Warm_Temp2);
			 Warm_Temp=(0xff & (m>>4))*10 +(0xf & m);
if(Warm_Temp>AT) 
{DT=Warm_Temp-AT;}
else	
{DT=Warm_Temp-ST;}
			  if((AT>=0x80)||(AT>Warm_Temp))
			  {
				Hot_Disp=0x00;
				data[1]&=0xe7;
				Insulation_Disp=0x60;
       UJ2=0;  
       UJ3=0;  
       UJ4=0;  					
			  }
       else
		   {
	 if(keymode==0)  //用k计数，后续用温度值
    {
		 if(DT<5)  //用k计数，后续用温度值
       {
       	UJ1=1;
       	UJ2=1;  //打开1设备
				 	UJ3=0;  
				 	UJ4=0;  
       Watt0_Disp=0x20;	
           Watt1_Disp=0x18;
            Watt2_Disp=0x00;
          data[1]&=0xf8;
            Watt3_Disp=0x00;
         data[0]&=0x1f;
			 }      
       else if(DT<10)
       {	
       	UJ1=1;
       	UJ2=1;  //打开1设备
       	UJ3=1;  //打开2设备
				 	UJ4=0;  
       Watt0_Disp=0x20;	
           Watt1_Disp=0x18;
            Watt2_Disp=0x07;
            Watt3_Disp=0x00;
         data[0]&=0x1f;
			 }
       else 
       {	
       UJ1=1;
       UJ2=1;  //打开1设备
       UJ3=1;  //打开2设备	
       UJ4=1;  //打开3设备	
       Watt0_Disp=0x20;	
           Watt1_Disp=0x18;
            Watt2_Disp=0x07;
            Watt3_Disp=0xe0;
			 }
		 }
		if(keymode==1)
		{ 
			 if(AT>Warm_Temp)
			  {
				Hot_Disp=0x00;
				data[0]&=0xe7;
					      	Watt0_Disp=0x00;
        Watt1_Disp=0x00;
				  Watt2_Disp=0x00; 
				 data[1]&=0xc0; 
        Watt3_Disp=0x00;
				data[0]&=0x1f;
							  	UJ1=1;
       	UJ2=0;  
				 	UJ3=0;  
				 	UJ4=0;  	
				}
				else
				{
			  	UJ1=1;
       	UJ2=1;  //打开1设备
				 	UJ3=0;  
				 	UJ4=0;  
       Watt0_Disp=0x20;	
           Watt1_Disp=0x18;
            Watt2_Disp=0x00;
          data[1]&=0xf8;
            Watt3_Disp=0x00;
         data[0]&=0x1f;
				}
		}
	
	 }
 }
if(Work==0)
{
	        Open_Disp=0x00;
       	data[4]&=0xdf;
        Close_Disp=0x08; 
	UJ1=1;
	    
       	UJ2=0; 
       	UJ3=0;
				Hot_Disp=0x00;
				data[0]&=0xe7;
					      	Watt0_Disp=0x00;
        Watt1_Disp=0x00;
				  Watt2_Disp=0x00; 
				 data[1]&=0xc0; 
        Watt3_Disp=0x00;
				data[0]&=0x1f;
}



}
}



void Key2_Control(void)
{
 if (Flash_Num>500)
 {
	 Keymode_Exit=0;
	 key2_Num=0;
     
	  
 } 
	 
 if((key2_Num==0) && key1_Num==1) 
{
		Time1_Disp=0x00;  
	  data[4]&=0xbf;			 
    Time2_Disp=0x00;
	  data[4]&=0xef;			 
    Time3_Disp=0x00; 	
	  data[8]&=0x8f;
	  if(keymode==0)  //用k计数，后续用温度值
    {			
        if(key3_Num==1)
       {
			    Keymode_Exit=1;
				  Temperature1_Disp=0x08;
          Temperature2_Disp=0x00;
	        data[2]&=0xf7;
				 Real_Temprature=0;
		       m=((Warm_Temp1<<4)|Warm_Temp2);
		       m=AddKey3(Warm_Temp1,Warm_Temp2);
		       key3_Num=0;	
				   Warm_Temp2=(m&0x0f);
           Warm_Temp1=((m>>4)&0x0f);
			     Warm_Temp=(0xff & (m>>4))*10 +(0xf & m);
           HYM8563_Read_time();
          Temp2=Warm_Temp2;  
           Temp1=Warm_Temp1; 
					 	if(m>0x80)
            m=0x80;	
         }			
        if(key4_Num==1)
        {
						Keymode_Exit=1;
						Temperature1_Disp=0x08;
						Temperature2_Disp=0x00;
				  	Real_Temprature=0;
						data[2]&=0xf7;
						m=((Warm_Temp1<<4)|Warm_Temp2);
						m=ReduKey3(Warm_Temp1,Warm_Temp2);
						key4_Num=0;
					  Warm_Temp2=(m&0x0f);
						Warm_Temp1=((m>>4)&0x0f);
					  Warm_Temp=(0xff & (m>>4))*10 +(0xf & m);
	          HYM8563_Read_time();
          Temp2=Warm_Temp2;  
           Temp1=Warm_Temp1; 
					 	if(m<0x04)
            m=0x04;	
         }
				 	
     }
		HYM8563_Read_time();//采用写地址读数据模式
		Hour1_Set=Hour1;
  	Hour2_Set=Hour2;
  	Minute1_Set=Minute1;
  	Minute2_Set=Minute2;
		  Temp2_Set=Warm_Temp2;  
            Temp1_Set=Warm_Temp1;  
   LED_Set_Disp();	
	 
	}  
    if(key2_Num==1) 
    {
		
       	 Temperature1_Disp=0x00;
			  Real_Temprature=1;
       	data[8]&=0xf7;
        Temperature2_Disp=0x08; 		 
	HYM8563_Read_time();//采用写地址读数据模式
				 	m=((Hour1<<4)|Hour2);
//	 if(key3_Num==1) 
//   {
//		  m=AddKey1(Hour1,Hour2);
//		  key3_Num=0;
//		 	Hour=(0xff & (m>>4))*10 +(0xf & m);
//		  Minute=(0xff & (Minute>>4))*10 +(0xf & Minute);
//		 	Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
//      HYM8563_Write_time();
//	 }
//	 if(key4_Num==1) 
//   {	 
//		m=ReduKey1(Hour1,Hour2);
//		key4_Num=0;
//		 	 		  Hour=(0xff & (m>>4))*10 +(0xf & m);
//		 Minute=(0xff & (Minute>>4))*10 +(0xf & Minute);
//		Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
//     HYM8563_Write_time();
//	 }
    Set_System_Time();
	
//		if(Time_flag==1)
//	{
//        p++;
//	  Time_flag=0;	
//	}
//Delay_count1=p/10;
//	if(Delay_count1%2)
//	{
//  HYM8563_Read_time();//采用写地址读数据模式
//	}
//	else
//	{ 			HYM8563_Read_time();//采用写地址读数据模式
//        Hour1=10;
//  	Hour2=10;

//	}
			Temp2=AT%10;  //温度的个位
      Temp1=AT/10; //温度的十位	
    LED_Disp();

       }
    else if(key2_Num==3)  
       {

       	Temperature1_Disp=0x00;
       	data[8]&=0xf7;
        Temperature2_Disp=0x08; 
         Real_Temprature=1;				 
	HYM8563_Read_time();//采用写地址读数据模式
				 	m=((Minute1<<4)|Minute2);
	 if(key3_Num==1) 
   {
		m=AddKey2(Minute1,Minute2);
		key3_Num=0;
		 		 Hour=(0xff & (Hour>>4))*10 +(0xf & Hour);
		 	 		  Minute=(0xff & (m>>4))*10 +(0xf & m);
		 	Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
     HYM8563_Write_time();
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey2(Minute1,Minute2);
		key4_Num=0;
		 Hour=(0xff & (Hour>>4))*10 +(0xf & Hour);
		 Minute=(0xff & (m>>4))*10 +(0xf & m);
		 	Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
     HYM8563_Write_time();
	 }
		if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(Delay_count1%2)
	{
  HYM8563_Read_time();//采用写地址读数据模式
	}
	else
	{ 			HYM8563_Read_time();//采用写地址读数据模式
        Minute1=10;
  	Minute2=10;
	}
			Temp2=AT%10;  //温度的个位
      Temp1=AT/10; //温度的十位	 
    LED_Disp();
       }
    else if(key2_Num==3)
{  
	       	Temperature1_Disp=0x00;
	       Real_Temprature=1;
       	data[8]&=0xf7;
        Temperature2_Disp=0x08; 		 
	HYM8563_Read_time();//采用写地址读数据模式
			Temp2=AT%10;  //温度的个位
      Temp1=AT/10; //温度的十位		 
        if(key3_Num==1)
         {
  	keymode=0;
	key3_Num=0;
         }			
        if(key4_Num==1)
         {
	keymode=1;	
	key4_Num=0;	
         }
if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(keymode==0) 	
	{	
		if(Delay_count1%2)
	{
    Insulation_Disp=0x60;
    AntiFreeze_Disp=0x00;
    data[12]&=0xe7;
	}
	else 
	{ 
	Insulation_Disp=0x00;
  data[12]&=0x9f;
AntiFreeze_Disp=0x00;
  data[12]&=0xe7;
	}
        }
    if(keymode==1) 
     {
	if(Delay_count1%2)
	{
  Insulation_Disp=0x00;
  data[12]&=0x9f;
AntiFreeze_Disp=0x18;
	}
	else 
	{ 
	Insulation_Disp=0x00;
  data[12]&=0x9f;
AntiFreeze_Disp=0x00;
  data[12]&=0xe7;
	} 
      }
   LED_Disp();

}	
    else if(key2_Num==4)
{

  Insulation_Disp=0x00;
  data[12]&=0x9f;
AntiFreeze_Disp=0x18;
key2_flag2=0;	
			m=((Cold_Temp1<<4)|Cold_Temp2);
        if(key3_Num==1)
         {

		m=AddKey3(Cold_Temp1,Cold_Temp2);
		key3_Num=0;	
     key2_flag3=1;			 
					if(m>0x14) 
            m=0x14;						
         }			
        if(key4_Num==1)
         {
		m=ReduKey3(Cold_Temp1,Cold_Temp2);
		key4_Num=0;	
     key2_flag3=1;
					 	if(m<0x04)
            m=0x04;
         }
	
   	 
	Cold_Temp2=(m&0x0f);
  Cold_Temp1=((m>>4)&0x0f);
			Warm_Temp=(0xff & (m>>4))*10 +(0xf & m);
  HYM8563_Read_time();
      Temp2=Cold_Temp2;  //秒的个位
      Temp1=Cold_Temp1;  //秒的十位	
   LED_Disp();


}
    else if(key2_Num==5)
{  
	 
	Temperature1_Disp=0x00;
	Real_Temprature=1;
       	data[8]&=0xf7;
        Temperature2_Disp=0x08; 		 
	HYM8563_Read_time();//采用写地址读数据模式
			Temp2=AT%10;  //温度的个位
      Temp1=AT/10; //温度的十位	
        if(key3_Num==1)
         {
  	Time_mode=0;
	key3_Num=0;
         }			
        if(key4_Num==1)
         {
	Time_mode=1;	
	key4_Num=0;	
         }
if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
if(Time_mode==0) 	
	{	
if(Delay_count1%2)
	{
Time1_Disp=0x40;  				 
Time2_Disp=0x10;		 
Time3_Disp=0x00; 	
data[8]&=0x8f;
	}
	else 
	{ 
Time1_Disp=0x00;  
	data[4]&=0xbf;				 
Time2_Disp=0x00;
	data[4]&=0xef;				 
Time3_Disp=0x00; 	
	data[8]&=0x8f;
	}
        }
if(Time_mode==1) 
     {
if(Delay_count1%2)
	{
		Time1_Disp=0x00;  
	data[4]&=0xbf;			 
Time2_Disp=0x00;
	data[4]&=0xef;			 
Time3_Disp=0x70; 
	}
else 
	{ 
Time1_Disp=0x00;  
	data[4]&=0xbf;				 
Time2_Disp=0x00;
	data[4]&=0xef;				 
Time3_Disp=0x00; 	
	data[8]&=0x8f;
	} 
      }
   LED_Disp();
}
   
   else if(key2_Num==6)  
       {	
				  
//    	       Temperature1_Disp=0x00;
//       	data[8]&=0xf7;
//        Temperature2_Disp=0x00;
	//data[2]&=0xf7;
				 	Label3_Disp=0x00;  
  data[14]&=0xef;	
		if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(Delay_count1%2)
	{
	Hour1_Set=Time1_Start_Hour1;
  	Hour2_Set=Time1_Start_Hour2;
  	Minute1_Set=Time1_Start_Min1;
  	Minute2_Set=Time1_Start_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
	else
	{

	Hour1_Set=10;
  	Hour2_Set=10;
  	Minute1_Set=Time1_Start_Min1;
  	Minute2_Set=Time1_Start_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
		m=((Time1_Start_Hour1<<4)|Time1_Start_Hour2);
	 if(key3_Num==1) 
   {
		m=AddKey1(Time1_Start_Hour1,Time1_Start_Hour2);
		key3_Num=0;
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey1(Time1_Start_Hour1,Time1_Start_Hour2);
		key4_Num=0;
	 }
    Time1_Start_Hour2=(m&0x0f); 
    Time1_Start_Hour1=((m>>4)&0x0f);
	 Time1_Start_Hour=((Time1_Start_Hour1<<4)|Time1_Start_Hour2);
    LED_Set_Disp();
       } 
    else if(key2_Num==7)  
       {	
    	  if (Flash_Num>500)
					 key2_Num=0;
//				 Temperature1_Disp=0x00;
//       	data[8]&=0xf7;
//        Temperature2_Disp=0x00;
	//data[2]&=0xf7;
				 	Label3_Disp=0x00;  
  data[14]&=0xef;	
		if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(Delay_count1%2)
	{
	Hour1_Set=Time1_Start_Hour1;
  	Hour2_Set=Time1_Start_Hour2;
  	Minute1_Set=Time1_Start_Min1;
  	Minute2_Set=Time1_Start_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
	else
	{

	Hour1_Set=Time1_Start_Hour1;
  	Hour2_Set=Time1_Start_Hour2;
  	Minute1_Set=10;
  	Minute2_Set=10;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
			m=((Time1_Start_Min1<<4)|Time1_Start_Min2);
	 if(key3_Num==1) 
   {
		m=AddKey2(Time1_Start_Min1,Time1_Start_Min2);
		key3_Num=0;
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey2(Time1_Start_Min1,Time1_Start_Min2);
		key4_Num=0;
	 }
  Time1_Start_Min2=(m&0x0f);
  Time1_Start_Min1=((m>>4)&0x0f);
Time1_Start_Min=((Time1_Start_Min1<<4)|Time1_Start_Min2); 
    LED_Set_Disp();
       }
    
   else if(key2_Num==8)  
       {	
				  
//    	       Temperature1_Disp=0x00;
//       	data[8]&=0xf7;
//        Temperature2_Disp=0x00;
	//data[2]&=0xf7;
		Label3_Disp=0x00;  
  data[14]&=0xef;	
		if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(Delay_count1%2)
	{
	Hour1_Set=Time1_Stop_Hour1;
  	Hour2_Set=Time1_Stop_Hour2;
  	Minute1_Set=Time1_Stop_Min1;
  	Minute2_Set=Time1_Stop_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
	else
	{
	Hour1_Set=10;
  	Hour2_Set=10;
   	Minute1_Set=Time1_Stop_Min1;
  	Minute2_Set=Time1_Stop_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
		m=((Time1_Stop_Hour1<<4)|Time1_Stop_Hour2);
	 if(key3_Num==1) 
   {
		m=AddKey1(Time1_Stop_Hour1,Time1_Stop_Hour2);
		key3_Num=0;
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey1(Time1_Stop_Hour1,Time1_Stop_Hour2);
		key4_Num=0;
	 }
    Time1_Stop_Hour2=(m&0x0f); 
    Time1_Stop_Hour1=((m>>4)&0x0f);
	 Time1_Stop_Hour=((Time1_Stop_Hour1<<4)|Time1_Stop_Hour2);
    LED_Set_Disp();
       } 
    else if(key2_Num==9)  
       {	
				  
//    	       Temperature1_Disp=0x00;
//       	data[8]&=0xf7;
//        Temperature2_Disp=0x00;
	//data[2]&=0xf7;
	Label3_Disp=0x00;  
  data[14]&=0xef;	
		if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(Delay_count1%2)
	{
	Hour1_Set=Time1_Stop_Hour1;
  	Hour2_Set=Time1_Stop_Hour2;
  	Minute1_Set=Time1_Stop_Min1;
  	Minute2_Set=Time1_Stop_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
	else
	{
	Hour1_Set=Time1_Stop_Hour1;
  	Hour2_Set=Time1_Stop_Hour2;
  	Minute1_Set=10;
  	Minute2_Set=10;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
			m=((Time1_Stop_Min1<<4)|Time1_Stop_Min2);
	 if(key3_Num==1) 
   {
		m=AddKey2(Time1_Stop_Min1,Time1_Stop_Min2);
		key3_Num=0;
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey2(Time1_Stop_Min1,Time1_Stop_Min2);
		key4_Num=0;
	 }
  Time1_Stop_Min2=(m&0x0f);
  Time1_Stop_Min1=((m>>4)&0x0f);
Time1_Stop_Min=((Time1_Stop_Min1<<4)|Time1_Stop_Min2);	 
    LED_Set_Disp();
       }
    
   else if(key2_Num==10)  
       {	
				  
//    	   Temperature1_Disp=0x00;
//       	data[8]&=0xf7;
//        Temperature2_Disp=0x00;
	//data[2]&=0xf7;
				 	Label3_Disp=0x00;  
  data[14]&=0xef;	
		if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(Delay_count1%2)
	{
	Hour1_Set=Time2_Start_Hour1;
  	Hour2_Set=Time2_Start_Hour2;
  	Minute1_Set=Time2_Start_Min1;
  	Minute2_Set=Time2_Start_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
	else
	{
	Hour1_Set=10;
  	Hour2_Set=10;
  	Minute1_Set=Time2_Start_Min1;
  	Minute2_Set=Time2_Start_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
		m=((Time2_Start_Hour1<<4)|Time2_Start_Hour2);
	 if(key3_Num==1) 
   {
		m=AddKey1(Time2_Start_Hour1,Time2_Start_Hour2);
		key3_Num=0;
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey1(Time2_Start_Hour1,Time2_Start_Hour2);
		key4_Num=0;
	 }
    Time2_Start_Hour2=(m&0x0f); 
    Time2_Start_Hour1=((m>>4)&0x0f);
	 Time2_Start_Hour=((Time2_Start_Hour1<<4)|Time2_Start_Hour2);
    LED_Set_Disp();
       } 
    else if(key2_Num==11)  
       {	 
				  
//    	  Temperature1_Disp=0x00;
//       	data[8]&=0xf7;
//        Temperature2_Disp=0x00;
//	data[2]&=0xf7;
				 	Label3_Disp=0x00;  
  data[14]&=0xef;	
		if(Time_flag==1)
	{
        p++;
	  Time_flag=0;	
	}
Delay_count1=p/10;
	if(Delay_count1%2)
	{
	Hour1_Set=Time2_Start_Hour1;
  	Hour2_Set=Time2_Start_Hour2;
  	Minute1_Set=Time2_Start_Min1;
  	Minute2_Set=Time2_Start_Min2;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
	else
	{
	Hour1_Set=Time2_Start_Hour1;
  	Hour2_Set=Time2_Start_Hour2;
  	Minute1_Set=10;
  	Minute2_Set=10;
	Temp1_Set=Time1_Temp1;
  	Temp2_Set=Time1_Temp2;
	}
			m=((Time2_Start_Min1<<4)|Time2_Start_Min2);
	 if(key3_Num==1) 
   {
		m=AddKey2(Time2_Start_Min1,Time2_Start_Min2);
		key3_Num=0;
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey2(Time2_Start_Min1,Time2_Start_Min2);
		key4_Num=0;
	 }
  Time2_Start_Min2=(m&0x0f);
  Time2_Start_Min1=((m>>4)&0x0f);
Time2_Start_Min=((Time2_Start_Min1<<4)|Time2_Start_Min2); 
    LED_Set_Disp();
       }

			}

void Hot_Warm(void)
{
		if((ST>=AT+Temp_Diff1) && ST<=AT+Temp_Diff2)
		{				
			    power_disp(1);
		}
		if((ST>AT+Temp_Diff2) && ST<=AT+Temp_Diff3)
		{
					 power_disp(2);		    
		}	  
		if(ST>AT+Temp_Diff3)
		{
					 power_disp(3);		   
		}
	  if(ST<=AT)
		{
				 power_disp(0);		   
		}			 
}			
void All_Day_Warm(void)  //全天模式Work=0
{
	if((Work==0) && (key1_Num==1))
{ 
						Time1_Disp=0x00;  				 
						Time2_Disp=0x00;		 
						Time3_Disp=0x00; 	
			      data[8]&=0xaf;
		        data[4]&=0x5f;
						Open_Disp=0x00; 
						Close_Disp=0x00;	
						data[4]&=0xd7;
	          Fan_Flahs();	
	  m=((Warm_Temp1<<4)|Warm_Temp2);
		Warm_Temp=(0xff & (m>>4))*10 +(0xf & m);
    Hot_Warm();
}
}			
void All_Day_Cold(void)  //防冻模式Work=1
{
	AntiFreeze_Disp=0x18;

		if((Work==1) && (key1_Num==1))
		{
				m=((Cold_Temp1<<4)|Cold_Temp2);
				Cold_Temp=(0xff & (m>>4))*10 +(0xf & m);
			  if (Cold_Temp>=AT-1)
				{
         power_disp(1);
				}					
         if (Cold_Temp<AT)
				{
         power_disp(0);
				}					
		}

}			
void All_Day_Time(void)  //定时模式Work=2
{
	if((Work==2) && (key1_Num==1))
  {
			Time1_Disp=0x40;  
      Time2_Disp=0x10;
      Time3_Disp=0x70;
			data[8]&=0xaf;
		  data[4]&=0x5f;
      Open_Disp=0x00;       
      Close_Disp=0x00;
		  data[4]&=0xd7;
	 if(Time_Mode==1)
   {
			Time1_Disp=0x40;  
      Time2_Disp=0x00;
      Time3_Disp=0x00;
			data[8]&=0xaf;
		  data[4]&=0x5f;
      Open_Disp=0x20;       
      Close_Disp=0x00;
		  data[4]&=0xd7;
      Work_Time1();
	 }
	 if(Time_Mode==2)
   {
			Time1_Disp=0x00;  
      Time2_Disp=0x10;
      Time3_Disp=0x00;
			data[8]&=0xaf;
		  data[4]&=0x5f;
      Open_Disp=0x20;       
      Close_Disp=0x00;
		  data[4]&=0xd7;
      Work_Time2();
	 }
	 if(Time_Mode==3)
   {
			Time1_Disp=0x00;  
      Time2_Disp=0x00;
      Time3_Disp=0x70;
			data[8]&=0xaf;
		  data[4]&=0x5f;
      Open_Disp=0x20;       
      Close_Disp=0x00;
		  data[4]&=0xd7;
      Work_Time3();
	 }	 
	}
}
int Judgment_Time(unsigned char a1,unsigned char a2,unsigned char b1,unsigned char b2)  //判断时间
{
	u8 t;
			if(Hour>a1)
			{
	     t=1;
			}
			if(Hour==a1)
			{
        if(Minute>=b1)
			  {
	       t=1;
			  }
			}
			if(Hour>b1)
			{
	     t=0;
			}
			if(Hour==b1)
			{
        if(Minute>=b2)
			  {
	       t=0;
			  }
			}
			if(a1>b1)
			{
			  if(Hour>a1)
			  {
	       t=0;
			  }
			  if(Hour==a1)
			  {
          if(Minute>=a2)
			    {
	         t=0;
			    }
			  }
			  if(Hour>b1)
			  {
	       t=1;
			  }
			  if(Hour==b1)
			  {
          if(Minute>=b2)
			    {
	         t=1;
			    }
			  }	      
			}
			if(a1==b1)
			{
        if(a1>=b2)
			  {
			    if(Hour>a1)
			    {
	         t=0;
			    }
			    if(Hour==a1)
			    {
             if(Minute>=a2)
			      {
	           t=0;
			      }
			    }
			    if(Hour>b1)
			    {
	        t=1;
			    }
			    if(Hour==b1)
			    {
            if(Minute>=b2)
			      {
	          t=1;
			      }
			    }		      
			   }
			}
		return 	t;	
}
void Work_Time1(void)  //定时1
{
    Time1_Start_Hour=((Time1_Start_Hour1<<4)|Time1_Start_Hour2);
		Time1_Start_Min=((Time1_Start_Min1<<4)|Time1_Start_Min2);
		Time1_Stop_Hour=((Time1_Stop_Hour1<<4)|Time1_Stop_Hour2);
		Time1_Stop_Min=((Time1_Stop_Min1<<4)|Time1_Stop_Min2);
	  m=((Time1_Temp1<<4)|Time1_Temp2);
		ST=(0xff & (m>>4))*10 +(0xf & m);
    Work_Time_Flag=Judgment_Time(Time1_Start_Hour,Time1_Start_Min,Time1_Stop_Hour,Time1_Stop_Min);
    if(Work_Time_Flag==1)
    {			
			Hot_Warm();			
    }
		else
		{
     power_disp(4);//不工作
		}
}
void Work_Time2(void)  //定时2
{
    Time2_Start_Hour=((Time2_Start_Hour1<<4)|Time2_Start_Hour2);
		Time2_Start_Min=((Time2_Start_Min1<<4)|Time2_Start_Min2);
		Time2_Stop_Hour=((Time2_Stop_Hour1<<4)|Time2_Stop_Hour2);
		Time2_Stop_Min=((Time2_Stop_Min1<<4)|Time2_Stop_Min2);
	  m=((Time2_Temp1<<4)|Time2_Temp2);
		ST=(0xff & (m>>4))*10 +(0xf & m);
    Work_Time_Flag=Judgment_Time(Time2_Start_Hour,Time2_Start_Min,Time2_Stop_Hour,Time2_Stop_Min);
    if(Work_Time_Flag==1)
    {			
			Hot_Warm();			
    }
		else
		{
     power_disp(4);//不工作
		}
}
void Work_Time3(void)  //定时3
{
    Time3_Start_Hour=((Time3_Start_Hour1<<4)|Time3_Start_Hour2);
		Time3_Start_Min=((Time3_Start_Min1<<4)|Time3_Start_Min2);
		Time3_Stop_Hour=((Time3_Stop_Hour1<<4)|Time3_Stop_Hour2);
		Time3_Stop_Min=((Time3_Stop_Min1<<4)|Time3_Stop_Min2);
	 	m=((Time3_Temp1<<4)|Time3_Temp2);
		ST=(0xff & (m>>4))*10 +(0xf & m);
    Work_Time_Flag=Judgment_Time(Time3_Start_Hour,Time3_Start_Min,Time3_Stop_Hour,Time3_Stop_Min);
    if(Work_Time_Flag==1)
    {			
			Hot_Warm();			
    }
		else
		{
     power_disp(4);//不工作
		}
}

void Set_Timing_Time(void)  //设置定时时间
{


}

void Set_Temp(void)  //设置温度
{


}
void Set_System_Time(void)  //设置系统时钟
{ 
	u8 i=0,j=0;
 j=key2_Num;  
if(i==0)	
{		HYM8563_Read_time();//采用写地址读数据模式
		m=((Hour1<<4)|Hour2);
	 if(key3_Num==1) 
   {
		m=AddKey1(Hour1,Hour2);
		key3_Num=0;
		 	 		  Hour=(0xff & (m>>4))*10 +(0xf & m);
		 Minute=(0xff & (Minute>>4))*10 +(0xf & Minute);
		Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
     HYM8563_Write_time();
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey1(Hour1,Hour2);
		key4_Num=0;
		 	 		  Hour=(0xff & (m>>4))*10 +(0xf & m);
		 Minute=(0xff & (Minute>>4))*10 +(0xf & Minute);
		Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
     HYM8563_Write_time();
	 }
	 if(key2_Num>j)
	 {	i=1; }

}
if(i==1)
{
	 	HYM8563_Read_time();//采用写地址读数据模式
		m=((Minute1<<4)|Minute2);
	 if(key3_Num==1) 
   {
		m=AddKey2(Minute1,Minute2);
		key3_Num=0;
		 		 Hour=(0xff & (Hour>>4))*10 +(0xf & Hour);
		 	 		  Minute=(0xff & (m>>4))*10 +(0xf & m);
		 	Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
     HYM8563_Write_time();
	 }
	 if(key4_Num==1) 
   {	 
		m=ReduKey2(Minute1,Minute2);
		key4_Num=0;
		 Hour=(0xff & (Hour>>4))*10 +(0xf & Hour);
		 Minute=(0xff & (m>>4))*10 +(0xf & m);
		 	Seconds=(0xff & (Seconds>>4))*10 +(0xf & Seconds);
     HYM8563_Write_time();
	 }
}
	 HYM8563_Read_time();//采用写地址读数据模式
}

void Set_Time1(void)  //设置定时1
{



}

void Set_Time2(void)  //设置定时2
{



}


void Set_Time3(void)  //设置定时3
{


}
