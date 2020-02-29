#include "led_ctrl.h"

char t_high;
char t_low;

void setWatt(struct STRUCT_LED_PIN_VALUE* pin);

/*
LED控制函数
*/
void mode1Led(RUN_MODE* mode) {
    struct STRUCT_LED_PIN_VALUE* pin = getLedPinValueStruct();
    pin->Label_Power = 1;
    pin->Icon_Logo=1;
    pin->Digit_Hour_High = 10;
    pin->Digit_Hour_Low = 10;
    pin->Digit_Minute_High = 10;
    pin->Digit_Minute_Low = 10;
    pin->Digit_Temperature_High = 10;
    pin->Digit_Temperature_Low = 10;

    LED_Disp();
};

/*
LED控制函数
*/
void mode2Led(RUN_MODE* mode) {
    struct STRUCT_LED_PIN_VALUE* pin = getLedPinValueStruct();
    pin->Label_Power = 1;
    pin->Icon_Logo=1;
    pin->Icon_Time=1;
    pin->Icon_Temperature=1;
    pin->Label_Temperature_Real=1;

    pin->Digit_Colon = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Digit_Hour_High = sysParam.Hour_High;
    pin->Digit_Hour_Low = sysParam.Hour_Low;
    pin->Digit_Minute_High = sysParam.Minute_High;
    pin->Digit_Minute_Low = sysParam.Minute_Low;
    pin->Digit_Temperature_High = capParam.temperature / 10;
    pin->Digit_Temperature_Low = capParam.temperature % 10;

    if(mode->setCurr != NULL) {
        mode->setCurr->showLed(mode, pin);
    }

    pin->Label_Time1 =  0;
    pin->Label_Time2 =  0;
    pin->Label_Time3 =  0;
    if(workState.isFan)
    {
        pin->Fan_Point=1;
        pin->Fan_Angle1 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle2 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle3 = sysParam.Seconds % 3 == 1 ? 1 : 0;
        pin->Fan_Angle4 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle5 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle6 = sysParam.Seconds % 3 == 1 ? 1 : 0;
        pin->Fan_Angle7 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle8 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle9 = sysParam.Seconds % 3 == 1 ? 1 : 0;
    }

    pin->Icon_Hot = workState.isHot;
    pin->Icon_Insulation = workState.isInsulation;
    setWatt(pin);

    LED_Disp();
};

/*
LED控制函数
*/
void mode3Led(RUN_MODE* mode) {
    struct STRUCT_LED_PIN_VALUE* pin = getLedPinValueStruct();
    pin->Label_Power = 1;
    pin->Icon_Logo=1;
    pin->Icon_Temperature=1;
    pin->Icon_Time=1;
    pin->Label_Time1=workState.timeIndex == 1;
    pin->Label_Time2=workState.timeIndex == 2;
    pin->Label_Time3=workState.timeIndex == 3;
    pin->Label_Temperature_Real=1;
    pin->Digit_Colon = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Digit_Hour_High = sysParam.Hour_High;
    pin->Digit_Hour_Low = sysParam.Hour_Low;
    pin->Digit_Minute_High = sysParam.Minute_High;
    pin->Digit_Minute_Low = sysParam.Minute_Low;
    pin->Digit_Temperature_High = capParam.temperature / 10;
    pin->Digit_Temperature_Low = capParam.temperature % 10;

    if(mode->setCurr != NULL) {
        mode->setCurr->showLed(mode, pin);
    }
    if(workState.isFan)
    {
        pin->Fan_Point=1;
        pin->Fan_Angle1 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle2 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle3 = sysParam.Seconds % 3 == 1 ? 1 : 0;
        pin->Fan_Angle4 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle5 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle6 = sysParam.Seconds % 3 == 1 ? 1 : 0;
        pin->Fan_Angle7 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle8 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle9 = sysParam.Seconds % 3 == 1 ? 1 : 0;
    }

    pin->Icon_Hot = workState.isHot;
    pin->Icon_Insulation = workState.isInsulation;
    setWatt(pin);

    LED_Disp();
};

/*
LED控制函数
*/
void mode4Led(RUN_MODE* mode) {
    struct STRUCT_LED_PIN_VALUE* pin = getLedPinValueStruct();
    pin->Label_Power = 1;
    pin->Icon_Logo=1;
    pin->Icon_Time=1;
    pin->Icon_Temperature=1;
    pin->Label_Temperature_Real=1;

    pin->Digit_Colon = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Digit_Hour_High = sysParam.Hour_High;
    pin->Digit_Hour_Low = sysParam.Hour_Low;
    pin->Digit_Minute_High = sysParam.Minute_High;
    pin->Digit_Minute_Low = sysParam.Minute_Low;
    pin->Digit_Temperature_High = capParam.temperature / 10;
    pin->Digit_Temperature_Low = capParam.temperature % 10;
    pin->Icon_AntiFreeze = 1;

    if(mode->setCurr != NULL) {
        mode->setCurr->showLed(mode, pin);
    }

    pin->Label_Time1 =  0;
    pin->Label_Time2 =  0;
    pin->Label_Time3 =  0;
    if(workState.isFan)
    {
        pin->Fan_Point=1;
        pin->Fan_Angle1 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle2 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle3 = sysParam.Seconds % 3 == 1 ? 1 : 0;
        pin->Fan_Angle4 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle5 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle6 = sysParam.Seconds % 3 == 1 ? 1 : 0;
        pin->Fan_Angle7 = sysParam.Seconds % 3 == 0 ? 1 : 0;
        pin->Fan_Angle8 = sysParam.Seconds % 3 == 2 ? 1 : 0;
        pin->Fan_Angle9 = sysParam.Seconds % 3 == 1 ? 1 : 0;
    }
    pin->Icon_Hot = workState.isHot;
    pin->Icon_Insulation = workState.isInsulation;
    setWatt(pin);
    LED_Disp();
};

void setTime1OpenHourLed(struct RUN_MODE* mode, struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time1 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time2 =1;
    pin->Label_Time3 =1;

    t_high = mode->runParam.Time1_Start_Hour / 10;
    t_low = mode->runParam.Time1_Start_Hour % 10;

    pin->Digit_Hour_High =  sysParam.Seconds % 2 == 0 ? t_high : 10;
    pin->Digit_Hour_Low =  sysParam.Seconds % 2 == 0 ? t_low : 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Digit_Temperature_High = mode->runParam.Time1_Temp / 10 ;
    pin->Digit_Temperature_Low =  mode->runParam.Time1_Temp % 10;
    pin->Label_Open = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
//    pin->Fan_Point= sysParam.Seconds % 2 == 0 ? 1 : 0;
//    pin->Fan_Angle3=sysParam.Seconds % 2 == 0 ? 1 : 0;
//    pin->Fan_Angle6=sysParam.Seconds % 2 == 0 ? 1 : 0;
//    pin->Fan_Angle9=sysParam.Seconds % 2 == 0 ? 1 : 0;
};

void setTime1OpenMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
};
void setTime1CloseHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time1 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time2 =1;
    pin->Label_Time3 =1;

    t_high = mode->runParam.Time1_Stop_Hour / 10;
    t_low = mode->runParam.Time1_Stop_Hour % 10;
    pin->Digit_Hour_High =  sysParam.Seconds % 2 == 0 ? t_high: 10;
    pin->Digit_Hour_Low =  sysParam.Seconds % 2 == 0 ? t_low: 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Digit_Temperature_High = mode->runParam.Time1_Temp / 10 ;
    pin->Digit_Temperature_Low =  mode->runParam.Time1_Temp % 10;
    pin->Label_Close = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
};
void setTime1CloseMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
};
void setTime1TempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time1 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time2 =1;
    pin->Label_Time3 =1;

    t_high = mode->runParam.Time1_Temp / 10;
    t_low = mode->runParam.Time1_Temp % 10;
    pin->Digit_Temperature_High =  sysParam.Seconds % 2 == 0 ? t_high : 10;
    pin->Digit_Temperature_Low =  sysParam.Seconds % 2 == 0 ? t_low : 10;
    pin->Digit_Hour_High =   mode->runParam.Time1_Stop_Hour/ 10;
    pin->Digit_Hour_Low =   mode->runParam.Time1_Stop_Hour% 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Label_Temperature_Set =sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
};
void setTime2OpenHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time2 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time1 =1;
    pin->Label_Time3 =1;
    t_high = mode->runParam.Time2_Start_Hour / 10;
    t_low = mode->runParam.Time2_Start_Hour % 10;

    pin->Digit_Hour_High =  sysParam.Seconds % 2 == 0 ? t_high : 10;
    pin->Digit_Hour_Low =  sysParam.Seconds % 2 == 0 ? t_low : 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Digit_Temperature_High = mode->runParam.Time2_Temp / 10 ;
    pin->Digit_Temperature_Low =  mode->runParam.Time2_Temp % 10;
    pin->Label_Open = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
};
void setTime2OpenMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
};
void setTime2CloseHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time2 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time1 =1;
    pin->Label_Time3 =1;
    t_high = mode->runParam.Time2_Stop_Hour / 10;
    t_low = mode->runParam.Time2_Stop_Hour % 10;
    pin->Digit_Hour_High =  sysParam.Seconds % 2 == 0 ? t_high: 10;
    pin->Digit_Hour_Low =  sysParam.Seconds % 2 == 0 ? t_low: 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Digit_Temperature_High = mode->runParam.Time2_Temp / 10 ;
    pin->Digit_Temperature_Low =  mode->runParam.Time2_Temp % 10;

    pin->Label_Close = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
};
void setTime2CloseMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
};
void setTime2TempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time2 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time1 =1;
    pin->Label_Time3 =1;

    t_high = mode->runParam.Time2_Temp / 10;
    t_low = mode->runParam.Time2_Temp % 10;
    pin->Digit_Temperature_High =  sysParam.Seconds % 2 == 0 ? t_high : 10;
    pin->Digit_Temperature_Low =  sysParam.Seconds % 2 == 0 ? t_low : 10;
    pin->Digit_Hour_High =   mode->runParam.Time2_Stop_Hour/ 10;
    pin->Digit_Hour_Low =   mode->runParam.Time2_Stop_Hour% 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Label_Temperature_Set = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
};
void setTime3OpenHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time3 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time1 =1;
    pin->Label_Time2 =1;
    t_high = mode->runParam.Time3_Start_Hour / 10;
    t_low = mode->runParam.Time3_Start_Hour % 10;

    pin->Digit_Hour_High =  sysParam.Seconds % 2 == 0 ? t_high : 10;
    pin->Digit_Hour_Low =  sysParam.Seconds % 2 == 0 ? t_low : 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Digit_Temperature_High = mode->runParam.Time3_Temp / 10 ;
    pin->Digit_Temperature_Low =  mode->runParam.Time3_Temp % 10;

    pin->Label_Open = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
};
void setTime3OpenMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
};
void setTime3CloseHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time3 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time1 =1;
    pin->Label_Time2 =1;
    t_high = mode->runParam.Time3_Stop_Hour / 10;
    t_low = mode->runParam.Time3_Stop_Hour % 10;
    pin->Digit_Hour_High =  sysParam.Seconds % 2 == 0 ? t_high: 10;
    pin->Digit_Hour_Low =  sysParam.Seconds % 2 == 0 ? t_low: 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Digit_Temperature_High = mode->runParam.Time3_Temp / 10 ;
    pin->Digit_Temperature_Low =  mode->runParam.Time3_Temp % 10;
    pin->Label_Close = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
};
void setTime3CloseMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
};
void setTime3TempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Label_Time3 = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Time1 =1;
    pin->Label_Time2 =1;
    t_high = mode->runParam.Time3_Temp / 10;
    t_low = mode->runParam.Time3_Temp % 10;
    pin->Digit_Temperature_High =  sysParam.Seconds % 2 == 0 ? t_high : 10;
    pin->Digit_Temperature_Low =  sysParam.Seconds % 2 == 0 ? t_low : 10;
    pin->Digit_Hour_High =   mode->runParam.Time3_Stop_Hour/ 10;
    pin->Digit_Hour_Low =   mode->runParam.Time3_Stop_Hour% 10;
    pin->Digit_Minute_High=0;
    pin->Digit_Minute_Low=0;
    pin->Label_Temperature_Set = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=0;
    pin->Label_Temperature_Real=0;
};
void setSysTimeHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {



    pin->Digit_Hour_High =  sysParam.Seconds % 2 == 0 ? sysParam.Hour_High : 10;
    pin->Digit_Hour_Low =  sysParam.Seconds % 2 == 0 ? sysParam.Hour_Low : 10;
    pin->Icon_Time=sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
};
void setSysTimeMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Digit_Temperature_High =	mode->runParam.Time1_Temp / 10;
    pin->Digit_Temperature_Low =	mode->runParam.Time1_Temp % 10;
    pin->Digit_Minute_High =  sysParam.Seconds % 2 == 0 ? sysParam.Minute_High : 10;
    pin->Digit_Minute_Low =  sysParam.Seconds % 2 == 0 ? sysParam.Minute_Low : 10;
    pin->Icon_Time=sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Label_Temperature_Real=0;
    pin->Label_Temperature_Set = 1;
};
void setTempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin) {

    t_high = mode->runParam.Time1_Temp / 10;
    t_low = mode->runParam.Time1_Temp % 10;
    pin->Digit_Temperature_High =  sysParam.Seconds % 2 == 0 ? t_high : 10;
    pin->Digit_Temperature_Low =  sysParam.Seconds % 2 == 0 ? t_low : 10;
    pin->Label_Temperature_Set = sysParam.Seconds % 2 == 0 ? 1 : 0;
    pin->Icon_Time=1;
    pin->Label_Temperature_Real=0;
};

void setWatt(struct STRUCT_LED_PIN_VALUE* pin) {
    pin->Watt= 1;
    pin->Watt1=workState.Watt >= 1;
    pin->Watt2=workState.Watt >= 2;
    pin->Watt3=workState.Watt >= 3;
    pin->Watt4=workState.Watt >= 4;
    pin->Watt5=workState.Watt >= 5;
    pin->Watt6=workState.Watt >= 6;
    pin->Watt7=workState.Watt >= 7;
    pin->Watt8=workState.Watt >= 8;

}