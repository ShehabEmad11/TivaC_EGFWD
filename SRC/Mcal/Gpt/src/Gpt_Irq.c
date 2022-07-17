#include "Gpt.h"
#include "Std_Types.h"
#include "Mcu_Hw.h"
#include "Gpt_Types.h"

volatile uint32 TIMER0_TICK=0;
volatile uint32 TIMER1_TICK=0;
volatile uint32 WTIMER0_TICK=0;


void TIMER0A_Handler(void)
{
    TIMER0_TICK++;

    Gpt_Notification_TIMER0A();

    GPTMRegs_t * channelPtrRegBase = GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs + TIMER_16_32_TIMER0;
    /*Clear TIMERA Timeout Pending Interrupts*/;
    channelPtrRegBase->GPTMICR.fieldAccess.TATOCINT=1;
} 



void WTIMER0A_Handler(void)
{
    GPTMRegs_t * channelPtrRegBase = GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs + TIMER_32_64_TIMER0;
    
    WTIMER0_TICK++;

    Gpt_Notification_WTIMER0A();

    /*Clear TIMERA Timeout Pending Interrupts*/;
    channelPtrRegBase->GPTMICR.fieldAccess.TATOCINT=1;
} 