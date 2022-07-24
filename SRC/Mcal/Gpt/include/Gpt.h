#ifndef GPT_H
#define GPT_H

#include "Std_Types.h"
#include "Gpt_Cfg.h"


extern void Gpt_Init(const Gpt_ConfigType* ConfigPtr);
extern void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
extern void Gpt_StopTimer(Gpt_ChannelType Channel);
extern void Gpt_EnableNotification( Gpt_ChannelType Channel );
extern void Gpt_DisableNotification( Gpt_ChannelType Channel );
#endif /* GPT_H */
