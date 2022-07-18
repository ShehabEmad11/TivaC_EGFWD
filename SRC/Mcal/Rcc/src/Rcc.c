/*Select OSCSRC from RCC/RCC2*/
/*Enable PLL if it will be used from XTAL/PWRDN from RCC/RCC2*/
/*If PLL is enabled select if Divide / 2 or not (optional) from DIV400 bit at RCC2*/
/*If PLL is enabled select the SYSDIV value (mandatory) from RCC2*/
/*Select If we will use PLL or not by BYPASS from RCC/RCC2*/
/*If PLL is used keep Polling on PLL lock*/

#include "Macros.h"
#include "Std_Types.h"
#include "Rcc.h"
#include "Rcc_Cfg.h"
#include "Rcc_Types.h"
#include "Rcc_Private.h"


typedef enum
{
    WDG                             =0x00,
    TIMER_16_32                     =(PERIPH_TIMER_16_32_RUN_TIMER0>>8),
    GPIO                            =(PERIPH_GPIO_RUN_PA>>8),
    DMA               				=0x03,				
	HIBERNATION       				=0x04,
	UART              				=0x05,				
	SPI               				=0x06,				
	I2C               				=0x07,				
	USB               				=0x08,				
	CAN               				=0x09,				
	ADC               				=0x0A,
	ANALOG_COMPARATOR			    =0x0B,
	PWM              				=0x0C,		
	QUADRATURE       				=0x0D,
	EEPROM           				=0x0E,
    TIMER_32_64                     =(PERIPH_TIMER_32_64_RUN_TIMER0>>8)
}Rcc_InternalPeriph_t;

typedef enum
{
    RUN_MODE,
    SLEEP_MODE,
    DEEPSLEEP_MODE
}Rcc_InternalMode_t;

/*Refer to Figure 5-5. Main Clock Tree*/
/*Refer to Table 5-3. Clock Source Options */
extern void Rcc_InitSysClock(void)
{
    #if(SYSTEM_CLOCK != PLL_OUT)
    {
        /*ByPass PLL*/
        SYSCTRL_P2strRegs->RCC.fieldAccess.BYPASS=1;

        /*Power Down PLL (This Step must be after setting the BYPASS bit)*/
        SYSCTRL_P2strRegs->RCC.fieldAccess.PWRDN=1;

        #if(SYSTEM_CLOCK == PERCISION_INTERNAL_OSCILATOR)
        {
            /*Select Source*/
            SYSCTRL_P2strRegs->RCC.fieldAccess.OSCSRC=1;

            /*Disable Main Oscilator*/
            SYSCTRL_P2strRegs->RCC.fieldAccess.MOSCDIS=1;
        }
        #elif(SYSTEM_CLOCK == PERCISION_INTERNAL_OSCILATOR_DIV4)
        {
            /*Select Source*/
            SYSCTRL_P2strRegs->RCC.fieldAccess.OSCSRC=2;

            /*Disable Main Oscilator*/
            SYSCTRL_P2strRegs->RCC.fieldAccess.MOSCDIS=1;
        }
        #else
        {
            /*TODO: HANDLE OTHER CLK SOURCES*/
        }
        #endif

        /*Divide Clock if applicable*/
        #if(SYSTEM_CLOCK_DIVIDER == STD_ON)
            SYSCTRL_P2strRegs->RCC.fieldAccess.SYSDIV = SYSTEM_CLOCK_DIVIDER_VALUE;
            SYSCTRL_P2strRegs->RCC.fieldAccess.USESYSDIV = 1;
        #else
            SYSCTRL_P2strRegs->RCC.fieldAccess.USESYSDIV = 0;
        #endif    
    }
    #else
    {
        /*TODO: Handle PLL INIT*/
    }
    #endif
}

extern void Rcc_voidEnablePeripheral(Rcc_PeripheralType Peripheral)
{
    uint8 peripheralID;
    uint8 mode;
    uint8 subPeripheralOffset;
    
    /*Decoding: TWO BYTES:-   0x 0PMSS 
    Byte(1) decides peripheal ID
    Byte(0).High decides Mode  (0==RUN  1==Sleep  2==DeepSleep)
    Byte(0).LOW  decides SubPeripheral Offset*/

    peripheralID= (uint8) ( ((uint16) 0xFF00 &  Peripheral) >> 8u);
    mode=(uint8) ( ((uint16) 0x00F0 & Peripheral) >> 4u);
    subPeripheralOffset= (uint8)  ( (uint16)0x000F  & Peripheral); 

    switch (peripheralID)
    {
    case WDG:
        /*TODO: Complete Init*/;
        break;

    case TIMER_16_32:
        switch(mode)
        {
            case RUN_MODE:
                SET_BIT(SYSCTRL_P2strRegs->RCGCTIMER, subPeripheralOffset);
                break;
            case SLEEP_MODE:
            /*TODO: Complete Init*/
                break;
            case DEEPSLEEP_MODE:
            /*TODO: Complete Init*/
                break;    
            default:
                break;
        }
        break;
    
    case GPIO:
        switch(mode)
        {
            case RUN_MODE:
                SET_BIT(SYSCTRL_P2strRegs->RCGCGPIO, subPeripheralOffset);
                break;
            case SLEEP_MODE:
            /*TODO: Complete Init*/
                break;
            case DEEPSLEEP_MODE:
            /*TODO: Complete Init*/
                break;    
            default:
                break;
        }
        
        break;
    
    case DMA:
        /*TODO: Complete Init*/;
        break;
    
    case HIBERNATION:
        /*TODO: Complete Init*/;
        break;
    
    case UART:
        /*TODO: Complete Init*/;
        break;

    case SPI:
        /*TODO: Complete Init*/;
        break;
    
    case I2C:
        /*TODO: Complete Init*/;
        break;
    
    case USB:
        /*TODO: Complete Init*/;
        break;
    
    case CAN:
        /*TODO: Complete Init*/;
        break;
        
    case ADC:
        /*TODO: Complete Init*/;
        break;
    
    case ANALOG_COMPARATOR:
        /*TODO: Complete Init*/;
        break;
    
    case PWM:
        /*TODO: Complete Init*/
        break;
    
    case QUADRATURE:
        /*TODO: Complete Init*/
        break;

    case EEPROM:
        /*TODO: Complete Init*/
        break;
                      
    case TIMER_32_64:
        switch(mode)
        {
            case RUN_MODE:
                SET_BIT(SYSCTRL_P2strRegs->RCGCWTIMER, subPeripheralOffset);
                /*TODO: Complete Init*/
                break;
            case SLEEP_MODE:
            /*TODO: Complete Init*/
                break;
            case DEEPSLEEP_MODE:
            /*TODO: Complete Init*/
                break;    
            default:
                break;
        }
        
        /*TODO: Complete Init*/
        break;
    
    default:
        /*Error*/
        break;
    }
}

extern void Rcc_GpioAllUseAHB(void)
{
    SYSCTRL_P2strRegs->GPIOHBCTL= (uint32)0x0000003f;
}
extern void Rcc_GpioUseAHB(uint8 PortId)
{
    if(PortId<6)
    {
        SET_BIT(SYSCTRL_P2strRegs->GPIOHBCTL, PortId);
    }
    else
    {
        /*Error*/
    }
}
