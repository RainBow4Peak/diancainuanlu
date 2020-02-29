#include "capture.h"
#include  "adc.h"

u16 value=0;
float vol1;
float vol2;
u8 j;

//温度电阻的线性阻值
float TR[100]= {162.3,154.3,146.7,139.6,132.8,126.4,120.4,114.7,109.3,104.1,
                99.3,94.6,90.3,86.1,82.2,78.5,74.9,71.6,68.4,65.3,
                62.4,59.7,57.1,54.6,52.2,50.0,47.9,45.8,43.9,42.0,
                40.3,38.6,37.0,35.5,34.0,32.6,31.3,30.1,28.9,27.7,
                26.6,25.6,24.5,23.6,22.7,21.8,21.0,20.1,19.4,18.6,
                17.9,17.3,16.6,16.0,15.4,14.8,14.3,13.8,13.3,12.8,
                12.3,11.9,11.5,11.1,10.7,10.3,9.9,9.6,9.3,8.9,
                8.6,8.3,8.1,7.9,7.5,7.3,7.0,6.8,6.6,6.3,
                6.1,5.9,5.7,5.6,5.4,5.2,5.0,4.9,4.7,4.6,
                4.4,4.3,4.2,4.0,3.9,3.8,3.7,3.6,3.5,3.3
               };

#define temp_len  30
u16 temp_history[temp_len];	
char temp_count = 0;							 
char i;			
u16 temp_total;							 
					 
							 

//温度采集函数
void Get_Temputure(void)
{
    value=Get_ADC_Value(ADC_Channel_0,20);
    vol1=(float)(value*(3.3/4096));
    vol2=(float)(47*(vol1/(5.0-vol1)));

    for(j=0; j<=100&&TR[j]>=vol2; j++);
	
	

    if(TR[j]<=vol2){
			for(i = 0; i < temp_len - 1; i++){
				temp_history[i] = temp_history[i+1];
			}
			temp_history[temp_len-1] = j;
			temp_count++;
			if(temp_count > temp_len){
				temp_count = temp_len;
			}
			
			temp_total = 0;
			for(i = 0; i < temp_count; i++){
				temp_total += temp_history[temp_len - i - 1];
			}
			
			capParam.temperature = temp_total / temp_count;
		}
			
        
}