#include "Std_Types.h"
#include "IntrCtrl.h"
#include "IntrCtrl_Types.h"
#include "IntrCtrl_Cfg.h"
#include "IntrCtrl_Private.h"



extern const ExceptionConfigstr_t Exceptions_astrConfig[];

void IntrCtrl_voidInit(void)
{
    uint8 exceptionIter;
    uint8 InterruptNumberInsidePrioReg;
    uint8 currentPriority;
    uint8 bitShift;
    uint8 exceptionNumber;
    uint8 exceptiontNumberInsidePrioReg;
    uint8 intRegNumber;
    uint8 interruptNumber;

    /*BASED on user configurations::*/
    /*Configure Interrupt Priority Combination Bits*/
    APINT->regAccess = APINT_VECTKEY | PRIORITY_CONFIGURATION; 

    for(exceptionIter=0; exceptionIter<NUMBER_EXCEPTIONS_CONFIGURED; exceptionIter++)
    {
        exceptionNumber = Exceptions_astrConfig[exceptionIter].exceptionID;
        
        if(Exceptions_astrConfig[exceptionIter].isConfigurable==TRUE)
        {
            if(Exceptions_astrConfig[exceptionIter].isEnabled==TRUE)
            {
                if(exceptionNumber<16)
                {
                    /*TODO control exception Priorities*/
                }
                else
                {
                    interruptNumber = (exceptionNumber-16);
                    intRegNumber =  (interruptNumber) / 4;
                    InterruptNumberInsidePrioReg = (interruptNumber) % 4 ;
                    bitShift =  (InterruptNumberInsidePrioReg * 8) + 5 ;
                    currentPriority  = (uint8)(Exceptions_astrConfig[exceptionIter].groupPriority << (3 - GROUP_PRIORITY_NUMBER_BITS))
                                    |  (uint8)(Exceptions_astrConfig[exceptionIter].subGroupPriority) ; 

                    /*Configure Interrupt Priority */
                    PRIOx[intRegNumber].regAccess |= (uint32)(currentPriority << bitShift);

                    /*Enable Interrupt Logic*/
                    intRegNumber = interruptNumber / 32;
                    bitShift=(interruptNumber) % 32;
                    ENx[intRegNumber].regAccess |= (uint32)(1<<bitShift);
                }
            }
            else
            {
                /*Disable Interrupt Logic*/                
                interruptNumber = (exceptionNumber-16);
                intRegNumber =  (interruptNumber) / 32;
                bitShift=(interruptNumber) % 32;
                DISx[intRegNumber].regAccess |= (uint32)(1<<bitShift);  
            }
        }
    }
}
