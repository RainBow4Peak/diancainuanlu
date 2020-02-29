#include "mode_Relay.h"
#include "led.h"
#include "capture.h"

#define Temp_Diff1 5
#define Temp_Diff2 10
#define Temp_Diff3 15
#define Temp_Diff4 20

char isWork;
char isReady;
char  t;
char hexHour;
char setTemperature;

void checkWork( char start, char end, char prev, char* isWork, char* isReady) {
    if(sysParam.Hour < 10) {
        hexHour = sysParam.Hour;
    }
    if(sysParam.Hour >= 10 && sysParam.Hour < 32) {
        hexHour = sysParam.Hour - 6;
    }
    if(sysParam.Hour >= 32) {
        hexHour = sysParam.Hour - 12;
    }

    *isWork = 0;
    if(end < start) {
        t = start;
        start = end;
        end = t;
        if(hexHour >= start && hexHour < end) {
        } else {
            *isWork = 1;
        }
    } else {
        if(hexHour >= start && hexHour < end) {
            *isWork = 1;
        }
    }

    *isReady = 0;

    if(end < prev) {
        t = prev;
        prev = end;
        end = t;
        if(hexHour >= prev && hexHour < end) {
        } else {
            *isReady = 1;
        }
    } else {
        if(hexHour >= prev && hexHour < end) {
            *isReady = 1;
        }
    }
}

void checkTimer(char start, char end, char* timeIndex) {

}

/*
Relay控制函数
*/
void mode1Relay(RUN_MODE* mode) {
    UJ1=0;
    UJ2=0;
    UJ3=0;
    UJ4=0;
    workState.isInsulation = 0;
    workState.isHot = 0;
    workState.Watt = 0;
    workState.isFan = 0;
};

/*
Relay控制函数
*/
void mode2Relay(RUN_MODE* mode) {
    UJ1=1;
    if((mode->runParam.Time1_Temp>=capParam.temperature+Temp_Diff1) && mode->runParam.Time1_Temp<=capParam.temperature+Temp_Diff2)
    {
        UJ2=1;
        workState.isInsulation = 1;
        workState.isHot = 0;
        workState.Watt = 2;
        workState.isFan = 1;
    }
    if((mode->runParam.Time1_Temp>capParam.temperature+Temp_Diff2) && mode->runParam.Time1_Temp<=capParam.temperature+Temp_Diff3)
    {
        UJ3=1;
        workState.isInsulation = 0;
        workState.isHot = 1;
        workState.Watt = 5;
        workState.isFan = 1;
    }
    if(mode->runParam.Time1_Temp>capParam.temperature+Temp_Diff3)
    {
        UJ4=1;
        workState.isInsulation = 0;
        workState.isHot = 1;
        workState.Watt = 8;
        workState.isFan = 1;
    }
    if((mode->runParam.Time1_Temp<=capParam.temperature)||(mode->runParam.Time1_Temp>mode->tempetureRangMax))
    {
        UJ2=0;
        UJ3=0;
        UJ4=0;

        workState.isInsulation = 1;
        workState.isHot = 0;
        workState.Watt = 0;
        workState.isFan = 1;
    }
};

/*
Relay控制函数
*/
void mode3Relay( RUN_MODE* mode) {
    UJ1=1;

    checkWork( mode->runParam.Time1_Start_Hour, mode->runParam.Time1_Stop_Hour, mode->runParam.Time3_Stop_Hour, &isWork, &isReady);
    if(isReady) {
        workState.timeIndex = 1;
    }
    if(isWork) {
        goto p;
    }

    checkWork( mode->runParam.Time2_Start_Hour, mode->runParam.Time2_Stop_Hour, mode->runParam.Time1_Stop_Hour, &isWork, &isReady);
    if(isReady) {
        workState.timeIndex = 2;
    }
    if(isWork) {
        goto p;
    }

    checkWork( mode->runParam.Time3_Start_Hour, mode->runParam.Time3_Stop_Hour, mode->runParam.Time2_Stop_Hour, &isWork, &isReady);
    if(isReady) {
        workState.timeIndex = 3;
    }
    if(isWork) {
        goto p;
    }

p:

    switch(workState.timeIndex) {
    case 1: {
        setTemperature = mode->runParam.Time1_Temp;
        break;
    }
    case 2: {
        setTemperature = mode->runParam.Time2_Temp;
        break;
    }
    case 3: {
        setTemperature = mode->runParam.Time3_Temp;
        break;
    }
    }

    if(isWork && setTemperature < capParam.temperature + Temp_Diff1)
    {
        UJ2=0;
        UJ3=0;
        UJ4=0;
        workState.isInsulation = 1;
        workState.isHot = 0;
        workState.Watt = 2;
        workState.isFan = 1;
    }

    if(isWork && setTemperature >= capParam.temperature + Temp_Diff1 && setTemperature < capParam.temperature + Temp_Diff2)
    {
        UJ2=1;
        UJ3=0;
        UJ4=0;
        workState.isInsulation = 1;
        workState.isHot = 0;
        workState.Watt = 2;
        workState.isFan = 1;
    }

    if(isWork && setTemperature>=capParam.temperature + Temp_Diff2 && setTemperature < capParam.temperature + Temp_Diff3)
    {
        UJ2=1;
        UJ3=1;
        UJ4=0;
        workState.isInsulation = 0;
        workState.isHot = 1;
        workState.Watt = 5;
        workState.isFan = 1;
    }

    if(isWork && setTemperature >= capParam.temperature + Temp_Diff3)
    {
        UJ2=1;
        UJ3=1;
        UJ4=1;
        workState.isInsulation = 0;
        workState.isHot = 1;
        workState.Watt = 8;
        workState.isFan = 1;
    }

    if(!isWork) {
        UJ2=0;
        UJ3=0;
        UJ4=0;
        workState.isInsulation = 0;
        workState.isHot = 0;
        workState.Watt = 0;
        workState.isFan = 1;
    }

};

/*
Relay控制函数
*/
void mode4Relay( RUN_MODE* mode) {
    UJ1=1;
    if((mode->runParam.Time1_Temp>=capParam.temperature+Temp_Diff2) &&( mode->runParam.Time1_Temp<=capParam.temperature+Temp_Diff3))
    {
        UJ2=1;
        workState.isInsulation = 1;
        workState.isHot = 0;
        workState.Watt = 2;
        workState.isFan = 1;
    }
    if((mode->runParam.Time1_Temp>capParam.temperature+Temp_Diff3) &&( mode->runParam.Time1_Temp<=capParam.temperature+Temp_Diff4))
    {
        UJ3=1;
        workState.isInsulation = 0;
        workState.isHot = 1;
        workState.Watt = 5;
        workState.isFan = 1;
    }
    if(mode->runParam.Time1_Temp>capParam.temperature+Temp_Diff4)
    {
        UJ4=1;
        workState.isInsulation = 0;
        workState.isHot = 1;
        workState.Watt = 8;
        workState.isFan = 1;
    }
    if((mode->runParam.Time1_Temp<=capParam.temperature)||(mode->runParam.Time1_Temp>mode->tempetureRangMax))
    {
        UJ2=0;
        UJ3=0;
        UJ4=0;
        workState.isInsulation = 1;
        workState.isHot = 0;
        workState.Watt = 0;
        workState.isFan = 1;
    }
};
