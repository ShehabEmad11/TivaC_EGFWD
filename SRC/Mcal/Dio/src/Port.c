/*
API_TYPES:
Port_PinType
Port_PinDirectionType
Port_PinModeType
Port_PinInternalAttachType
Port_PinOutputCurrentType
Port_ConfigType



Api_Functions:
void Port_Init(const Port_ConfigType* ConfigPtr);


Configurations:
PortPinMode       :Uart , GPIO, ....
PortPinLevelValue       if output ---> HIGH,LOW
PortPinDirection        If GPIO : input/output
PortPinInternalAttach   PullUp/Down/OpenDrain
PortPinOutputCurrent    
*/

#include "Port.h"
#include "Port_Cfg.h"
#include "Mcu_Hw.h"
#include "Macros.h"


/*InitSequence
1. Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register (see
page 340). In addition, the SCGCGPIO and DCGCGPIO registers can be programmed in the
same manner to enable clocking in Sleep and Deep-Sleep modes.
2. Set the direction of the GPIO port pins by programming the GPIODIR register. A write of a 1
indicates output and a write of a 0 indicates input.
3. Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin. If an alternate
pin is chosen for a bit, then the PMCx field must be programmed in the GPIOPCTL register for
the specific peripheral required. There are also two registers, GPIOADCCTL and GPIODMACTL,
which can be used to program a GPIO pin as a ADC or μDMA trigger, respectively.
4. Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8R
registers.
5. Program each pad in the port to have either pull-up, pull-down, or open drain functionality through
the GPIOPUR, GPIOPDR, GPIOODR register. Slew rate may also be programmed, if needed,
through the GPIOSLR register.
6. To enable GPIO pins as digital I/Os, set the appropriate DEN bit in the GPIODEN register. To
enable GPIO pins to their analog function (if available), set the GPIOAMSEL bit in the
GPIOAMSEL register.
7. Program the GPIOIS, GPIOIBE, GPIOEV, and GPIOIM registers to configure the type, event,
and mask of the interrupts for each port.
Note: To prevent false interrupts, the following steps should be taken when re-configuring
GPIO edge and interrupt sense registers:
a. Mask the corresponding port by clearing the IME field in the GPIOIM register.
b. Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE
register.
c. Clear the GPIORIS register.
d. Unmask the port by setting the IME field in the GPIOIM register.
8. Optionally, software can lock the configurations of the NMI and JTAG/SWD pins on the GPIO
port pins, by setting the LOCK bits in the GPIOLOCK register.
When the internal POR signal is asserted and until otherwise configured, all GPIO pins are configured
to be undriven (tristate): GPIOAFSEL=0, GPIODEN=0, GPIOPDR=0, and GPIOPUR=0, except for
the pins shown in Table 10-1 on page 650. Table 10-3 on page 657 shows all possible configurations
of the GPIO pads and the control register settings required to achieve them. Table 10-4 on page 658
shows how a rising edge interrupt is configured for pin 2 of a GPIO port.
*/

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
