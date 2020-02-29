
#ifndef PERSON_H_
#define PERSON_H_



struct STRUCT_LED_PIN_VALUE {

    /*
    标签的灯管
    */
    unsigned char Label_Time1;//定时一 Label
    unsigned char Label_Time2;//定时二 Label
    unsigned char Label_Time3;//定时三 Label
    unsigned char Label_Power;//电源 Label 及 icon
    unsigned char Label_Open;//开 Label
    unsigned char Label_Close;//关 Label
    unsigned char Label_Temperature_Set;//设置温度 Label
    unsigned char Label_Temperature_Real;//实际温度 Label

    /*
    风扇的10个管
    */
    unsigned char Fan_Point;
    unsigned char Fan_Angle1;
    unsigned char Fan_Angle2;
    unsigned char Fan_Angle3;
    unsigned char Fan_Angle4;
    unsigned char Fan_Angle5;
    unsigned char Fan_Angle6;
    unsigned char Fan_Angle7;
    unsigned char Fan_Angle8;
    unsigned char Fan_Angle9;

    /*
    功率的灯管
    */
    unsigned char Watt;//功率 Label
    unsigned char Watt1;//功率计1
    unsigned char Watt2;//功率计2
    unsigned char Watt3;//功率计3
    unsigned char Watt4;//功率计4
    unsigned char Watt5;//功率计5
    unsigned char Watt6;//功率计6
    unsigned char Watt7;//功率计7
    unsigned char Watt8;//功率计8
    /*图标的灯管
    */
    unsigned char Icon_Logo; //电采暖炉 Label
    unsigned char	Icon_Time; //小时钟的 Icon
    unsigned char Icon_Temperature;//摄氏度 Icon
    unsigned char Icon_Hot;
    unsigned char Icon_Insulation;
    unsigned char Icon_AntiFreeze;
    unsigned char Icon_Fault;

    /*数码管的灯管*/
    unsigned char Digit_Hour_High;
    unsigned char Digit_Hour_Low;
    unsigned char Digit_Minute_High;
    unsigned char Digit_Minute_Low;
    unsigned char Digit_Temperature_High;
    unsigned char Digit_Temperature_Low;
    unsigned char Digit_Colon;
};
extern struct STRUCT_LED_PIN_VALUE ledPinValue;


/*
系统参数
*/
struct SYS_PARAM {
    int initState;
    signed  char Hour;
    signed  char Minute;

    signed char  Seconds;


    signed char  Date;
    signed char  Week;
    signed char   Month;
    signed char  Years;
    signed char   Hour_Low;  //小时的个位
    signed char  Hour_High; //小时的十位
    signed char   Minute_Low;  //分钟的个位
    signed char   Minute_High;  //分钟的十位

    long long beep;

    long long cycle;

    long long setTouch;

} ;

extern struct SYS_PARAM sysParam;

/*
捕获参数
*/
struct CAP_PARAM {
    char temperature;
} ;

extern struct CAP_PARAM capParam;

/*
运行参数
*/
struct RUN_PARAM {
    signed char Time1_Start_Hour;
    signed char Time1_Start_Minute;
    signed char Time1_Stop_Hour;
    signed char Time1_Stop_Minute;
    char Time1_Temp;

    signed char Time2_Start_Hour;
    signed char Time2_Start_Minute;
    signed char Time2_Stop_Hour;
    signed char Time2_Stop_Minute;
    char Time2_Temp;

    signed char Time3_Start_Hour;
    signed char Time3_Start_Minute;
    signed char Time3_Stop_Hour;
    signed char Time3_Stop_Minute;
    char Time3_Temp;

    char null;
};
struct RUN_MODE;
/*
设置链表的结构体
*/
typedef struct STRUCTSET {
    struct STRUCTSET *next;
    void (*setValue)(struct RUN_MODE* mode, int v);
    void (*showLed)(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
    void (*ctlRelay)(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
} STRUCT_SET;

/*
运行模式
*/
typedef struct RUN_MODE {
    char index;
    struct RUN_PARAM runParam;
//		struct SYS_PARAM sysParam;

    struct RUN_MODE* next;

    STRUCT_SET* setHead;
    STRUCT_SET* setCurr;
    char tempetureRangMax;
    char tempetureRangMin;

    void (*showLed)(struct RUN_MODE* mode);
    void (*ctlRelay)(struct RUN_MODE* mode);

} RUN_MODE;

struct STRUCT_WORK_STATE {
    char isHot;
    char isInsulation;
    char Watt;
    char isFan;
    char timeIndex;
};

extern struct STRUCT_WORK_STATE workState;


typedef struct STRUCT_FLASH_MEMORY {
    signed char Time1_Start_Hour2;
    signed char Time1_Start_Minute2;
    signed char Time1_Stop_Hour2;
    signed char Time1_Stop_Minute2;
    char Time1_Temp2;

    signed char Time2_Start_Hour2;
    signed char Time2_Start_Minute2;
    signed char Time2_Stop_Hour2;
    signed char Time2_Stop_Minute2;
    char Time2_Temp2;

    signed char Time3_Start_Hour2;
    signed char Time3_Start_Minute2;
    signed char Time3_Stop_Hour2;
    signed char Time3_Stop_Minute2;
    char Time3_Temp2;








    signed char Time1_Start_Hour3;
    signed char Time1_Start_Minute3;
    signed char Time1_Stop_Hour3;
    signed char Time1_Stop_Minute3;
    char Time1_Temp3;

    signed char Time2_Start_Hour3;
    signed char Time2_Start_Minute3;
    signed char Time2_Stop_Hour3;
    signed char Time2_Stop_Minute3;
    char Time2_Temp3;

    signed char Time3_Start_Hour3;
    signed char Time3_Start_Minute3;
    signed char Time3_Stop_Hour3;
    signed char Time3_Stop_Minute3;
    char Time3_Temp3;




















    signed char Time1_Start_Hour4;
    signed char Time1_Start_Minute4;
    signed char Time1_Stop_Hour4;
    signed char Time1_Stop_Minute4;
    char Time1_Temp4;

    signed char Time2_Start_Hour4;
    signed char Time2_Start_Minute4;
    signed char Time2_Stop_Hour4;
    signed char Time2_Stop_Minute4;
    char Time2_Temp4;

    signed char Time3_Start_Hour4;
    signed char Time3_Start_Minute4;
    signed char Time3_Stop_Hour4;
    signed char Time3_Stop_Minute4;
    char Time3_Temp4;






    char x1;
    char x2;

} flashMemory;

#endif /* PERSON_H_ */

