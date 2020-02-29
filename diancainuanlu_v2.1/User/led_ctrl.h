#include "led.h"
#include "global.h"
#include <stdio.h>

/*
LED控制函数
*/
void mode1Led(RUN_MODE* mode);

/*
LED控制函数
*/
void mode2Led(RUN_MODE* mode);

/*
LED控制函数
*/
void mode3Led(RUN_MODE* mode);

/*
LED控制函数
*/
void mode4Led(RUN_MODE* mode);

void setTime1OpenHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime1OpenMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime1CloseHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime1CloseMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime1TempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime2OpenHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime2OpenMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime2CloseHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime2CloseMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime2TempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime3OpenHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime3OpenMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime3CloseHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime3CloseMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTime3TempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setSysTimeHourLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setSysTimeMinuteLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
void setTempretureLed(struct RUN_MODE* mode,struct STRUCT_LED_PIN_VALUE* pin);
