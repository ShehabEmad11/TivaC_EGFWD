#ifndef PORT_CFG_H
#define PORT_CFG_H

#include "Port_Types.h"

#define NUMBER_GPIO_PORTS   (6u)


/*TODO: define complete config*/
                                /*PinMode     Direction        Level         Connection          DriveStrength*/
#define PORTA_PINS_CONFIG       {\
/*PINA0*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINA1*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINA2*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINA3*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINA4*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINA5*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINA6*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINA7*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
                                }

                                /*PinMode     Direction        Level         Connection          DriveStrength*/
#define PORTB_PINS_CONFIG       {\
/*PINB0*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
/*PINB1*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
/*PINB2*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
/*PINB3*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
/*PINB4*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
/*PINB5*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
/*PINB6*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
/*PINB7*/                         {GPIO        ,OUTPUT       ,STD_LOW      ,CONNECTION_DEFAULT   ,CURRENT_2mA}, \
                                }},

                                /*PinMode     Direction        Level         Connection          DriveStrength*/
#define PORTC_PINS_CONFIG       {\
/*PINC0*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
/*PINC1*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
/*PINC2*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
/*PINC3*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
/*PINC4*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
/*PINC5*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
/*PINC6*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
/*PINC7*/                         {GPIO        ,INPUT       ,STD_HIGH         ,PULL_UP           ,CURRENT_DEFAULT}, \
                                }
                                /*PinMode     Direction        Level         Connection          DriveStrength*/
#define PORTD_PINS_CONFIG       {\
/*PIND0*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
/*PIND1*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
/*PIND2*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
/*PIND3*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
/*PIND4*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
/*PIND5*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
/*PIND6*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
/*PIND7*/                         {GPIO        ,INPUT       ,STD_LOW         ,PULL_DOWN           ,CURRENT_DEFAULT}, \
                                }

                                /*PinMode     Direction        Level         Connection          DriveStrength*/
#define PORTE_PINS_CONFIG       {\
/*PINE0*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINE1*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINE2*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINE3*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINE4*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINE5*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*N/A                             {PORT_NA     ,PORT_NA      ,PORT_NA      ,PORT_NA              ,PORT_NA    }, \
/*N/A                             {PORT_NA     ,PORT_NA      ,PORT_NA      ,PORT_NA              ,PORT_NA    }, \*/
                                }

                                /*PinMode     Direction        Level         Connection          DriveStrength*/
#define PORTF_PINS_CONFIG       {\
/*PINF0*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINF1*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINF2*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINF3*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*PINF4*/                         {GPIO        ,OUTPUT       ,STD_HIGH     ,CONNECTION_DEFAULT   ,CURRENT_4mA}, \
/*N/A                             {PORT_NA     ,PORT_NA      ,PORT_NA      ,PORT_NA              ,PORT_NA    }, \
/*N/A                             {PORT_NA     ,PORT_NA      ,PORT_NA      ,PORT_NA              ,PORT_NA    }, \
/*N/A                             {PORT_NA     ,PORT_NA      ,PORT_NA      ,PORT_NA              ,PORT_NA    }, \*/
                                }



                                        /*numberPins*/          /*astrPins[8]*/ 
#define PORTA_CONFIGURATIONS                8           ,       PORTA_PINS_CONFIG
#define PORTB_CONFIGURATIONS                8           ,       PORTB_PINS_CONFIG
#define PORTC_CONFIGURATIONS                8           ,       PORTC_PINS_CONFIG
#define PORTD_CONFIGURATIONS                8           ,       PORTD_PINS_CONFIG
#define PORTE_CONFIGURATIONS                6           ,       PORTE_PINS_CONFIG
#define PORTF_CONFIGURATIONS                5           ,       PORTF_PINS_CONFIG

#endif /* PORT_CFG_H */
