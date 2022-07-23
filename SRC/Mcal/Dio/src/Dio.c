#include "Dio.h"
#include "Port_Private.h"



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

    addressOffsetVal=(uint16) ( (uint16)1 << ((uint16)pinOffset + (uint16)2) ) ;

    writeVal=(uint8)Level<<pinOffset;

    *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[portId].GPIODATA) + addressOffsetVal ) ) = writeVal;
}


extern void Dio_WritePort (Dio_PortType PortId , Dio_PortLevelType Level)
{
    uint16 addressOffsetVal;  

    addressOffsetVal= (uint16)((uint16)0x00FF <<(uint16)2);

   *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) ) = Level;
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

    addressOffsetVal=(uint16) ( (uint16)1 << ((uint16)pinOffset + (uint16)2) ) ;

    readVal= *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[portId].GPIODATA) + addressOffsetVal ) );

    readVal >>= pinOffset;

    return readVal;
}

extern Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId)
{
    uint16 addressOffsetVal;  
    Dio_PortLevelType readVal;

    addressOffsetVal= (uint16) ((uint16)0x00FF << (uint16)2);

    readVal= *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[PortId].GPIODATA) + addressOffsetVal ) );

    return readVal;
    
}


Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId)
{
    uint8 portId;
    uint16 addressOffsetVal;  
    uint8 pinOffset;
    uint8 writeVal;
    uint8 readVal;
    
    Dio_LevelType dummy=0;

    /*Get PortId*/
    portId= ChannelId / 8;

    /*Get PIN offset inside PORT register*/
    pinOffset= ChannelId % 8;

    addressOffsetVal=(uint16) ( (uint16)1 << ((uint16)pinOffset + (uint16)2) ) ;

    readVal= *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[portId].GPIODATA) + addressOffsetVal ) );

    writeVal=(readVal ^ ((uint8)1<<pinOffset));

    *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[portId].GPIODATA) + addressOffsetVal ) ) = writeVal;

    return dummy;
}
