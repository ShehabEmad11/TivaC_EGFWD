#ifndef GPT_CFG_H
#define GPT_CFG_H

#include "Std_Types.h"
#include "Gpt_Types.h"


enum GptPredefTimer1usEnablingGradeType
{
    GPT_PREDEF_TIMER_1US_DISABLED,                      /*Disabled*/
    GPT_PREDEF_TIMER_1US_16BIT_ENABLED,                 /*16bit timer enabled*/
    GPT_PREDEF_TIMER_1US_16_24BIT_ENABLED,              /*16 and 24bit timers enabled*/
    GPT_PREDEF_TIMER_1US_16_24_32BIT_ENABLED            /*16, 24 and 32bit timers enabled*/
};


/*Enables/disables the GPT Predef Timer 100μs32bit.*/
#define GptPredefTimer100us32bitEnable              (FALSE)
/*Specifies the grade of enabling the GPT Predef Timers with 1μs tick duration.*/
#define GptPredefTimer1usEnablingGrade              (GPT_PREDEF_TIMER_1US_DISABLED)  



#if GptPredefTimer100us32bitEnable != FALSE
    #define GPT_PREDEF_TIMER_100US_32BIT_CHANNEL_ID   (TIMER_32_64_TIMER0)
#endif


#if GptPredefTimer1usEnablingGrade != GPT_PREDEF_TIMER_1US_DISABLED
    #define GPT_PREDEF_TIMER_1US_16BIT_CHANNEL_ID     (TIMER_32_64_TIMER0)     
    #define GPT_PREDEF_TIMER_1US_24BIT_CHANNEL_ID     (TIMER_32_64_TIMER0)
    #define GPT_PREDEF_TIMER_1US_32BIT_CHANNEL_ID     (TIMER_32_64_TIMER0)
#endif


#define INDIVIDUAL_ACCESS    (0u)
#define CONCATENATED_ACCESS  (1u)
#define CHANNEL_ACCESS_MODE  (INDIVIDUAL_ACCESS)

#define GPT_STALL_DURING_DEBUG  FALSE

extern void App_WTIM0_CallBack(void);


#define NUMBER_GPT_CONFIGURED_CHANNELS 1   

#define GPT_CHANNELS_CONFIGURATION  \
{\
/*.channelID             */   TIMER_32_64_TIMER0,\
/*.channelMode           */   GPT_CH_MODE_CONTINUOUS,\
/*.channelFreqHz         */   16,\
/*.channelTickValMax     */   (uint32)0x00FFFFFF,\
/*.channelNotificationCbk*/   App_WTIM0_CallBack,\
/*.channelCountDirection */   COUNT_DOWN_DIRECTION,\
/*.channelBitWidth       */   BITWIDH_32,\
/*.channelPrescaler      */   PRESCALER_VAL_0\
}



#endif /* GPT_CFG_H */
