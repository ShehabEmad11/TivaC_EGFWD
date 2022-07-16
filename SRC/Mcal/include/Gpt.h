#ifndef GPT_H
#define GPT_H

#include "Std_Types.h"
#include "Gpt_Cfg.h"


extern void Gpt_Init(const Gpt_ConfigType* ConfigPtr);
extern void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );

#endif /* GPT_H */
