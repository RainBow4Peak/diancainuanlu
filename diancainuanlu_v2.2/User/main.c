//#include <jansson.h>
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

#define x3  0X08010000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
static char d;
RUN_MODE* m1; //关机模式
RUN_MODE* m2 ; //全天模式
RUN_MODE* m3; //定时模式
RUN_MODE* m4; //防冻模式
RUN_MODE* currMode;//当前的模式
RUN_MODE* runMode;//最后执行的开机范围内的运行模式

char memory[62];
char reviceData[200];

//系统初始化函数
//当初始化成功时返回0，否则返回初始化错误代�
int system_init(void) {

    //时钟初始化
    SysTick_Init(72);

    //系统配置
    Systerm_Config();

    //外部时钟初始化
    HYM8563_Init();

    //按键初始化
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

void wifi_send(u16 user_id, char* str);

//void Recv(void);
char wifiInitFlag = 0;
char wifiInitState = 0;
char wifiInitCount = 0;
char wifiSendFlag = 0;

//char* s_repon;
//json_t *root1  ;
//u16 num;

//json_t* root;
//json_t* json_value_entry;
//json_t* param;
//json_t* mode;
//json_t* func;
//json_error_t err;
//char code;

u8 mainRunStep;
u8 receiveStep;
u8 fps;
u8 fpsCount;


int main()
{
    u8 i;
    STRUCT_SET *set;

    //系统初始化
    sysParam.initState = system_init();

    Read_Flash(x3,(u16*)&memory,62);

    //关机模式
    m1 = ( RUN_MODE*)malloc(sizeof( RUN_MODE));
    m1->showLed = mode1Led;
    m1->ctlRelay = mode1Relay;
    m1->index = 1;

    //全天模式
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

    //定时模式
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

    //防冻模式
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

    //模式链表的构造初始化
    m2->next = m3;
    m3->next = m4;
    m4->next = m2;

    m1->next = m1;

    //初始化当前模式
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

    fpsCount = 0;

    while(1) {

        mainRunStep = 0;
        //按键检查函数
        check_button(&currMode);

        mainRunStep = 1;

//        Recv();

        mainRunStep = 2;

        if( sysParam.cycle > sysParam.setTouch + 3000 && sysParam.setTouch > 0) {
            currMode->setCurr = NULL;
            sysParam.setTouch = 0;
        }

        mainRunStep = 3;

        //读取系统时间
        HYM8563_Read_time();

        mainRunStep = 4;

        if(wifiInitState == 0) {
//            wifi_init();
            mainRunStep = 5;
        } else {
            mainRunStep = 6;
//            s_repon = NULL;
//            root1  = json_object();

//            num= currMode->runParam.Time1_Start_Hour*60+currMode->runParam.Time1_Start_Minute;
//            json_object_set_new(root1,"T1Start",json_integer(num));

//            num= currMode->runParam.Time1_Stop_Hour*60+currMode->runParam.Time1_Stop_Minute;
//            json_object_set_new(root1,"T1Stop",json_integer(num));

//            num= currMode->runParam.Time1_Temp;
//            json_object_set_new(root1,"T1Temp",json_integer(num));

//            num= currMode->runParam.Time2_Start_Hour*60+currMode->runParam.Time2_Start_Minute;
//            json_object_set_new(root1,"T2Start",json_integer(num));

//            num= currMode->runParam.Time2_Stop_Hour*60+currMode->runParam.Time2_Stop_Minute;
//            json_object_set_new(root1,"T2Stop",json_integer(num));

//            num= currMode->runParam.Time2_Temp;
//            json_object_set_new(root1,"T2Temp",json_integer(num));

//            num= currMode->runParam.Time3_Start_Hour*60+currMode->runParam.Time3_Start_Minute;
//            json_object_set_new(root1,"T3Start",json_integer(num));

//            num= currMode->runParam.Time3_Stop_Hour*60+currMode->runParam.Time3_Stop_Minute;
//            json_object_set_new(root1,"T3Stop",json_integer(num));

//            num= currMode->runParam.Time3_Temp;
//            json_object_set_new(root1,"T3Temp",json_integer(num));

//            num= (sysParam.Hour_High*10+sysParam.Hour_Low)*60+(sysParam.Minute_High*10+sysParam.Minute_Low);
//            json_object_set_new(root1,"Systime",json_integer(num));

//            num= capParam.temperature;
//            json_object_set_new(root1,"CapTemp",json_integer(num));

//            num= workState.isHot;
//            json_object_set_new(root1,"Hot",json_integer(num));

//            num= workState.isInsulation;
//            json_object_set_new(root1,"Insulation",json_integer(num));

//            num= workState.isFan;
//            json_object_set_new(root1,"Fan",json_integer(num));

//            json_object_set_new(root1,"mode",json_integer(currMode->index));

            mainRunStep = 7;
//            s_repon = json_dumps(root1, JSON_INDENT(0));
//            if(s_repon != NULL && Data_ok == 0) {
//                mainRunStep = 8;
//                //for(i = 0; i < 1; i++){
//                wifi_send(0,s_repon);
//                //}
//                free(s_repon);
//                mainRunStep = 9;
//            }
//            json_decref(root1);
//            mainRunStep = 10;
        }

        mainRunStep = 11;

        //采集数据
        if(sysParam.Seconds % 2 == 0) {
            mainRunStep = 12;
            Get_Temputure();
            mainRunStep = 13;
        }
        mainRunStep = 14;
        //继电器控制
        currMode->ctlRelay(currMode);
        mainRunStep = 15;
        //数码管显示
        currMode->showLed(currMode);

        mainRunStep = 16;
        sysParam.cycle++;
    }
}

void mode_exchange(int m) {

    if(m == 0) {
        currMode = m1;
        memory[60] = currMode->index;
        memory[61] = runMode->index;
        Write_Flash(x3, (u16*)&memory,62);
    }

    if(m == 1) {
        currMode = runMode;
        currMode->setCurr=NULL;
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
    u8 i;
    u16 index = 0;
    u16 temp_datalen;
    char temp[20]= {0};
    char user_id_str[2]= {0};
    char * len_str;
//	  if(Send_Flag < 200)
//	 {
//	   return;
//	 }
    if(!Find(">"))
    {
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

        i = 0;
        for (; i<strlen(temp); i++)
        {
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
            USART_SendData(USART1,temp[i]);
        }
        UART1_SendLR();
        Send_Again = 0;
        Send_Flag = 0;
        return;
    }


    for ( i = 0; i<strlen(str); i++)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
        USART_SendData(USART1,str[i]);
    }
    CLR_Buf1();
    Send_Flag = 0;
}


//void Recv(void)
//{
//    if(Data_ok == 1)
//    {


//        u8 i;
//        receiveStep = 0;
//        for(i = 0; i<Data_len; i++) {
//            reviceData[i] = Data[i];
//        }

//        receiveStep = 1;

//        for(; i < 200; i++) {
//            reviceData[i] = 0;
//        }

//        receiveStep = 2;

//        root = json_loads(&reviceData[0], Data_len, &err);

//        receiveStep = 3;
//        //root = json_loads(str, 39, &err);

//        if(NULL != root && json_is_object(root))
//        {

//            receiveStep = 4;

//            func = json_object_get(root, "func");

//            receiveStep = 5;

//            if(NULL != func && json_is_integer(func))
//            {

//                receiveStep = 6;

//                code = json_integer_value(func);

//                receiveStep = 7;

//                json_decref(func);

//                //BSP_LED_On(json_real_value(led));
//                if(code < 5) {

//                    receiveStep = 8;

//                    mode_exchange(code);

//                    receiveStep = 9;

//                }
//                if(code == 5) {



////                    RUN_MODE **rm;
////                    receiveStep = 10;
////                    mode =json_object_get(root, "mode");

////                    receiveStep = 11;

////                    if(NULL != mode && json_is_integer(mode))
////                    {

////                        receiveStep = 12;

////                        code = json_integer_value(mode);

////                        receiveStep = 13;

////                        json_decref(mode);

////                        switch(code) {
////                        case 2: {

////                            receiveStep = 14;

////                            rm = &m2;
////                            break;
////                        }
////                        case 3: {

////                            receiveStep = 15;

////                            rm = &m3;
////                            break;
////                        }
////                        case 4: {

////                            receiveStep = 16;

////                            rm = &m4;
////                            break;
////                        }
////                        case 5: {

////                            receiveStep = 17;

////                            param =json_object_get(root, "param");

////                            receiveStep = 18;

////                            if(NULL != param && json_is_integer(param))
////                            {

////                                receiveStep = 19;

////                                code = json_integer_value(param);

////                                receiveStep = 20;

////                                if(code==0) {

////                                    receiveStep = 21;

////                                    json_value_entry =json_object_get(root, "value");

////                                    receiveStep = 22;

////                                    if(NULL != json_value_entry && json_is_integer(json_value_entry))
////                                    {

////                                        receiveStep = 23;

////                                        code = json_integer_value(json_value_entry);
////                                        sysParam.Hour=code/60;
////                                        sysParam.Minute=code%60;
////                                        Hour=(0xff & (sysParam.Hour>>4))*10 +(0xf & sysParam.Hour);
////                                        Minute=(0xff & (sysParam.Minute>>4))*10 +(0xf & sysParam.Minute);
////                                        HYM8563_Write_time();
////                                        json_decref(json_value_entry);

////                                        receiveStep = 24;

////                                    }
////                                }

////                                receiveStep = 25;

////                                json_decref(param);

////                                receiveStep = 26;

////                            }
////                        }
////                        }

////                        receiveStep = 27;


////                    }

//                    if(currMode != NULL) {

//                        receiveStep = 28;

//                        param =json_object_get(root, "param");

//                        receiveStep = 29;

//                        code = -1;
//                        if(NULL != param && json_is_integer(param))
//                        {

//                            receiveStep = 30;

//                            code = json_integer_value(param);
//                            json_decref(param);

//                            receiveStep = 31;

//                        }

//                        switch(code) {
//                        case 0:
//                        {

//                            receiveStep = 32;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 33;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {

//                                receiveStep = 34;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time1_Start_Hour=code/60;
//                                currMode->runParam.Time1_Start_Minute=code%60;

//                                receiveStep = 35;

//                            }
//                            break;
//                        }
//                        case 1:
//                        {

//                            receiveStep = 36;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 37;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {

//                                receiveStep = 38;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time1_Stop_Hour=code/60;
//                                currMode->runParam.Time1_Stop_Minute=code%60;

//                                receiveStep = 39;

//                            }
//                            break;
//                        }
//                        case 2:
//                        {

//                            receiveStep = 40;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 41;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {

//                                receiveStep = 42;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time1_Temp=code;

//                                receiveStep = 43;

//                            }
//                            break;
//                        }
//                        case 3:
//                        {

//                            receiveStep = 44;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 45;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {

//                                receiveStep = 46;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time2_Start_Hour=code/60;
//                                currMode->runParam.Time2_Start_Minute=code%60;

//                                receiveStep = 47;

//                            }
//                            break;
//                        }
//                        case 4:
//                        {

//                            receiveStep = 48;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 49;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {

//                                receiveStep = 50;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time2_Stop_Hour=code/60;
//                                currMode->runParam.Time2_Stop_Minute=code%60;

//                                receiveStep = 51;

//                            }
//                            break;
//                        }
//                        case 5:
//                        {
//                            receiveStep = 52;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 53;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {

//                                receiveStep = 54;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time2_Temp=code;

//                                receiveStep = 55;

//                            }
//                            break;
//                        }
//                        case 6:
//                        {

//                            receiveStep = 56;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 57;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {

//                                receiveStep = 58;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time3_Start_Hour=code/60;
//                                currMode->runParam.Time3_Start_Minute=code%60;

//                                receiveStep = 59;

//                            }
//                            break;
//                        }
//                        case 7:
//                        {

//                            receiveStep = 60;

//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 61;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {
//                                receiveStep = 62;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time3_Stop_Hour=code/60;
//                                currMode->runParam.Time3_Stop_Minute=code%60;

//                                receiveStep = 63;

//                            }
//                            break;
//                        }
//                        case 8:
//                        {

//                            receiveStep = 64;
//                            json_value_entry =json_object_get(root, "value");

//                            receiveStep = 65;

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {
//                                receiveStep = 66;

//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                currMode->runParam.Time3_Temp=code;

//                                receiveStep = 67;

//                            }
//                            break;
//                        }
//                        case 9: {
//                            json_value_entry =json_object_get(root, "value");

//                            if(NULL != json_value_entry && json_is_integer(json_value_entry))
//                            {
//                                code = json_integer_value(json_value_entry);
//                                json_decref(json_value_entry);
//                                sysParam.Hour=code/60;
//                                sysParam.Minute=code%60;
//                                Hour=(0xff & (sysParam.Hour>>4))*10 +(0xf & sysParam.Hour);
//                                Minute=(0xff & (sysParam.Minute>>4))*10 +(0xf & sysParam.Minute);
//                                HYM8563_Write_time();

//                            }
//                            break;

//                        }
//                        }
//                    }
//                }
//                receiveStep = 68;

//                receiveStep = 69;
//            }
//            receiveStep = 70;
//            json_decref(root);
//            receiveStep = 71;
//        }
//        receiveStep = 72;
//        Data_ok =0;
//    }
//}