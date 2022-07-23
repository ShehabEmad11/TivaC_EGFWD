#ifndef DIO_TYPES_H
#define DIO_TYPES_H

#include "Std_Types.h"

typedef enum 
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F
}Dio_PortType;

typedef enum
{
    PIN_A0 = 0,
    PIN_A1,
    PIN_A2,
    PIN_A3,
    PIN_A4,
    PIN_A5,
    PIN_A6,
    PIN_A7 = 7,

    PIN_B0 = 8,
    PIN_B1,
    PIN_B2,
    PIN_B3,
    PIN_B4,
    PIN_B5,
    PIN_B6,
    PIN_B7 = 15,

    PIN_C0 = 16,
    PIN_C1,
    PIN_C2,
    PIN_C3,
    PIN_C4,
    PIN_C5,
    PIN_C6,
    PIN_C7 = 23,

    PIN_D0 = 24,
    PIN_D1,
    PIN_D2,
    PIN_D3,
    PIN_D4,
    PIN_D5,
    PIN_D6,
    PIN_D7 = 31,

    PIN_E0 = 32,
    PIN_E1,
    PIN_E2,
    PIN_E3,
    PIN_E4,
    PIN_E5 = 37, 
 /* PIN_E6
    PIN_E7 */

    PIN_F0 = 40,
    PIN_F1,
    PIN_F2,
    PIN_F3,
    PIN_F4 = 44
 /* PIN_F5,
    PIN_F6,
    PIN_F7 */
}Dio_ChannelType;

typedef uint8 Dio_LevelType;
typedef uint8 Dio_PortLevelType;



#endif /* DIO_TYPES_H */
