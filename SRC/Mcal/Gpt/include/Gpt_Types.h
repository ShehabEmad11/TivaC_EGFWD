#ifndef GPT_TYPES_H
#define GPT_TYPES_H

#include "Std_Types.h"


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

    NUMBER_GPT_CHANNELS=12
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

typedef void(*Ptr2VoidFunction_t)(void);

typedef struct 
{
    GptInternal_StateType   channelState;
    Ptr2VoidFunction_t      channelCbk;
    uint8                   channelNotificationStatus;
}GptInternal_ChannelInfo;


typedef enum
{
    BITWIDH_16=16,
    BITWIDH_24=24,
    BITWIDH_32=32,
    BITWIDH_64=64
}GptInternal_BitSizeType;

typedef enum
{
    COUNT_DOWN_DIRECTION,
    COUNT_UP_DIRECTION  
}GptInternal_CountDirectionType;

typedef enum
{
    PRESCALER_VAL_0,
    PRESCALER_VAL_1
}GptInternal_PrescalerType;


typedef uint8 GptInternal_FreqType;

typedef struct 
{  
    Gpt_ChannelType                 channelID;
    GptChannelMode                  channelMode;
    GptInternal_FreqType            channelFreqHz ;
    Gpt_ValueType                   channelTickValMax;   
    GptPtrNotificationCbkType       channelNotificationCbk;

    GptInternal_CountDirectionType  channelCountDirection;
    GptInternal_BitSizeType         channelBitWidth;
    GptInternal_PrescalerType       channelPrescaler;
}Gpt_ChannelConfigType;

typedef struct
{
    const uint8                        numberChannels;  
    const Gpt_ChannelConfigType       *p2ChannelsCfg;                
}Gpt_ConfigType;
#endif /* GPT_TYPES_H */
