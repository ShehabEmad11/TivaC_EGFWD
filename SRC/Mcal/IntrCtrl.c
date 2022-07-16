#include "Std_Types.h"
#include "IntrCtrl.h"
#include "IntrCtrl_Types.h"
#include "IntrCtrl_Cfg.h"
#include "Mcu_Hw.h"



extern ExceptionConfigstr_t Exceptions_astrConfig[];

void IntrCtrl_voidInit(void)
{
    uint8 exceptionIter;
    uint8 exceptionNumberInsidePrioReg;
    uint8 currentPriority;
    uint8 bitShift;
    uint8 intRegNumber;

    /*BASED on user configurations::*/
    /*Configure Interrupt Priority Combination Bits*/
    APINT->regAccess = APINT_VECTKEY | PRIORITY_CONFIGURATION; 

    /*Todo: remove*/
    Exceptions_astrConfig[INTERRUPT_16_32Timer_0A].isConfigurable=TRUE;
    Exceptions_astrConfig[INTERRUPT_16_32Timer_0A].isEnabled=TRUE;
    Exceptions_astrConfig[INTERRUPT_16_32Timer_0A].groupPriority=1;
    Exceptions_astrConfig[INTERRUPT_16_32Timer_0A].subGroupPriority=1;

    Exceptions_astrConfig[INTERRUPT_16_32Timer_1A].isConfigurable=TRUE;
    Exceptions_astrConfig[INTERRUPT_16_32Timer_1A].isEnabled=TRUE;
    Exceptions_astrConfig[INTERRUPT_16_32Timer_1A].groupPriority=1;
    Exceptions_astrConfig[INTERRUPT_16_32Timer_1A].subGroupPriority=1;

    Exceptions_astrConfig[INTERRUPT_32_64_Timer_0A].isConfigurable=TRUE;
    Exceptions_astrConfig[INTERRUPT_32_64_Timer_0A].isEnabled=TRUE;
    Exceptions_astrConfig[INTERRUPT_32_64_Timer_0A].groupPriority=1;
    Exceptions_astrConfig[INTERRUPT_32_64_Timer_0A].subGroupPriority=1;
    for(exceptionIter=16; exceptionIter<NUMBER_EXCEPTIONS; exceptionIter++)
    {
        if(Exceptions_astrConfig[exceptionIter].isConfigurable==TRUE)
        {
            if(Exceptions_astrConfig[exceptionIter].isEnabled==TRUE)
            {
                intRegNumber =  (exceptionIter-16) / 4;
                exceptionNumberInsidePrioReg = (exceptionIter-16) % 4 ;
                bitShift =  (exceptionNumberInsidePrioReg * 8) + 5 ;
                currentPriority  = (uint8)(Exceptions_astrConfig[exceptionIter].groupPriority << (3 - GROUP_PRIORITY_NUMBER_BITS))
                                |  (uint8)(Exceptions_astrConfig[exceptionIter].subGroupPriority) ; 

                /*Configure Interrupt Priority */
                PRIOx[intRegNumber].regAccess |= (uint32)(currentPriority << bitShift);

                /*Enable Interrupt Logic*/
                if(exceptionIter >=16)
                {
                    intRegNumber = (exceptionIter-16) / 32;
                    bitShift=(exceptionIter-16) % 32;
                    ENx[intRegNumber].regAccess |= (uint32)(1<<bitShift);
                }
            }
            else
            {
                /*Disable Interrupt Logic*/                
                if(exceptionIter >=16)
                {
                    intRegNumber = (exceptionIter-16) / 32;
                    bitShift=(exceptionIter-16) % 32;
                    DISx[intRegNumber].regAccess |= (uint32)(1<<bitShift);
                }
            }
        }
    }
}
