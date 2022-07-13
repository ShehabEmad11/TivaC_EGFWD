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
#include "Mcu_Hw.h"


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

extern void Rcc_voidEnablePeripheral(Rcc_PeripheralType Peripheral_Id)
{
    switch (Peripheral_Id)
    {
    case PERIPHIRAL_GPIO_PORTA:
        SET_BIT(SYSCTRL_P2strRegs->RCGCGPIO, 0);
        break;
    case PERIPHIRAL_GPIO_PORTB:
        SET_BIT(SYSCTRL_P2strRegs->RCGCGPIO, 1);
        break;
    case PERIPHIRAL_GPIO_PORTC:
        SET_BIT(SYSCTRL_P2strRegs->RCGCGPIO, 2);
        break;
    case PERIPHIRAL_GPIO_PORTD:
        SET_BIT(SYSCTRL_P2strRegs->RCGCGPIO, 3);
        break;
    case PERIPHIRAL_GPIO_PORTE:
        SET_BIT(SYSCTRL_P2strRegs->RCGCGPIO, 4);
        break;
    case PERIPHIRAL_GPIO_PORTF:
        SET_BIT(SYSCTRL_P2strRegs->RCGCGPIO, 5);
        break;


    /*Todo: Complete the rest of peripherals enable*/
    default:
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
