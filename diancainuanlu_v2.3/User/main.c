#include <jansson.h>
#include "system.h"
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "exti.h"

#include "SysTick.h"
#include "usart.h"
#include "time.h"

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "led_ctrl.h"
#include "set_param.h"
#include "global.h"
#include "capture.h"
#include "mode_Relay.h"
#include "wifi.h"
#include "usart.h"

#include "stm32_flash.h"
//#include <jansson.h>
#define x3  0X08010000		//ÉèÖÃFLASH ±£´æµØÖ·(±ØÐëÎªÅ¼Êý£¬ÇÒÆäÖµÒª´óÓÚ±¾´úÂëËùÕ¼ÓÃFLASHµÄ´óÐ¡+0X08000000)
static char d;
RUN_MODE* m1; //¹Ø»úÄ£Ê½
RUN_MODE* m2 ; //È«ÌìÄ£Ê½
RUN_MODE* m3; //¶¨Ê±Ä£Ê½
RUN_MODE* m4; //·À¶³Ä£Ê½
RUN_MODE* currMode;//µ±Ç°µÄÄ£Ê½
RUN_MODE* runMode;//×îºóÖ´ÐÐµÄ¿ª»ú·¶Î§ÄÚµÄÔËÐÐÄ£Ê½


char memory[62];
char reviceData[200];

//GET_PARAM* capParam;

//ÏµÍ³³õÊ¼»¯º¯Êý
//µ±³õÊ¼»¯³É¹¦Ê±·µ»Ø0£¬·ñÔò·µ»Ø³õÊ¼»¯´íÎó´úÂ
int system_init(void) {

    //Ê±ÖÓ³õÊ¼»¯
    SysTick_Init(72);

    //ÏµÍ³ÅäÖÃ
    Systerm_Config();

    //Íâ²¿Ê±ÖÓ³õÊ¼»¯
    HYM8563_Init();

    //°´¼ü³õÊ¼»¯
    KEY_Init();

    FMQ=0;
    UJ1=0;
    UJ2=0;
    UJ3=0;
    UJ4=0;

    return 0;
}

void check_button(struct RUN_MODE** currMOde);

void wifi_receive(struct RUN_MODE* currMOde) {};

void capture(struct CAP_PARAM** capParam) ;

void Set_Wifi(void);

void wifi_init();
//void wifi_send(char* str);
void wifi_send(u16 user_id, char* str);

//void jansson_pack_test(void);

void Recv(void);
char wifiInitFlag = 0;
char wifiInitState = 0;
char wifiInitCount = 0;
char wifiSendFlag = 0;


int main()
{
    STRUCT_SET *set;

    //ÏµÍ³³õÊ¼»¯
    sysParam.initState = system_init();

    //Èç¹û³õÊ¼»¯Ê§°Ü£¬³¢ÊÔ¼ÌÐø³õÊ¼»¯
    //while(sysParam.initState) {
    //    sysParam.initState = system_init();
    //}

    //·ÖÅäÉèÖÃ½á¹¹ÄÚ´æ


    Read_Flash(x3,(u16*)&memory,62);

    /*·ÖÅäÄ£Ê½½á¹¹ÄÚ´æ*/

    //¹Ø»úÄ£Ê½
    m1 = ( RUN_MODE*)malloc(sizeof( RUN_MODE));
    m1->showLed = mode1Led;
    m1->ctlRelay = mode1Relay;
    m1->index = 1;



    //È«ÌìÄ£Ê½
    m2 = ( RUN_MODE*)malloc(sizeof( RUN_MODE));
    m2->showLed = mode2Led;
    m2->ctlRelay = mode2Relay;
    m2->index = 2;
    m2->tempetureRangMax = 80;
    m2->tempetureRangMin = 20;

    m2->runParam.Time1_Start_Hour = memory[15];
    m2->runParam.Time1_Start_Minute = memory[16];
    m2->runParam.Time1_Stop_Hour = memory[17];
    m2->runParam.Time1_Stop_Minute = memory[18];

    if(memory[19]>=m2->tempetureRangMax)
    {   memory[19]=m2->tempetureRangMax;
    }
    if(memory[19]<=m2->tempetureRangMin)
    {   memory[19]=m2->tempetureRangMin;
    }
    m2->runParam.Time1_Temp = memory[19];
    m2->setCurr = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m2->setHead = m2->setCurr;
    m2->setCurr->showLed = setTempretureLed;
    m2->setCurr->setValue = setTime1Tempreture;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m2->setCurr->next = set;
    m2->setCurr = set;
    m2->setCurr->showLed = setSysTimeHourLed;
    m2->setCurr->setValue = setSysTimeHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m2->setCurr->next = set;
    m2->setCurr = set;
    m2->setCurr->showLed = setSysTimeMinuteLed;
    m2->setCurr->setValue = setSysTimeMinute;

    m2->setCurr = NULL;

    //¶¨Ê±Ä£Ê½
    m3 = ( RUN_MODE*)malloc(sizeof( RUN_MODE));
    m3->showLed = mode3Led;
    m3->ctlRelay = mode3Relay;
    m3->index = 3;
    m3->tempetureRangMax = 80;
    m3->tempetureRangMin = 20;

    m3->runParam.Time1_Start_Hour = memory[30];
    m3->runParam.Time1_Start_Minute = memory[31];
    m3->runParam.Time1_Stop_Hour = memory[32];
    m3->runParam.Time1_Stop_Minute = memory[33];
    if(memory[34]>=m3->tempetureRangMax)
    {   memory[34]=m3->tempetureRangMax;
    }
    if(memory[34]<=m3->tempetureRangMin)
    {   memory[34]=m3->tempetureRangMin;
    }
    m3->runParam.Time1_Temp = memory[34];

    m3->runParam.Time2_Start_Hour = memory[35];
    m3->runParam.Time2_Start_Minute = memory[36];
    m3->runParam.Time2_Stop_Hour = memory[37];
    m3->runParam.Time2_Stop_Minute = memory[38];
    if(memory[39]>=m3->tempetureRangMax)
    {   memory[39]=m3->tempetureRangMax;
    }
    if(memory[39]<=m3->tempetureRangMin)
    {   memory[39]=m3->tempetureRangMin;
    }
    m3->runParam.Time2_Temp = memory[39];

    m3->runParam.Time3_Start_Hour = memory[40];
    m3->runParam.Time3_Start_Minute = memory[41];
    m3->runParam.Time3_Stop_Hour = memory[42];
    m3->runParam.Time3_Stop_Minute = memory[43];
    if(memory[44]>=m3->tempetureRangMax)
    {   memory[44]=m3->tempetureRangMax;
    }
    if(memory[44]<=m3->tempetureRangMin)
    {   memory[44]=m3->tempetureRangMin;
    }
    m3->runParam.Time3_Temp = memory[44];

    m3->setCurr = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setHead = m3->setCurr;
    m3->setCurr->showLed = setTime1OpenHourLed;
    m3->setCurr->setValue = setTime1OpenHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime1CloseHourLed;
    m3->setCurr->setValue = setTime1CloseHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime1TempretureLed;
    m3->setCurr->setValue = setTime1Tempreture;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime2OpenHourLed;
    m3->setCurr->setValue = setTime2OpenHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime2CloseHourLed;
    m3->setCurr->setValue = setTime2CloseHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime2TempretureLed;
    m3->setCurr->setValue = setTime2Tempreture;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime3OpenHourLed;
    m3->setCurr->setValue = setTime3OpenHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime3CloseHourLed;
    m3->setCurr->setValue = setTime3CloseHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setTime3TempretureLed;
    m3->setCurr->setValue = setTime3Tempreture;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setSysTimeHourLed;
    m3->setCurr->setValue = setSysTimeHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m3->setCurr->next = set;
    m3->setCurr = set;
    m3->setCurr->showLed = setSysTimeMinuteLed;
    m3->setCurr->setValue = setSysTimeMinute;

    m3->setCurr = NULL;

    //·À¶³Ä£Ê½
    m4 = ( RUN_MODE*)malloc(sizeof( RUN_MODE));
    m4->showLed = mode4Led;
    m4->ctlRelay = mode4Relay;
    m4->index = 4;
    m4->tempetureRangMax = 20;
    m4->tempetureRangMin = 5;

    m4->runParam.Time1_Start_Hour = memory[45];
    m4->runParam.Time1_Start_Minute = memory[46];
    m4->runParam.Time1_Stop_Hour = memory[47];
    m4->runParam.Time1_Stop_Minute = memory[48];
    if(memory[49]>=m4->tempetureRangMax)
    {   memory[49]=m4->tempetureRangMax;
    }
    if(memory[49]<=m4->tempetureRangMin)
    {   memory[49]=m4->tempetureRangMin;
    }
    m4->runParam.Time1_Temp = memory[49];

    m4->setCurr = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m4->setHead = m4->setCurr;
    m4->setCurr->showLed = setTempretureLed;
    m4->setCurr->setValue = setTime1Tempreture;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m4->setCurr->next = set;
    m4->setCurr = set;
    m4->setCurr->showLed = setSysTimeHourLed;
    m4->setCurr->setValue = setSysTimeHour;

    set = ( STRUCT_SET*)malloc(sizeof( STRUCT_SET));
    m4->setCurr->next = set;
    m4->setCurr = set;
    m4->setCurr->showLed = setSysTimeMinuteLed;
    m4->setCurr->setValue = setSysTimeMinute;

    m4->setCurr = NULL;

    //Ä£Ê½Á´±íµÄ¹¹Ôì³õÊ¼»¯
    //m2->prev = m4;
    m2->next = m3;
    //m3->prev = m2;
    m3->next = m4;
    //m4->prev = m3;
    m4->next = m2;

    //m1->prev = m1;
    m1->next = m1;

    //³õÊ¼»¯µ±Ç°Ä£Ê½
    //³õÊ¼µÄÔËÐÐÄ£Ê½ÐèÒªµô¼ÇÒä»Ö¸´ ÍõÅô
    //Read_Flash(x3 + 2048*4,(u16*)&x1,sizeof(char));
    switch(memory[60]) {
    case 1: {
        currMode = m1;
        break;
    }
    case 2: {
        currMode = m2;
        break;
    }
    case 3: {
        currMode = m3;
        break;
    }
    case 4: {
        currMode = m4;
        break;
    }
    }

    if(currMode == NULL) {
        currMode = m1;
    }

    switch(memory[61]) {
    case 2: {
        runMode = m2;
        break;
    }
    case 3: {
        runMode = m3;
        break;
    }
    case 4: {
        runMode = m4;
        break;
    }
    }

    if(runMode == NULL) {
        runMode = m2;
    }

    sysParam.beep = 0;

    sysParam.setTouch = 0;

    sysParam.cycle = 10;

    while(1) {

        //°´¼ü¼ì²éº¯Êý
        check_button(&currMode);

        if( sysParam.cycle > sysParam.setTouch + 5000 && sysParam.setTouch > 0) {
            currMode->setCurr = NULL;
            sysParam.setTouch = 0;
        }

        //¶ÁÈ¡ÏµÍ³Ê±¼ä
        HYM8563_Read_time();

        if(wifiInitState == 0) {
            wifi_init();
        } else {
            char* s_repon = NULL;

            json_t *root1;
            u16 num0,num1,num2,num3,num4,num5,num6,num7,num8,num9,num10,num11,num12,num13;

            num0= currMode->runParam.Time1_Start_Hour*60+currMode->runParam.Time1_Start_Minute;
            num1= currMode->runParam.Time1_Stop_Hour*60+currMode->runParam.Time1_Stop_Minute;
            num2=currMode->runParam.Time1_Temp;
            num3= currMode->runParam.Time2_Start_Hour*60+currMode->runParam.Time2_Start_Minute;
            num4= currMode->runParam.Time2_Stop_Hour*60+currMode->runParam.Time2_Stop_Minute;
            num5=currMode->runParam.Time2_Temp;
            num6= currMode->runParam.Time3_Start_Hour*60+currMode->runParam.Time3_Start_Minute;
            num7= currMode->runParam.Time3_Stop_Hour*60+currMode->runParam.Time3_Stop_Minute;
            num8=currMode->runParam.Time3_Temp;
            num9=(sysParam.Hour_High*10+sysParam.Hour_Low)*60+(sysParam.Minute_High*10+sysParam.Minute_Low);
            num10=capParam.temperature;
            num11=workState.isHot;
            num12=workState.isInsulation;
            num13=workState.isFan;

            root1 = json_object();


            json_object_set_new(root1,"Fan",json_integer(num13));
            json_object_set_new(root1,"Insulation",json_integer(num12));
            json_object_set_new(root1,"Hot",json_integer(num11));
            json_object_set_new(root1,"CapTemp",json_integer(num10));
            json_object_set_new(root1,"Systime",json_integer(num9));
            json_object_set_new(root1,"T3Temp",json_integer(num8));
            json_object_set_new(root1,"T3Stop",json_integer(num7));
            json_object_set_new(root1,"T3Start",json_integer(num6));
            json_object_set_new(root1,"T2Temp",json_integer(num5));
            json_object_set_new(root1,"T2Stop",json_integer(num4));
            json_object_set_new(root1,"T2Start",json_integer(num3));
            json_object_set_new(root1,"T1Temp",json_integer(num2));
            json_object_set_new(root1,"T1Stop",json_integer(num1));
            json_object_set_new(root1,"T1Start",json_integer(num0));
            json_object_set_new(root1,"mode",json_integer(currMode->index));
            //json_object_set_new(root1,"root1",item);

            s_repon = json_dumps(root1, JSON_INDENT(0));
            wifi_send(0,s_repon);
            free(s_repon);
            json_decref(root1);
        }

        Recv();

        //²É¼¯Êý¾Ý
        if(sysParam.Seconds % 2 == 0) {
            Get_Temputure();
        }

        //¼ÌµçÆ÷¿ØÖÆ
        currMode->ctlRelay(currMode);

        //ÊýÂë¹ÜÏÔÊ¾
        currMode->showLed(currMode);
        sysParam.cycle++;
    }
}

void mode_exchange(int m) {
    if(m == 1) {
        currMode = runMode;
        currMode->setCurr=NULL;
        memory[60] = currMode->index;
        memory[61] = runMode->index;
        Write_Flash(x3, (u16*)&memory,62);
    }

    if(m == 0) {
        currMode = m1;
        memory[60] = currMode->index;
        memory[61] = runMode->index;
        Write_Flash(x3, (u16*)&memory,62);
    }

    if(m == 2) {
        currMode = m2;
        currMode->setCurr = NULL;
        runMode = currMode;
        memory[60] = currMode->index;
        memory[61] = (runMode)->index;
        Write_Flash(x3, (u16*)&memory,62);
    }

    if(m == 3) {
        currMode = m3;
        currMode->setCurr = NULL;
        runMode = currMode;
        memory[60] = currMode->index;
        memory[61] = (runMode)->index;
        Write_Flash(x3, (u16*)&memory,62);
    }

    if(m == 4) {
        currMode = m4;
        currMode->setCurr = NULL;
        runMode = currMode;
        memory[60] = currMode->index;
        memory[61] = (runMode)->index;
        Write_Flash(x3, (u16*)&memory,62);
    }
}


void check_button(RUN_MODE** currMode) {

    if(buttonState.clickCount>0) {

        switch(buttonState.keyNum) {

        case 1: {
            if(*currMode == m1) {
                mode_exchange(1);
            } else {
                mode_exchange(0);
            }
            break;
        }

        case 2: {
            if((*currMode) != m1) {
                if((*currMode)->setCurr == NULL) {
                    (*currMode)->setCurr = (*currMode)->setHead;
                } else {
                    (*currMode)->setCurr = (*currMode)->setCurr->next;
                }
            }

            sysParam.setTouch = sysParam.cycle;
            break;
        }

        case 3: {
            if((*currMode) != m1) {
                if((*currMode)->setCurr != NULL) {
                    (*currMode)->setCurr->setValue((*currMode),-1);
                }
            }

            sysParam.setTouch = sysParam.cycle;

            memory[((*currMode)->index - 1) * 15] = (*currMode)->runParam.Time1_Start_Hour;
            memory[((*currMode)->index - 1) * 15 + 1] = (*currMode)->runParam.Time1_Start_Minute;
            memory[((*currMode)->index - 1) * 15 + 2] = (*currMode)->runParam.Time1_Stop_Hour;
            memory[((*currMode)->index - 1) * 15 + 3] = (*currMode)->runParam.Time1_Stop_Minute;
            memory[((*currMode)->index - 1) * 15 + 4] = (*currMode)->runParam.Time1_Temp;

            memory[((*currMode)->index - 1) * 15 + 5] = (*currMode)->runParam.Time2_Start_Hour;
            memory[((*currMode)->index - 1) * 15 + 6] = (*currMode)->runParam.Time2_Start_Minute;
            memory[((*currMode)->index - 1) * 15 + 7] = (*currMode)->runParam.Time2_Stop_Hour;
            memory[((*currMode)->index - 1) * 15 + 8] = (*currMode)->runParam.Time2_Stop_Minute;
            memory[((*currMode)->index - 1) * 15 + 9] = (*currMode)->runParam.Time2_Temp;

            memory[((*currMode)->index - 1) * 15 + 10] = (*currMode)->runParam.Time3_Start_Hour;
            memory[((*currMode)->index - 1) * 15 + 11] = (*currMode)->runParam.Time3_Start_Minute;
            memory[((*currMode)->index - 1) * 15 + 12] = (*currMode)->runParam.Time3_Stop_Hour;
            memory[((*currMode)->index - 1) * 15 + 13] = (*currMode)->runParam.Time3_Stop_Minute;
            memory[((*currMode)->index - 1) * 15 + 14] = (*currMode)->runParam.Time3_Temp;

            Write_Flash(x3, (u16*)&memory,62);

            break;
        }

        case 4: {
            if((*currMode) != m1) {
                if((*currMode)->setCurr != NULL) {
                    (*currMode)->setCurr->setValue((*currMode),1);
                }
            }

            sysParam.setTouch = sysParam.cycle;


            memory[((*currMode)->index - 1) * 15] = (*currMode)->runParam.Time1_Start_Hour;
            memory[((*currMode)->index - 1) * 15 + 1] = (*currMode)->runParam.Time1_Start_Minute;
            memory[((*currMode)->index - 1) * 15 + 2] = (*currMode)->runParam.Time1_Stop_Hour;
            memory[((*currMode)->index - 1) * 15 + 3] = (*currMode)->runParam.Time1_Stop_Minute;
            memory[((*currMode)->index - 1) * 15 + 4] = (*currMode)->runParam.Time1_Temp;

            memory[((*currMode)->index - 1) * 15 + 5] = (*currMode)->runParam.Time2_Start_Hour;
            memory[((*currMode)->index - 1) * 15 + 6] = (*currMode)->runParam.Time2_Start_Minute;
            memory[((*currMode)->index - 1) * 15 + 7] = (*currMode)->runParam.Time2_Stop_Hour;
            memory[((*currMode)->index - 1) * 15 + 8] = (*currMode)->runParam.Time2_Stop_Minute;
            memory[((*currMode)->index - 1) * 15 + 9] = (*currMode)->runParam.Time2_Temp;

            memory[((*currMode)->index - 1) * 15 + 10] = (*currMode)->runParam.Time3_Start_Hour;
            memory[((*currMode)->index - 1) * 15 + 11] = (*currMode)->runParam.Time3_Start_Minute;
            memory[((*currMode)->index - 1) * 15 + 12] = (*currMode)->runParam.Time3_Stop_Hour;
            memory[((*currMode)->index - 1) * 15 + 13] = (*currMode)->runParam.Time3_Stop_Minute;
            memory[((*currMode)->index - 1) * 15 + 14] = (*currMode)->runParam.Time3_Temp;

            Write_Flash(x3, (u16*)&memory,62);

            break;
        }

        case 5: {
            if((*currMode) != m1) {
                mode_exchange((*currMode)->next->index);
                //wifi_send(0,"abcdefghijklmnopqrstuvwxyz");
            }


            break;
        }

        }

        buttonState.clickCount = 0;
        sysParam.beep = sysParam.cycle;
    }
}

void wifi_init() {
    char* b;

    switch(wifiInitFlag) {
    case 0: {
        CLR_Buf1();
        wifiInitFlag = 1;
        break;
    }
    case 1: {
        if(!Find("OK") ) {
            b = Set_Mode;
            if(Send_Again == 1)
            {
                for (; *b!='\0'; b++)
                {
                    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
                    USART_SendData(USART1,*b);
                }
                UART1_SendLR();
                Send_Again=0;
            }

        } else {
            if(wifiInitCount < 3) {
                wifiInitCount++;
            } else {
                wifiInitFlag = 2;
                CLR_Buf1();
                wifiInitCount = 0;
            }

        }
        break;
    }
    case 2: {
        if(!Find("version")) {
            b = RST;
            if(Send_Again == 1)
            {
                for (; *b!='\0'; b++)
                {
                    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
                    USART_SendData(USART1,*b);
                }
                UART1_SendLR();
                Send_Again=0;
            }
        } else {
            if(wifiInitCount < 3) {
                wifiInitCount++;
            } else {
                wifiInitFlag = 3;
                CLR_Buf1();
                wifiInitCount = 0;
            }
        }
        break;
    }
    case 3: {
        if(!Find("OK")) {
            b = Set_Name;
            if(Send_Again == 1)
            {
                for (; *b!='\0'; b++)
                {
                    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
                    USART_SendData(USART1,*b);
                }
                UART1_SendLR();
                Send_Again=0;
            }
        } else {
            if(wifiInitCount < 3) {
                wifiInitCount++;
            } else {
                wifiInitFlag = 4;
                CLR_Buf1();
                wifiInitCount = 0;
            }
        }
        break;
    }
    case 4: {
        if(!Find("OK")) {
            b = Set_Parameter;
            if(Send_Again == 1)
            {
                for (; *b!='\0'; b++)
                {
                    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
                    USART_SendData(USART1,*b);
                }
                UART1_SendLR();
                Send_Again=0;
            }
        } else {
            if(wifiInitCount < 3) {
                wifiInitCount++;
            } else {
                wifiInitFlag = 5;
                CLR_Buf1();
                wifiInitCount = 0;
            }
        }
        break;
    }
    case 5: {

        if(!Find("OK")) {
            b = Mult_Mode;
            if(Send_Again == 1)
            {
                for (; *b!='\0'; b++)
                {
                    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
                    USART_SendData(USART1,*b);
                }
                UART1_SendLR();
                Send_Again=0;
            }
        } else {
            if(wifiInitCount < 3) {
                wifiInitCount++;
            } else {
                wifiInitFlag = 6;
                CLR_Buf1();
                wifiInitCount = 0;
            }
        }
        break;
    }
    case 6: {

        if(!Find("OK")) {
            b = Open_Server;
            if(Send_Again == 1)
            {
                for (; *b!='\0'; b++)
                {
                    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
                    USART_SendData(USART1,*b);
                }
                UART1_SendLR();
                Send_Again=0;
            }
        } else {
            if(wifiInitCount < 3) {
                wifiInitCount++;
            } else {
                wifiInitFlag = 7;
                wifiInitState = 1;
                CLR_Buf1();
                wifiInitCount = 0;
            }
        }
        break;
    }
    }
}

void wifi_send(u16 user_id, char* str)
{
    u16 len;
    u8 i=0;
    u16 index = 0;
	u16 temp_datalen;
    char temp[20]= {0};
    char user_id_str[2]= {0};
    char * len_str;
    len = strlen(str);
		temp_datalen = len;
		while(temp_datalen /= 10)
		{
		   index ++;
		}
		index = index + 13;
    user_id_str[0] = user_id + 0x30;
    user_id_str[1] = 0x00;
    strcat(temp,"AT+CIPSEND=");
    strcat(temp,user_id_str);
    strcat(temp,",");
    do {
        switch(len % 10) {
        case 0: {
            temp[index] = '0';
            break;
        }
        case 1: {
            temp[index] = '1';
            break;
        }
        case 2: {
            temp[index] = '2';
            break;
        }
        case 3: {
            temp[index] = '3';
            break;
        }
        case 4: {
            temp[index] = '4';
            break;
        }
        case 5: {
            temp[index] = '5';
            break;
        }
        case 6: {
            temp[index] = '6';
            break;
        }
        case 7: {
            temp[index] = '7';
            break;
        }
        case 8: {
            temp[index] = '8';
            break;
        }
        case 9: {
            temp[index] = '9';
            break;
        }
        }
        len = len / 10;
        index--;
    } while(len>0);

    CLR_Buf1();
    for (; i<strlen(temp); i++)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
        USART_SendData(USART1,temp[i]);
    }
    UART1_SendLR();
    Send_Again = 0;
    while(!Find(">"))
    {
        if(Send_Again == 1)
        {
            break;
        }
        if(Find("ERROR"))
        {
					CLR_Buf1();
            return;
        }
    }
    i = 0;
    for (; i<strlen(str); i++)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
        USART_SendData(USART1,str[i]);
    }
    CLR_Buf1();
}


void Recv(void)
{
    if(Data_ok == 1)
    {
        int i = 0;
        char code;
        json_t* root;
        json_error_t err;


        for(; i<Data_len; i++) {
            reviceData[i] = Data[i];
        }
        for(; i < 200; i++) {
            reviceData[i] = 0;
        }



        root = json_loads(&reviceData[0], Data_len, &err);

        //root = json_loads(str, 39, &err);

        if(NULL != root && json_is_object(root))
        {
            json_t* func = json_object_get(root, "func");
            if(NULL != func && json_is_integer(func))
            {
                code = json_integer_value(func);
                //BSP_LED_On(json_real_value(led));
                if(code < 5) {
                    mode_exchange(code);
                }
                if(code == 5) {
                    RUN_MODE *rm;
                    json_t* mode =json_object_get(root, "mode");
                    if(NULL != mode && json_is_integer(mode))
                    {
                        code = json_integer_value(mode);
                        switch(code) {
                        case 2: {

                            rm = m2;
                            break;
                        }
                        case 3: {
                            rm = m3;
                            break;
                        }
                        case 4: {
                            rm = m4;
                            break;
                        }
                        case 5: {
                            json_t* param =json_object_get(root, "param");
                            if(NULL != param && json_is_integer(param))
                            {
                                code = json_integer_value(param);
                                if(code==0) {
                                    json_t* value =json_object_get(root, "value");
                                    code = json_integer_value(value);
                                    sysParam.Hour=code/60;
                                    sysParam.Minute=code%60;
                                    Hour=(0xff & (sysParam.Hour>>4))*10 +(0xf & sysParam.Hour);
                                    Minute=(0xff & (sysParam.Minute>>4))*10 +(0xf & sysParam.Minute);
                                    HYM8563_Write_time();
                                }
                            }
                        }
                        }
                    }

                    if(rm != NULL) {


                        json_t* param =json_object_get(root, "param");
                        code = -1;
                        if(NULL != param && json_is_integer(param))
                        {
                            code = json_integer_value(param);

                        }

                        switch(code) {
                        case 0:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time1_Start_Hour=code/60;
                            rm->runParam.Time1_Start_Minute=code%60;
                            break;
                        }
                        case 1:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time1_Stop_Hour=code/60;
                            rm->runParam.Time1_Stop_Minute=code%60;
                            break;
                        }
                        case 2:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time1_Temp=code;
                            break;
                        }
                        case 3:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time2_Start_Hour=code/60;
                            rm->runParam.Time2_Start_Minute=code%60;
                            break;
                        }
                        case 4:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time2_Stop_Hour=code/60;
                            rm->runParam.Time2_Stop_Minute=code%60;
                            break;
                        }
                        case 5:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time2_Temp=code;
                            break;
                        }
                        case 6:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time3_Start_Hour=code/60;
                            rm->runParam.Time3_Start_Minute=code%60;
                            break;
                        }
                        case 7:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time3_Stop_Hour=code/60;
                            rm->runParam.Time3_Stop_Minute=code%60;
                            break;
                        }
                        case 8:
                        {
                            json_t* value =json_object_get(root, "value");
                            code = json_integer_value(value);
                            rm->runParam.Time3_Temp=code;
                            break;
                        }

                        }
                    }
                }




            }
        }
        json_decref(root);
        Data_ok =0;
    }
}