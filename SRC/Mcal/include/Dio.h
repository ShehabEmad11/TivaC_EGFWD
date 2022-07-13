#ifndef DIO_H
#define DIO_H

#include "Dio_Types.h"
#include "Std_Types.h"

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
void Dio_WriteChannel (Dio_ChannelType ChannelId , Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);
void Dio_WritePort (Dio_PortType PortId , Dio_PortLevelType Level);
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId);

#endif /* DIO_H */
