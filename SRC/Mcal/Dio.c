
/*Task1:
No User Configurations
BIT BANDING/BIT MASK
functions must be re-entrant  (read-Modify_write not exist)

API Functions:
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId)
void Dio_WriteChannel (Dio_ChannelType ChannelId , Dio_LevelType Level)
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId)
void Dio_WritePort (Dio_PortType PortId , Dio_PortLevelType Level)
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId)
*/

/*
All GPIO signals are 5-V tolerant when configured as inputs
except for PD4, PD5, PB0 and PB1, which are limited to 3.6 V
*/
#include "Dio.h"
#include "Mcu_Hw.h"



extern void Dio_WriteChannel (Dio_ChannelType ChannelId , Dio_LevelType Level)
{
    uint8 portId;
    uint16 addressOffsetVal;  
    uint8 pinOffset;
    uint8 writeVal;

    /*Get PortId*/
    portId= ChannelId / 8;

    /*Get PIN offset inside PORT register*/
    pinOffset= ChannelId % 8;

    addressOffsetVal=((uint16) pinOffset & 0x00FF )<<2;

    writeVal=Level<<pinOffset;

    *( (uint8*) ( ((uint8 *)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) ) = writeVal;
}


extern void Dio_WritePort (Dio_PortType PortId , Dio_PortLevelType Level)
{
    uint16 addressOffsetVal;  

    addressOffsetVal= 0x00FF << 2;

   *( (uint8*) ( ((uint8 *)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) ) = Level;
}


extern Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId)
{
    uint8 portId;
    uint16 addressOffsetVal;  
    uint8 pinOffset;
    Dio_LevelType readVal;

    /*Get PortId*/
    portId= ChannelId / 8;

    /*Get PIN offset inside PORT register*/
    pinOffset= ChannelId % 8;

    addressOffsetVal=((uint16) pinOffset & 0x00FF )<<2;


    readVal= *( (uint8*) ( ((uint8 *)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) );

    readVal >>= pinOffset;

    return readVal;
}

extern Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId)
{
    uint16 addressOffsetVal;  
    Dio_PortLevelType readVal;

    addressOffsetVal= 0x00FF << 2;

    readVal= *( (uint8*) ( ((uint8 *)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) );

    return readVal;
    
}


Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId)
{
    uint8 portId;
    uint16 addressOffsetVal;  
    uint8 pinOffset;
    uint8 writeVal;
    uint8 readVal
    
    Dio_LevelType dummy;

    /*Get PortId*/
    portId= ChannelId / 8;

    /*Get PIN offset inside PORT register*/
    pinOffset= ChannelId % 8;

    addressOffsetVal=((uint16) pinOffset & 0x00FF )<<2;


    readVal= *( (uint8*) ( ((uint8 *)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) );

    writeVal=(readVal ^ (1<<pinOffset));

    *( (uint8*) ( ((uint8 *)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) ) = writeVal;

    return dummy;
}