#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/*
Port_PinType
Port_PinDirectionType
Port_PinModeType
Port_PinInternalAttachType
Port_PinOutputCurrentType
Port_ConfigType
*/

typedef Std_ValuesType PortPinLevelValueType;

typedef enum
{
    PORT_A0 = 0,
    PORT_A1,
    PORT_A2,
    PORT_A3,
    PORT_A4,
    PORT_A5,
    PORT_A6,
    PORT_A7 = 7,

    PORT_B0 = 8,
    PORT_B1,
    PORT_B2,
    PORT_B3,
    PORT_B4,
    PORT_B5,
    PORT_B6,
    PORT_B7 = 15,

    PORT_C0 = 16,
    PORT_C1,
    PORT_C2,
    PORT_C3,
    PORT_C4,
    PORT_C5,
    PORT_C6,
    PORT_C7 = 23,

    PORT_D0 = 24,
    PORT_D1,
    PORT_D2,
    PORT_D3,
    PORT_D4,
    PORT_D5,
    PORT_D6,
    PORT_D7 = 31,

    PORT_E0 = 32,
    PORT_E1,
    PORT_E2,
    PORT_E3,
    PORT_E4,
    PORT_E5 = 37, 
 /* PORT_E6
    PORT_E7 */

    PORT_F0 = 40,
    PORT_F1,
    PORT_F2,
    PORT_F3,
    PORT_F4 = 44
 /* PORT_F5,
    PORT_F6,
    PORT_F7 */
}Port_PinType;


typedef enum
{
    MODE_DEFAULT,
    GPIO,
    UART_Tx,
    UART_Rx,
    SPI_MISO,
    SPI_MOSI,
    SPI_CS,
    SPI_CLK,
    I2C_SDA,
    I2C_SCL,
    TIMER,
    PWM,
    ADC
}Port_PinModeType;

typedef enum
{
    DIRECTION_DEFAULT,
    INPUT,
    OUTPUT
}Port_PinDirectionType;


typedef enum
{
    CONNECTION_DEFAULT,
    PULL_UP,
    PULL_DOWN,
    OPEN_DRAIN
}Port_PinInternalAttachType;

typedef enum
{
    CURRENT_DEFAULT,
    CURRENT_2mA,
    CURRENT_4mA,
    CURRENT_8mA
}Port_PinOutputCurrentType;

typedef struct 
{
    Port_PinModeType             mode;           //{Uart , GPIO, ....}
    Port_PinDirectionType        direction;      //If GPIO : input/output
    PortPinLevelValueType        level;          //if output ---> HIGH,LOW
    Port_PinInternalAttachType   connection;     //PullUp/Down/OpenDrain
    Port_PinOutputCurrentType    driveStrength;     //2mA, 4mA, 8mA
}Pin_ConfigType;


typedef struct
{
    uint8 numberPins;
    Pin_ConfigType astrPins[8];            //Array of 8 pins 
}Port_ConfigType;



#endif /* PORT_TYPES_H */
