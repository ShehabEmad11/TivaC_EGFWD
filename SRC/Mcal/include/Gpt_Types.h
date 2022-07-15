#ifndef GPT_TYPES_H
#define GPT_TYPES_H

#include "Std_Types.h"
//#include "Gpt_Cfg.h"


typedef enum
{
    TIMER_16_32_TIMER0 ,
	TIMER_16_32_TIMER1 ,
	TIMER_16_32_TIMER2 ,
	TIMER_16_32_TIMER3 ,
	TIMER_16_32_TIMER4 ,
	TIMER_16_32_TIMER5 ,

    TIMER_32_64_TIMER0 ,
	TIMER_32_64_TIMER1 ,
	TIMER_32_64_TIMER2 ,
	TIMER_32_64_TIMER3 ,
	TIMER_32_64_TIMER4 ,
	TIMER_32_64_TIMER5 , 

    NUMBER_TIMER_CHANNELS=12
}Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum
{
    GPT_MODE_NORMAL,
    GPT_MODE_SLEEP,
    uninitialized,
}Gpt_ModeType;

typedef enum
{
    GPT_PREDEF_TIMER_1US_16BIT,
    GPT_PREDEF_TIMER_1US_24BIT,
    GPT_PREDEF_TIMER_1US_32BIT,
    GPT_PREDEF_TIMER_100US_32BIT
}Gpt_PredefTimerType;


typedef enum
{
    GPT_CH_MODE_CONTINUOUS,
    GPT_CH_MODE_ONESHOT
}GptChannelMode;

typedef void (*GptPtrNotificationCbkType)(void);


typedef enum
{
    STATE_NOT_INITIALIZED,
    STATE_INITIALIZED,
    STATE_RUNNING,
    STATE_STOPPED,
    STATE_EXPIRED
}GptInternal_StateType;

typedef enum
{
    BITWIDH_16,
    BITWIDH_24,
    BITWIDH_32,
    BITWIDH_64
}GptInternal_BitSizeType;

typedef enum
{
    COUNT_DOWN_DIRECTION,
    COUNT_UP_DIRECTION  
}GptInternal_CountDirectionType;

typedef enum
{
    PRESCALER_VAL_0
}GptInternal_PrescalerType;
typedef  struct
{
    GptInternal_StateType           channelState;
}GptInternal_InfoType;



typedef uint8 GptInternal_FreqType;

typedef struct 
{  
    Gpt_ChannelType                 channelID;
    GptChannelMode                  channelMode;
    GptInternal_FreqType            channelFreq ;
    Gpt_ValueType                   channelTickValMax;   
    GptPtrNotificationCbkType       channelNotificationCbk;

    GptInternal_CountDirectionType  channelCountDirection;
    GptInternal_BitSizeType         channelBitWidth;
    GptInternal_PrescalerType       channelPrescaler;
}Gpt_ChannelConfigType;

typedef struct
{
    uint8                        numberChannels;  
    Gpt_ChannelConfigType       channelsCfg;                
}Gpt_ConfigType;
#endif /* GPT_TYPES_H */
