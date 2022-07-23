#include "Std_Types.h"
#include "Gpt_Types.h"
#include "Gpt_Cfg.h"

const Gpt_ChannelConfigType GptChannelConfigs[NUMBER_GPT_CONFIGURED_CHANNELS]=
{
    GPT_CHANNELS_CONFIGURATION
};
const Gpt_ConfigType GptConfig={NUMBER_GPT_CONFIGURED_CHANNELS,&GptChannelConfigs};
