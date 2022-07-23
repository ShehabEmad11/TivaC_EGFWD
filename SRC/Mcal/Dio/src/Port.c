#include "Port.h"
#include "Port_Cfg.h"
#include "Port_Private.h"
#include "Macros.h"

extern void Port_Init(const Port_ConfigType* ConfigPtr)
{
    uint8 pinIter;
    uint8 portIter;
    uint8 writeVal;
    uint16 addressOffsetVal;
    for(portIter=0; portIter<NUMBER_GPIO_PORTS; portIter++)
    {
        if(ConfigPtr[portIter].numberPins > 8)
        {
            /*Error*/
            continue;
        }
        for(pinIter=0; pinIter<ConfigPtr[portIter].numberPins; pinIter++)
        {
            if(ConfigPtr[portIter].astrPins[pinIter].mode == GPIO)
            {
                /*Clear bit in AFSEL to indicate a GPIO*/
                CLR_BIT(GPIO_P2str[portIter].GPIOAFSEL , pinIter);

                if(ConfigPtr[portIter].astrPins[pinIter].direction == INPUT)
                {
                    CLR_BIT(GPIO_P2str[portIter].GPIODIR , pinIter);
                }
                else if(ConfigPtr[portIter].astrPins[pinIter].direction == OUTPUT)
                {
                    SET_BIT(GPIO_P2str[portIter].GPIODIR , pinIter);

                    /*Set Level*/
                    if(ConfigPtr[portIter].astrPins[pinIter].level == STD_HIGH 
                    || ConfigPtr[portIter].astrPins[pinIter].level == STD_LOW)
                    {
                        addressOffsetVal=(uint16) ( (uint16)1 << ((uint16)pinIter + (uint16)2) ) ;

                        writeVal=(uint8)((uint8) (ConfigPtr[portIter].astrPins[pinIter].level) << pinIter);
                        
                        *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[portIter].GPIODATA) + addressOffsetVal ) ) = writeVal;
                    }

                    /*Set Drive Strength*/
                    switch(ConfigPtr[portIter].astrPins[pinIter].driveStrength)
                    {
                        case CURRENT_2mA:
                        default:
                        case CURRENT_DEFAULT:   
                            SET_BIT(GPIO_P2str[portIter].GPIODR2R , pinIter);
                            break;
                    
                        case CURRENT_4mA:
                            SET_BIT(GPIO_P2str[portIter].GPIODR4R , pinIter);
                            break;

                        case CURRENT_8mA:
                            SET_BIT(GPIO_P2str[portIter].GPIODR8R , pinIter);
                            break;
                    }
                }
                else
                {
                    /*Error*/
                }
            }
            else
            {
                /*Enable Alternate Function*/
                SET_BIT(GPIO_P2str[portIter].GPIOAFSEL , pinIter);

                /*TODO: Select Alternate Fucntion value from Mapping*/
                //mapValue=......
                //GPIO_P2str[portIter].GPIOPCTL |= ((mapValue & 0x0000000F) << (pinIter*4));
            }

            switch(ConfigPtr[portIter].astrPins[pinIter].connection)
            {
                case PULL_UP:
                    SET_BIT(GPIO_P2str[portIter].GPIOPUR , pinIter);
                    break;
                case PULL_DOWN:
                    SET_BIT(GPIO_P2str[portIter].GPIOPDR , pinIter);
                    break;
                case OPEN_DRAIN:
                    SET_BIT(GPIO_P2str[portIter].GPIOODR , pinIter);
                    break;
                case CONNECTION_DEFAULT:
                default:
                    break;
            }


            /*Enable/Disable Digital Functionality GPIO/Alternate function*/
            if(ConfigPtr[portIter].astrPins[pinIter].mode != MODE_DEFAULT)
            {
                SET_BIT(GPIO_P2str[portIter].GPIODEN , pinIter);
            }
            else
            {
                /*Disable Digital Functionality if pin not configured*/
                CLR_BIT(GPIO_P2str[portIter].GPIODEN , pinIter);
            }
        }

    }
}
