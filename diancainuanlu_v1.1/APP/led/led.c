#include "led.h"
#include "key.h"

u8 m;
u8 key1_Num=0,key2_Num,key3_Num=0,key4_Num=0,key5_Num=0;
unsigned char n;

unsigned char Time1_Start_Hour,Time1_Start_Min,Time1_Stop_Hour,Time1_Stop_Min,Time1_Temp;
unsigned char Time2_Start_Hour,Time2_Start_Min,Time2_Stop_Hour,Time2_Stop_Min,Time2_Temp;
unsigned char Time3_Start_Hour,Time3_Start_Min,Time3_Stop_Hour,Time3_Stop_Min,Time3_Temp;

unsigned char Time1_Start_Hour1=0,Time1_Start_Min1=0,Time1_Stop_Hour1=0,Time1_Stop_Min1=3,Time1_Temp1=1; 
unsigned char Time1_Start_Hour2=7,Time1_Start_Min2=0,Time1_Stop_Hour2=9,Time1_Stop_Min2=0,Time1_Temp2=5;  
unsigned char Time2_Start_Hour1=0,Time2_Start_Min1=0,Time2_Stop_Hour1=0,Time2_Stop_Min1=3,Time2_Temp1=1; 
unsigned char Time2_Start_Hour2=7,Time2_Start_Min2=0,Time2_Stop_Hour2=9,Time2_Stop_Min2=0,Time2_Temp2=5;  
unsigned char Time3_Start_Hour1=0,Time3_Start_Min1=0,Time3_Stop_Hour1=0,Time3_Stop_Min1=3,Time3_Temp1=1; 
unsigned char Time3_Start_Hour2=7,Time3_Start_Min2=0,Time3_Stop_Hour2=9,Time3_Stop_Min2=0,Time3_Temp2=5;

unsigned char Warm_Temp,Warm_Temp1=4,Warm_Temp2=0;
unsigned char Cold_Temp,Cold_Temp1=0,Cold_Temp2=6;
unsigned char Temp1,Temp2;
	
unsigned char Hour1_Set,Hour2_Set,Minute1_Set,Minute2_Set,Temp1_Set,Temp2_Set;

 void delay(unsigned int xms)   
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=110;y>0;y--);
}
/*******************************************************************************
* 函 数 名         : GPIO_Init1
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void GPIO_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_10|GPIO_Pin_11;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* 初始化GPIO */

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //选择你要设置的IO口
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	 //设置模式
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
//	GPIO_Init(GPIOA,&GPIO_InitStructure); 	
	
	PBout(12)=1;   //将LED端口拉高，熄灭所有LED
	PBout(13)=1; 
	PBout(14)=1; 
	PBout(15)=1; 
	
}

/*******************************************************************************
* 函 数 名         : indate
* 函数功能		       : LED数据显示
* 输    入         : 需要显示的数据
* 输    出         : 无
*******************************************************************************/
 void indate(unsigned char p)
{
  unsigned int i;	 
  STB=0;	
 	for(i=0;i<8;i++)
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
* 函 数 名         : display
* 函数功能		       : LED数据显示
* 输    入         : 需要显示的数据
* 输    出         : 无
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

	for(i=0;i<datacount;i++)
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
void LED_Init(void)
{
Time1_Disp=0x40;  
Time2_Disp=0x10;
Time3_Disp=0x70;
Power_Disp=0x70;
Open_Disp=0x20;       
Close_Disp=0x08;
Fan1_Disp=0xf0;
Fan2_Disp=0x3f; //???????
Watt0_Disp=0x20;
Watt1_Disp=0x18;
Watt2_Disp=0x07;  
Watt3_Disp=0xe0;
Label1_Disp=0x60;
Label2_Disp=0x18;
Label3_Disp=0x10;  //??C 
Temperature1_Disp=0x08;
Temperature2_Disp=0x08;
Hot_Disp=0x18;
Insulation_Disp=0x60;
AntiFreeze_Disp=0x18; 
FaultDisp=0x60;
Key1_Disp=0x01; 
Key2_Disp=0x01; 
Key3_Disp=0x01; 
Key4_Disp=0x01; 
Key5_Disp=0x01;
}	

 
void LED_Disp(void)
{
	unsigned char i;  //??

data[0]=data[0]|Watt3_Disp|Hot_Disp|Key5_Disp;
data[1]=data[1]|Watt0_Disp|Watt1_Disp|Watt2_Disp;
data[2]=data[2]|Fan1_Disp|Temperature2_Disp|Key1_Disp;
data[3]=data[3]|Fan2_Disp;
Hour1=Hour1*2; //Hour1_Disp=0x80;
data[4]=data[4]|Dec_Hex[Hour1+1]|Time1_Disp|Open_Disp|Close_Disp|Time2_Disp|Key2_Disp;
data[5]=data[5]|Dec_Hex[Hour1];  //Hour1	
Hour2=Hour2*2;  //Hour2_Disp=0x80;  
data[6]=data[6]|Dec_Hex[Hour2+1]|Label1_Disp|Label2_Disp|Key3_Disp;   
data[7]=data[7]|Dec_Hex[Hour2]; //Hour2
Minute1=Minute1*2; //Minute1_Disp=0x80; 
data[8]=data[8]|Dec_Hex[Minute1+1]|Time3_Disp|Temperature1_Disp|Key4_Disp;
data[9]=data[9]|Dec_Hex[Minute1] ;//Minute1
Minute2=Minute2*2; //Minute2_Disp=0x80;
data[10]=data[10]|Dec_Hex[Minute2+1]|Power_Disp;
data[11]=data[11]|Dec_Hex[Minute2];  //Minute2
Temp1=Temp1*2;     //Temperature1_Digital=0x80; Temp1,Temp2
data[12]=data[12]|Dec_Hex[Temp1+1]|Insulation_Disp|AntiFreeze_Disp;
data[13]=data[13]|Dec_Hex[Temp1]; //Temperature2_Digital
Temp2=Temp2*2;   //Temperature2_Digital=0x80;  
data[14]=data[14]|Dec_Hex[Temp2+1]|FaultDisp|Label3_Disp;
data[15]=data[15]|Dec_Hex[Temp2]; //Temperature2_Digital

for(i=0;i<16;i++)
display2(HYM8563_Address[i],data[i]);
 data[4]&= 0x7f;
 data[5]&= 0xc0;
 data[6]&= 0x7f;
 data[7]&= 0xc0;
 data[8]&= 0x7f;
 data[9]&= 0xc0;
 data[10]&= 0x7f;
 data[11]&= 0xc0;
 data[12]&= 0x7f;
 data[13]&= 0xc0;
 data[14]&= 0x7f;
 data[15]&= 0xc0;
}

void LED_Set_Disp(void)
{
	unsigned char i;  //??

data[0]=data[0]|Watt3_Disp|Hot_Disp|Key5_Disp;
data[1]=data[1]|Watt0_Disp|Watt1_Disp|Watt2_Disp;
data[2]=data[2]|Fan1_Disp|Temperature2_Disp|Key1_Disp;
data[3]=data[3]|Fan2_Disp;
Hour1_Set=Hour1_Set*2; //Hour1_Disp=0x80;
data[4]=data[4]|Dec_Hex[Hour1_Set+1]|Time1_Disp|Open_Disp|Close_Disp|Time2_Disp|Key2_Disp;
data[5]=data[5]|Dec_Hex[Hour1_Set];  //Hour1	
Hour2_Set=Hour2_Set*2;  //Hour2_Disp=0x80;  
data[6]=data[6]|Dec_Hex[Hour2_Set+1]|Label1_Disp|Label2_Disp|Key3_Disp;   
data[7]=data[7]|Dec_Hex[Hour2_Set]; //Hour2
Minute1_Set=Minute1_Set*2; //Minute1_Disp=0x80; 
data[8]=data[8]|Dec_Hex[Minute1_Set+1]|Time3_Disp|Temperature1_Disp|Key4_Disp;
data[9]=data[9]|Dec_Hex[Minute1_Set] ;//Minute1
Minute2_Set=Minute2_Set*2; //Minute2_Disp=0x80;
data[10]=data[10]|Dec_Hex[Minute2_Set+1]|Power_Disp;
data[11]=data[11]|Dec_Hex[Minute2_Set];  //Minute2
Temp1_Set=Temp1_Set*2;     //Temperature1_Digital=0x80; Temp1_Set,Temp2_Set,
data[12]=data[12]|Dec_Hex[Temp1_Set+1]|Insulation_Disp|AntiFreeze_Disp;
data[13]=data[13]|Dec_Hex[Temp1_Set]; //Temperature2_Digital
Temp2_Set=Temp2_Set*2;   //Temperature2_Digital=0x80;  
data[14]=data[14]|Dec_Hex[Temp2_Set+1]|FaultDisp|Label3_Disp;
data[15]=data[15]|Dec_Hex[Temp2_Set]; //Temperature2_Digital

for(i=0;i<16;i++)
display2(HYM8563_Address[i],data[i]);
 data[4]&= 0x7f;
 data[5]&= 0xc0;
 data[6]&= 0x7f;
 data[7]&= 0xc0;
 data[8]&= 0x7f;
 data[9]&= 0xc0;
 data[10]&= 0x7f;
 data[11]&= 0xc0;
 data[12]&= 0x7f;
 data[13]&= 0xc0;
 data[14]&= 0x7f;
 data[15]&= 0xc0;
}
 //?????????
int AddKey1(unsigned char a1,unsigned char a2){
	       if(a2<9) 
         { a2++;}
         else
           {
           a1++;
           a2=0;
           }
         if((a1>=2)&&(a2>=4))
          { 
           a1=0;
           a2=0;
          }
					n=((a1<<4)|a2);
			return 	n;	
}
int AddKey2(unsigned char a1,unsigned char a2){ 
	       if(a2<9) 
          a2++;
         else
           {
           a1++;
           a2=0;
           }
         if ((a1>=6)&&(a2==0))
          { 
           a1=0;
           a2=0;
          }
					n=((a1<<4)|a2);
					return	n;
}
int AddKey3(unsigned char a1,unsigned char a2){
	       if(a2<9) 
          a2++;
         else
           {
           a1++;
           a2=0;
           }
         if ((a1>=9)&&(a2>=9))
          { 
           a1=0;
           a2=0;
          }
			n=((a1<<4)|a2);
					return	n;
		 						
}
//?????????
int ReduKey1(unsigned char a1,unsigned char a2){
        if ((a1==0)&&(a2==0))
          { 
           a1=2;
           a2=4;
          }
       	if(a2>0) 
          a2--;
         else
           {
           a1--;
           a2=9;
           }
			n=((a1<<4)|a2);
			return 	n;	
}
int ReduKey2(unsigned char a1,unsigned char a2){
         if ((a1==0)&&(a2==0))
          { 
           a1=6;
           a2=0;
          }
       	if(a2>0) 
          a2--;
         else
           {
           a1--;
           a2=9;
           }
			n=((a1<<4)|a2);
			return 	n;						
}
int ReduKey3(unsigned char a1,unsigned char a2){
         if((a1<=0)&&(a2<=0))
          { 
           a1=9;
           a2=9;
          }	       
	       if(a2>0) 
          a2--;
         else
           {
           a1--;
           a2=9;
           }
			n=((a1<<4)|a2);
			return 	n;	
}


/*******************************************************************************
* 函 数 名         : Key_Control
* 函数功能		       : key控制
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
//void Key_Control()
//{ 

//}

void power_disp(u8 Num)
{
	switch(Num)
	{
		case 0:
			 Watt0_Disp=0x00;
					Watt1_Disp=0x00;
			    Watt2_Disp=0x00;
			    Watt3_Disp=0x00;
	       	Hot_Disp=0x00;
          Insulation_Disp=0x00;
			    data[0]&=0x07;
					data[1]&=0xc0;
		      data[12]&=0x9f;
			    data[0]&=0x1f;
					data[1]&=0xc0;
			UJ2=0;UJ3=0;UJ4=0;
      break;
		case 1:
          Watt0_Disp=0x20;
					Watt1_Disp=0x18;
			    Watt2_Disp=0x00;
			    Watt3_Disp=0x00;
		      Hot_Disp=0x18;
          Insulation_Disp=0x00;
			    data[0]&=0x07;
					data[1]&=0xc0;
		      data[12]&=0x9f;
			UJ2=1;UJ3=0;UJ4=0;
		      break;
		case 2:
          Watt0_Disp=0x20;
					Watt1_Disp=0x18;
			    Watt2_Disp=0x07;
			    Watt3_Disp=0x00;
		     Hot_Disp=0x18;
          Insulation_Disp=0x00;
			    data[0]&=0x07;
					data[1]&=0xc0;
		      data[12]&=0x9f;
			UJ2=1;UJ3=1;UJ4=0;
		  break;
		case 3:   
          Watt0_Disp=0x20;
					Watt1_Disp=0x18;
			    Watt2_Disp=0x07;
			    Watt3_Disp=0xE0;
	       	Hot_Disp=0x18;
          Insulation_Disp=0x00;
			    data[0]&=0x07;
					data[1]&=0xc0;
		      data[12]&=0x9f;
			    data[0]&=0x1f;
					data[1]&=0xc0;
			UJ2=1;UJ3=1;UJ4=1;
		  break;
		case 4:   
         Watt0_Disp=0x00;
					Watt1_Disp=0x00;
			    Watt2_Disp=0x00;
			    Watt3_Disp=0x00;
		      Hot_Disp=0x00;
          Insulation_Disp=0x60;
			    data[0]&=0x07;
					data[1]&=0xc0;
		      data[12]&=0x9f;
		      UJ2=0;UJ3=0;UJ4=0;
		      break;
	}	  
}
