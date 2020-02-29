#include "set_param.h"
#include "led.h"

void setTime1OpenHour(RUN_MODE* mode, int v) {
    mode->runParam.Time1_Start_Hour+=v;
    if(mode->runParam.Time1_Start_Hour>23) {
        mode->runParam.Time1_Start_Hour=0;
    }
    if(mode->runParam.Time1_Start_Hour<0) {
        mode->runParam.Time1_Start_Hour=23;
    }
};

void setTime1OpenMinute(RUN_MODE* mode, int v) {
    mode->runParam.Time1_Start_Minute+=v;
    if( mode->runParam.Time1_Start_Minute>59) {
        mode->runParam.Time1_Start_Minute = 0;
    }

    if( mode->runParam.Time1_Start_Minute<0) {
        mode->runParam.Time1_Start_Minute = 59;
    }
};

void setTime1CloseHour(RUN_MODE* mode, int v) {
    mode->runParam.Time1_Stop_Hour+=v;
    if(mode->runParam.Time1_Stop_Hour>23) {
        mode->runParam.Time1_Stop_Hour=0;
    }
    if(mode->runParam.Time1_Stop_Hour<0) {
        mode->runParam.Time1_Stop_Hour=23;
    }
};

void setTime1CloseMinute(RUN_MODE* mode, int v) {
    mode->runParam.Time1_Stop_Minute+=v;
    if( mode->runParam.Time1_Stop_Minute>59) {
        mode->runParam.Time1_Stop_Minute = 0;
    }

    if( mode->runParam.Time1_Stop_Minute<0) {
        mode->runParam.Time1_Stop_Minute = 59;
    }
};

void setTime1Tempreture(RUN_MODE* mode, int v) {
    mode->runParam.Time1_Temp+=v;
    if(mode->runParam.Time1_Temp>mode->tempetureRangMax) {
        mode->runParam.Time1_Temp=mode->tempetureRangMax;
    }
    if(mode->runParam.Time1_Temp<mode->tempetureRangMin) {
        mode->runParam.Time1_Temp=mode->tempetureRangMin;
    }
};

void setTime2OpenHour(RUN_MODE* mode, int v) {
    mode->runParam.Time2_Start_Hour+=v;
    if(mode->runParam.Time2_Start_Hour>23) {
        mode->runParam.Time2_Start_Hour=0;
    }
    if(mode->runParam.Time2_Start_Hour<0) {
        mode->runParam.Time2_Start_Hour=23;
    }
    if(mode->runParam.Time2_Start_Hour>=mode->runParam.Time1_Stop_Hour) {
        mode->runParam.Time2_Start_Hour=mode->runParam.Time1_Stop_Hour;
    }
		
		
		
};

void setTime2OpenMinute(RUN_MODE* mode, int v) {
    mode->runParam.Time2_Start_Minute+=v;
    if( mode->runParam.Time2_Start_Minute>59) {
        mode->runParam.Time2_Start_Minute = 0;
    }

    if( mode->runParam.Time2_Start_Minute<0) {
        mode->runParam.Time2_Start_Minute = 59;
    }
};

void setTime2CloseHour(RUN_MODE* mode, int v) {
    mode->runParam.Time2_Stop_Hour+=v;
    if(mode->runParam.Time2_Stop_Hour>23) {
        mode->runParam.Time2_Stop_Hour=0;
    }
    if(mode->runParam.Time2_Stop_Hour<0) {
        mode->runParam.Time2_Stop_Hour=23;
    }
};

void setTime2CloseMinute(RUN_MODE* mode, int v) {
    mode->runParam.Time2_Stop_Minute+=v;
    if( mode->runParam.Time2_Stop_Minute>59) {
        mode->runParam.Time2_Stop_Minute = 0;
    }

    if( mode->runParam.Time2_Stop_Minute<0) {
        mode->runParam.Time2_Stop_Minute = 59;
    }
};

void setTime2Tempreture(RUN_MODE* mode, int v) {
    mode->runParam.Time2_Temp+=v;
    if(mode->runParam.Time2_Temp>80) {
        mode->runParam.Time2_Temp=80;
    }
    if(mode->runParam.Time2_Temp<20) {
        mode->runParam.Time2_Temp=20;
    }
};

void setTime3OpenHour(RUN_MODE* mode, int v) {
    mode->runParam.Time3_Start_Hour+=v;
    if(mode->runParam.Time3_Start_Hour>23) {
        mode->runParam.Time3_Start_Hour=0;
    }
    if(mode->runParam.Time3_Start_Hour<0) {
        mode->runParam.Time3_Start_Hour=23;
    }
};

void setTime3OpenMinute(RUN_MODE* mode, int v) {
    mode->runParam.Time3_Start_Minute+=v;
    if( mode->runParam.Time3_Start_Minute>59) {
        mode->runParam.Time3_Start_Minute = 0;
    }

    if( mode->runParam.Time3_Start_Minute<0) {
        mode->runParam.Time3_Start_Minute = 59;
    }
};

void setTime3CloseHour(RUN_MODE* mode, int v) {
    mode->runParam.Time3_Stop_Hour+=v;
    if(mode->runParam.Time3_Stop_Hour>23) {
        mode->runParam.Time3_Stop_Hour=0;
    }
    if(mode->runParam.Time3_Stop_Hour<0) {
        mode->runParam.Time3_Stop_Hour=23;
    }
};

void setTime3CloseMinute(RUN_MODE* mode, int v) {
    mode->runParam.Time3_Stop_Minute+=v;
    if( mode->runParam.Time3_Stop_Minute>59) {
        mode->runParam.Time3_Stop_Minute = 0;
    }

    if( mode->runParam.Time3_Stop_Minute<0) {
        mode->runParam.Time3_Stop_Minute = 59;
    }
};

void setTime3Tempreture(RUN_MODE* mode, int v) {
    mode->runParam.Time3_Temp+=v;
    if(mode->runParam.Time3_Temp>80) {
        mode->runParam.Time3_Temp=80;
    }
    if(mode->runParam.Time3_Temp<20) {
        mode->runParam.Time3_Temp=20;
    }
};

void setSysTimeHour(RUN_MODE* mode, int v) {
    sysParam.Hour=(0xff & (sysParam.Hour>>4))*10 +(0xf & sysParam.Hour);
    if (v>0)
    {
        if(sysParam.Hour>22) {
            sysParam.Hour=0;
        }
        else
        {
            sysParam.Hour+=v;
        }

    }
    else
    {
        if(sysParam.Hour==0) {
            sysParam.Hour=24;
        }
        sysParam.Hour+=v;
    }
    Hour=sysParam.Hour;
    HYM8563_Read_time();//采用写地址读数据模式
    Minute=(0xff & (sysParam.Minute>>4))*10 +(0xf & sysParam.Minute);
    Seconds=(0xff & (sysParam.Seconds>>4))*10 +(0xf & sysParam.Seconds);
    HYM8563_Write_time();
};
void setSysTimeMinute(RUN_MODE* mode, int v) {
    sysParam.Minute=(0xff & (sysParam.Minute>>4))*10 +(0xf & sysParam.Minute);
    if (v>0)
    {
        if(sysParam.Minute>58) {
            sysParam.Minute=0;
        }
        else
        {
            sysParam.Minute+=v;
        }

    }
    else
    {
        if(sysParam.Minute==0) {
            sysParam.Minute=60;
        }
        sysParam.Minute+=v;
    }
    Minute=sysParam.Minute;
    HYM8563_Read_time();//采用写地址读数据模式
    Hour=(0xff & (sysParam.Hour>>4))*10 +(0xf & sysParam.Hour);
    Seconds=(0xff & (sysParam.Seconds>>4))*10 +(0xf & sysParam.Seconds);
    HYM8563_Write_time();
};
