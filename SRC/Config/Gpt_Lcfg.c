#include "Std_Types.h"
#include "Gpt_Types.h"
#include "Gpt_Cfg.h"

#if 0
extern void cbk (void)
{
    asm("nop");
}


#define GPT_CHANNELS_CONFIGURATION   \
{\
TIMER_32_64_TIMER0,GPT_CH_MODE_CONTINUOUS,16,4294967295ul,cbk,COUNT_DOWN_DIRECTION,BITWIDH_32,PRESCALER_VAL_0\
}

#define GPT_CONFIG          \
{\
    NUMBER_GPT_CONFIGURED_CHANNELS,{GPT_CHANNELS_CONFIGURATION}\
}


const Gpt_ConfigType GptChannelConfigs[]= GPT_CONFIG ;
#endif


const Gpt_ConfigType GptChannelConfigs[] ;
