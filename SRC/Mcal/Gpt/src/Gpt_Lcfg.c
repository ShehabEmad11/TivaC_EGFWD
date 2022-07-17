#include "Std_Types.h"
#include "Gpt_Types.h"
#include "Gpt_Cfg.h"

//const static Gpt_ChannelConfigType GptChannelConfigs=GPT_CHANNELS_CONFIGURATION;

/*
    {
        .channelID=TIMER_32_64_TIMER0,
        .channelMode=GPT_CH_MODE_CONTINUOUS,
        .channelFreqHz=16,
        .channelTickValMax=(uint32)0x00FFFFFF,
        .channelNotificationCbk=TIM_CallBack,
        .channelCountDirection= COUNT_DOWN_DIRECTION,
        .channelBitWidth=   BITWIDH_32,
        .channelPrescaler=PRESCALER_VAL_0
    },
*/

const Gpt_ChannelConfigType GptChannelConfigs[NUMBER_GPT_CONFIGURED_CHANNELS]=
{
    GPT_CHANNELS_CONFIGURATION
};
const Gpt_ConfigType GptConfig={NUMBER_GPT_CONFIGURED_CHANNELS,&GptChannelConfigs};
