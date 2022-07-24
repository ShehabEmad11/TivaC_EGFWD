#include "Port.h"
#include "Port_Cfg.h"
#include "Port_Private.h"
#include "Macros.h"

static PortInternal_PinInfo PinsArrInfo[NUMBER_GPIO_PINS];
extern void Port_Init(const Port_ConfigType* ConfigPtr)
{
    uint8 configIter;

    uint8 pinNumber;
    uint8 currentPin;
    uint8 currentPort;
    uint8 writeVal;
    uint16 addressOffsetVal;

    for(configIter=0; configIter<NUMBER_PINS_CONFIGURED; configIter++)
    {
        pinNumber=ConfigPtr[configIter].pinID;
        currentPort =  pinNumber/8;
        currentPin  =  pinNumber%8;
        
        if(ConfigPtr[configIter].mode == GPIO)
        {
            /*Clear bit in AFSEL to indicate a GPIO*/
            CLR_BIT(GPIO_P2str[currentPort].GPIOAFSEL , currentPin);

            if(ConfigPtr[currentPort].direction == INPUT)
            {
                CLR_BIT(GPIO_P2str[currentPort].GPIODIR , currentPin);

                if(ConfigPtr[configIter].isInterruptEnabled==STD_ON)
                {
                    /*Mask Interrupt Before any further configurations*/
                    CLR_BIT(GPIO_P2str[currentPort].GPIOIM,currentPin);

                    /*Store Callback function in local Array*/
                    PinsArrInfo[pinNumber].callBackFunc=ConfigPtr[configIter].callBackFunc;

                    switch(ConfigPtr[configIter].triggerMode)
                    {
                        case HIGH_LEVEL_TRIGGER:
                            /*Setting Interrupt Sense as Level Interrupt*/
                            SET_BIT(GPIO_P2str[currentPort].GPIOIS,currentPin);
                            /*Setting Interrupt Event as HIGH LEVEL*/
                            SET_BIT(GPIO_P2str[currentPort].GPIOIEV,currentPin);
                            break;
                    
                        case LOW_LEVEL_TRIGGER:
                            /*Setting Interrupt Sense as Level Interrupt*/
                            SET_BIT(GPIO_P2str[currentPort].GPIOIS,currentPin);
                            /*Setting Interrupt Event as LOW LEVEL*/
                            CLR_BIT(GPIO_P2str[currentPort].GPIOIEV,currentPin);
                            break;

                        case RISING_EDGE_TRIGGER:
                            /*Setting Interrupt Sense as EDGE Interrupt*/
                            CLR_BIT(GPIO_P2str[currentPort].GPIOIS,currentPin);
                            /*Setting Interrupt GENERATION TO be controllerd by Interrupt Event Register*/
                            CLR_BIT(GPIO_P2str[currentPort].GPIOIBE,currentPin);
                            /*Setting INterrupt Event as Rising Edge*/
                            SET_BIT(GPIO_P2str[currentPort].GPIOIEV,currentPin);
                            break;

                        case FALLING_EDGE_TRIGGER:
                            /*Setting Interrupt Sense as EDGE Interrupt*/
                            CLR_BIT(GPIO_P2str[currentPort].GPIOIS,currentPin);
                            /*Setting Interrupt GENERATION TO be controllerd by Interrupt Event Register*/
                            CLR_BIT(GPIO_P2str[currentPort].GPIOIBE,currentPin);
                            /*Setting INterrupt Event as FALLING Edge*/
                            CLR_BIT(GPIO_P2str[currentPort].GPIOIEV,currentPin);
                            break;
                        case BOTH_EDGE_TRIGGER:
                            /*Setting Interrupt Sense as EDGE Interrupt*/
                            CLR_BIT(GPIO_P2str[currentPort].GPIOIS,currentPin);
                            /*Setting Interrupt GENERATION TO be BOTH EDGES*/
                            SET_BIT(GPIO_P2str[currentPort].GPIOIBE,currentPin);
                            break;
                    }
                    /*Clear The Corresponding Interrupt to avoid Trigger False interrupt because of config*/
                    SET_BIT(GPIO_P2str[currentPort].GPIORIS,currentPin);

                    if(ConfigPtr[configIter].callBackFunc != NULL_PTR)
                    {
                        /*Todo ASsign callback to specific interrupt*/
                    }
                }
            }
            else if(ConfigPtr[currentPort].direction == OUTPUT)
            {
                SET_BIT(GPIO_P2str[currentPort].GPIODIR , currentPin);

                /*Set Level*/
                if(ConfigPtr[currentPort].level == STD_HIGH 
                || ConfigPtr[currentPort].level == STD_LOW)
                {
                    addressOffsetVal=(uint16) ( (uint16)1 << ((uint16)currentPin + (uint16)2) ) ;

                    writeVal=(uint8)((uint8) (ConfigPtr[currentPort].level) << currentPin);
                    
                    *( (volatile uint8*) ( ((volatile uint8*)&GPIO_P2str[currentPort].GPIODATA) + addressOffsetVal ) ) = writeVal;
                }

                /*Set Drive Strength*/
                switch(ConfigPtr[currentPort].driveStrength)
                {
                    case CURRENT_2mA:
                    default:
                    case CURRENT_DEFAULT:   
                        SET_BIT(GPIO_P2str[currentPort].GPIODR2R , currentPin);
                        break;
                
                    case CURRENT_4mA:
                        SET_BIT(GPIO_P2str[currentPort].GPIODR4R , currentPin);
                        break;

                    case CURRENT_8mA:
                        SET_BIT(GPIO_P2str[currentPort].GPIODR8R , currentPin);
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
            SET_BIT(GPIO_P2str[currentPort].GPIOAFSEL , currentPin);

            /*TODO: Select Alternate Fucntion value from Mapping*/
            //mapValue=......
            //GPIO_P2str[portIter].GPIOPCTL |= ((mapValue & 0x0000000F) << (pinIter*4));
        }

        switch(ConfigPtr[currentPort].connection)
        {
            case PULL_UP:
                SET_BIT(GPIO_P2str[currentPort].GPIOPUR , currentPin);
                break;
            case PULL_DOWN:
                SET_BIT(GPIO_P2str[currentPort].GPIOPDR , currentPin);
                break;
            case OPEN_DRAIN:
                SET_BIT(GPIO_P2str[currentPort].GPIOODR , currentPin);
                break;
            case CONNECTION_DEFAULT:
            default:
                break;
        }


        /*Enable/Disable Digital Functionality GPIO/Alternate function*/
        if(ConfigPtr[currentPort].mode != MODE_DEFAULT)
        {
            SET_BIT(GPIO_P2str[currentPort].GPIODEN , currentPin);
        }
        else
        {
            /*Disable Digital Functionality if pin not configured*/
            CLR_BIT(GPIO_P2str[currentPort].GPIODEN , currentPin);
        }

        /*Enable/Disable Interrupt*/
        if(ConfigPtr[configIter].isInterruptEnabled==STD_ON)
        {
            /*Mask Interrupt Before any further configurations*/
            SET_BIT(GPIO_P2str[currentPort].GPIOIM,currentPin);
        }
        else
        {
            /*Mask Interrupt Before any further configurations*/
            CLR_BIT(GPIO_P2str[currentPort].GPIOIM,currentPin);
        }
    }
}



void GPIOF_Handler(void)
{
    uint32 maskedInterrupts;
    uint8 currentPinNumber;
    uint8 pinIter;

    /*Check Which Pin has Currently Intterrupt and call its callback function*/
    maskedInterrupts=GPIO_P2str[PORTF].GPIOMIS;

    for(pinIter=0; pinIter<8; pinIter++)
    {
        currentPinNumber=(PORTF * 8)  + pinIter;
        if( (maskedInterrupts >> pinIter) & 0x01 == 1)
        {
            if(PinsArrInfo[currentPinNumber].callBackFunc != NULL_PTR)
            {
                PinsArrInfo[currentPinNumber].callBackFunc();
            }
        }
        /*Clear Interrupt*/
        SET_BIT(GPIO_P2str[PORTF].GPIOICR , pinIter);
    }
}