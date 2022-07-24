#ifndef PORT_TYPES_H
#define PORT_TYPES_H

#include "Std_Types.h"

typedef Std_ValuesType PortPinLevelValueType;

typedef enum 
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
}Internal_Port_Type;


typedef enum
{
    PA0 = 0,
    PA1,
    PA2,
    PA3,
    PA4,
    PA5,
    PA6,
    PA7 = 7,

    PB0 = 8,
    PB1,
    PB2,
    PB3,
    PB4,
    PB5,
    PB6,
    PB7 = 15,

    PC0 = 16,
    PC1,
    PC2,
    PC3,
    PC4,
    PC5,
    PC6,
    PC7 = 23,

    PD0 = 24,
    PD1,
    PD2,
    PD3,
    PD4,
    PD5,
    PD6,
    PD7 = 31,

    PE0 = 32,
    PE1,
    PE2,
    PE3,
    PE4,
    PE5 = 37, 
 /* PE6
    PE7 */

    PF0 = 40,
    PF1,
    PF2,
    PF3,
    PF4 = 44
 /* PF5,
    PF6,
    PF7 */
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
    ADC,
    JTAG,
    SWD
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

#if 0
typedef struct 
{
    Port_PinModeType             mode;           /*{Uart , GPIO, ....}*/
    Port_PinDirectionType        direction;      /*If GPIO : input/output*/
    PortPinLevelValueType        level;          /*if output ---> HIGH,LOW*/
    Port_PinInternalAttachType   connection;     /*PullUp/Down/OpenDrain*/
    Port_PinOutputCurrentType    driveStrength;     /*2mA, 4mA, 8mA*/
}Pin_ConfigType;
#endif

typedef void (*PortPin_FunctionCbkType)(void);

typedef enum
{
    HIGH_LEVEL_TRIGGER,
    LOW_LEVEL_TRIGGER,

    RISING_EDGE_TRIGGER,
    FALLING_EDGE_TRIGGER,
    BOTH_EDGE_TRIGGER,
    DEFAULT_TRIGGER
}Port_PinTriggerModeType;

typedef struct
{
    Port_PinType                 pinID;          /*PIN_A0, PIN_B1,.....*/
    Port_PinModeType             mode;           /*{Uart , GPIO, ....}*/
    Port_PinDirectionType        direction;      /*If GPIO : input/output*/
    PortPinLevelValueType        level;          /*if output ---> HIGH,LOW*/
    Port_PinInternalAttachType   connection;     /*PullUp/Down/OpenDrain*/
    Port_PinOutputCurrentType    driveStrength;     /*2mA, 4mA, 8mA*/
    uint8                        isInterruptEnabled;  
    PortPin_FunctionCbkType      callBackFunc;
    Port_PinTriggerModeType      triggerMode;     /*HIGH/LOW Level triggered or RISING/FALLING/BOTH Edges Triggered*/

}Port_ConfigType;


typedef struct 
{
    PortPin_FunctionCbkType      callBackFunc;
}PortInternal_PinInfo;

#endif /* PORT_TYPES_H */
