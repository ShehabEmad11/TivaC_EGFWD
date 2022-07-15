/*Target:

1-Init Function to configure timer and only enable counter for predefined timers (N.A now)
 but not Enable counter for rest of GPTs
 void Gpt_Init( const Gpt_ConfigType* ConfigPtr )

2-Predefined Timer enabled by user 
if enabled return:
100us 32
1us 16
1us 24
1us 32

3-Max array 12 timer 
channel ID
TickFreq
TickValMax
ChannelMode
CallBackFunc




2-Gpt_StartTimer()
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
Callback Gpt_Notification_<channel>


3-Gpt_StopTimer
4-During Running we could enable/Disable notification
5-Expired != Stopped



The GPTM is placed into individual/split mode by writing a value
of 0x4 to the GPTM Configuration (GPTMCFG) register

The selection of one-shot or periodic mode is determined by the value written to the TnMR field of
the GPTM Timer n Mode (GPTMTnMR) register

The timer is configured to count
up or down using the TnCDIR bit in the GPTMTnMR register.


The selection of one-shot or periodic mode is determined by the value written to the TnMR field of
the GPTM Timer n Mode (GPTMTnMR) register (see page 729). The timer is configured to count
up or down using the TnCDIR bit in the GPTMTnMR register.
When software sets the TnEN bit in the GPTM Control (GPTMCTL) register (see page 737), the
timer begins counting up from 0x0 or down from its preloaded value. Alternatively, if the TnWOT bit
is set in the GPTMTnMR register, once the TnEN bit is set, the timer waits for a trigger to begin
counting


In addition to reloading the count value, the GPTM can generate interrupts, CCP outputs and triggers
when it reaches the time-out event. The GPTM sets the TnTORIS bit in the GPTM Raw Interrupt
Status (GPTMRIS) register (see page 748), and holds it until it is cleared by writing the GPTM
Interrupt Clear (GPTMICR) register (see page 754).


If software updates the GPTMTnILR or the GPTMTnPR register while the counter is counting down,
the counter loads the new value on the next clock cycle and continues counting from the new value
if the TnILD bit in the GPTMTnMR register is clear. If the TnILD bit is set, the counter loads the
new value after the next timeout. If software updates the GPTMTnILR or the GPTMTnPR register
while the counter is counting up, the timeout event is changed on the next cycle to the new value.
If software updates the GPTM Timer n Value (GPTMTnV) register while the counter is counting up
or down, the counter loads the new value on the next clock cycle and continues counting from the
new value. If software updates the GPTMTnMATCHR or the GPTMTnPMR registers, the new values
are reflected on the next clock cycle if the TnMRSU bit in the GPTMTnMR register is clear. If the
TnMRSU bit is set, the new value will not take effect until the next timeout.


If the TnSTALL bit in the GPTMCTL register is set and the RTCEN bit is not set in the GPTMCTL
register, the timer freezes counting while the processor is halted by the debugger. The timer resumes
counting when the processor resumes execution. If the RTCEN bit is set, it prevents the TnSTALL
bit from freezing the count when the processor is halted by the debugger.

The prescaler can
only be used when a 16/32-bit timer is configured in 16-bit mode and when a 32/64-bit timer is
configured in 32-bit mode.




One-Shot/Periodic Timer Mode
The GPTM is configured for One-Shot and Periodic modes by the following sequence:
1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
any changes.
2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
a. Write a value of 0x1 for One-Shot mode.
b. Write a value of 0x2 for Periodic mode.
4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
to select whether to capture the value of the free-running timer at time-out, use an external
trigger to start counting, configure an additional trigger or interrupt, and count up or down.
5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
(GPTMIMR).
7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
Register (GPTMICR).
If the TnMIE bit in the GPTMTnMR register is set, the RTCRIS bit in the GPTMRIS register is set,
and the timer continues counting. In One-Shot mode, the timer stops counting after the time-out
event. To re-enable the timer, repeat the sequence. A timer configured in Periodic mode reloads
the timer and continues counting after the time-out event.
*/


/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gpt.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Gpt.h"
#include "Gpt_Types.h"
#include "Mcu_Hw.h"
#include "Macros.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/


extern const Gpt_ConfigType GptChannelConfigs[];

static GptInternal_InfoType Gpt_astrChannelsInfo[NUMBER_GPT_CONFIGURED_CHANNELS];

static Gpt_ModeType Gpt_Driver_State=uninitialized; 
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

extern void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
    Gpt_ChannelType Iter;

    Gpt_ChannelType              channelID;
    GptChannelMode               channelMode;
    GptInternal_FreqType         channelFreq ;
    Gpt_ValueType                channelTickValMax;   
    GptPtrNotificationCbkType    channelNotificationCbk;

    GptInternal_CountDirectionType  channelCountDirection;
    GptInternal_BitSizeType         channelBitWidth;
    GptInternal_PrescalerType       channelPrescaler;

    GPTMRegs_t *channelPtrRegBase=NULL_PTR;

    if(Gpt_Driver_State != uninitialized)
    {
        /*Error Driver Already initialized*/
        return;
    }

    if(ConfigPtr==NULL_PTR)
    {
        return;
    }

    /*Todo Enable PreDefined Timers*/
    #if ( (GptPredefTimer100us32bitEnable != FALSE)  \
        ||(GptPredefTimer1usEnablingGrade != GPT_PREDEF_TIMER_1US_DISABLED))
            #error Not Implemented Yet
        /*If PreDefined Timer is enabled:*/
        /*Todo: PreDefined Timer / Normal Timer Init Sequence*/

    #else/*If PreDefined Timer is Disabled:*/  
        for(Iter=0; Iter< ConfigPtr->numberChannels; Iter++)
        {
            if(GptChannelConfigs[Iter].channelsCfg.channelBitWidth==0 
            || GptChannelConfigs[Iter].channelsCfg.channelBitWidth > 64)
            {
                /*Error Wrong Channel Width*/
                return;
            }

            channelID=ConfigPtr->channelsCfg.channelID;
            channelMode=ConfigPtr->channelsCfg.channelMode;
            /*TODO: Configured but not yet used in driver*/
            channelFreq=ConfigPtr->channelsCfg.channelFreq;
            /*TODO: Configured but not yet used in driver*/
            channelTickValMax=ConfigPtr->channelsCfg.channelTickValMax;
            /*TODO: Configured but not yet used in driver*/
            channelNotificationCbk=ConfigPtr->channelsCfg.channelNotificationCbk;

            channelCountDirection=ConfigPtr->channelsCfg.channelCountDirection;
            
            /*TODO: Configured but not yet used in driver*/
            channelBitWidth=ConfigPtr->channelsCfg.channelBitWidth;
            /*TODO: Configured but not yet used in driver*/
            channelPrescaler=ConfigPtr->channelsCfg.channelPrescaler;
            if(channelID<TIMER_32_64_TIMER2)
            {
                channelPtrRegBase = GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs + channelID;
            }
            else if(channelID >= TIMER_32_64_TIMER2)
            {
                channelPtrRegBase = GPTM_TIMER2To5_32_64_P2strRegs + (channelID-TIMER_32_64_TIMER2) ;
            }
            
            /*Disable Timer (Pre-Cautionary) and according to datasheet some registers only written
             when this bit is cleared*/
            channelPtrRegBase->GPTMCTL.fieldAccess.TAEN=0;

            /*Clear TIMERA Timeout Pending Interrupts*/;
            channelPtrRegBase->GPTMICR.fieldAccess.TATOCINT=1;

            /*Set Timer Mode of Operation (Individual vs Concatenated)*/
            #if CHANNEL_ACCESS_MODE == INDIVIDUAL_ACCESS
            channelPtrRegBase->GPTMCFG=0x4;
            #elif CHANNEL_ACCESS_MODE == CONCATENATED_ACCESS
                channelPtrRegBase->GPTMCFG=0x00;
                /*Todo Complete Implementation*/
                #error Not Implemented Yet
            #else
                #error Wrong Register Access Mode Configurations
            #endif

            
            /*Set  Channel Mode*/
            if(channelMode==GPT_CH_MODE_CONTINUOUS)
            {
                channelPtrRegBase->GPTMTAMR.fieldAccess.TAMR=2;
            }
            else
            {
                /*One Shoot Mode*/
                channelPtrRegBase->GPTMTAMR.fieldAccess.TAMR=1;                
            }

            /*Set Counting Direction*/
            if(channelCountDirection==COUNT_DOWN_DIRECTION)
            {
                channelPtrRegBase->GPTMTAMR.fieldAccess.TACDIR=0;
                
                /*Configure that any write attempts to Counter through Interval Load register in countdown
                 while timer is enabled, takes effect next clock cycle (default)*/
                channelPtrRegBase->GPTMTAMR.fieldAccess.TAILD=0;
            }
            else
            {
                channelPtrRegBase->GPTMTAMR.fieldAccess.TACDIR=1;
            }

            #if GPT_STALL_DURING_DEBUG==TRUE
                /*In case of not RTC mode, enable stall of timer counter when debuging*/
                channelPtrRegBase->GPTMCTL.fieldAccess.TASTALL=1;
            #else
                /*In case of not RTC mode, Disable stall of timer counter when debuging*/
                channelPtrRegBase->GPTMCTL.fieldAccess.TASTALL=0;
            #endif

            /*Disable All GPT Interrupts*/
            channelPtrRegBase->GPTMIMR.regAccess=0x00;

            /*Set Channel State as initialized*/
            Gpt_astrChannelsInfo[Iter].channelState=STATE_INITIALIZED;
            
        }
        Gpt_Driver_State=GPT_MODE_NORMAL;
    #endif
}

extern Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{

}

extern Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{

}

/******************************************************************************
* \Syntax          : void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)        
* \Description     : Service to start Timer of specific channel with specific tick values                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant (not for same channel ID)                                          
* \Parameters (in) : Channel <channel ID> ,    Value <TickValues>                     
* \Parameters (out): None                                                      
* \Return value:   : void  
*                                   
*******************************************************************************/

extern void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    uint32 mask;
    GPTMRegs_t *channelPtrRegBase=NULL_PTR;

    #if ( (GptPredefTimer100us32bitEnable != FALSE) )
        /*If PreDefined Timer is enabled:*/    
        if(Channel==GPT_PREDEF_TIMER_100US_32BIT_CHANNEL_ID)
        {
             /*Error using Gpt_StartTimer with PreDefined Timers*/
            return;
        }

    #elif(GptPredefTimer1usEnablingGrade != GPT_PREDEF_TIMER_1US_DISABLED)
        if(Channel==GPT_PREDEF_TIMER_1US_16BIT_CHANNEL_ID
        ||Channel==GPT_PREDEF_TIMER_1US_24BIT_CHANNEL_ID
        ||Channel==GPT_PREDEF_TIMER_1US_32BIT_CHANNEL_ID )
        {
            /*Error using Gpt_StartTimer with PreDefined Timers*/
            return;
        }
    #endif

    ENTER_CRITICAL_SECTION();
    if(Gpt_astrChannelsInfo[Channel].channelState == STATE_NOT_INITIALIZED)
    {
        EXIT_CRITICAL_SECTION();
        /*Error Channel Not Initialized Yet*/
        return;
    }
    else if(Gpt_astrChannelsInfo[Channel].channelState == STATE_RUNNING)
    {
        EXIT_CRITICAL_SECTION();
        /*Error Re-entrant*/
        return;
    }
    EXIT_CRITICAL_SECTION();


    if(Channel>NUMBER_TIMER_CHANNELS)
    {
        /*Error Wrong Channel Config*/
        return;
    }

    if(Value==0 || Value > GptChannelConfigs[Channel].channelsCfg.channelTickValMax)
    {
        /*Error Wrong Value Passed*/
        return;
    }

    switch(GptChannelConfigs[Channel].channelsCfg.channelBitWidth)
        {
        case BITWIDH_16:
            mask=0x0000FFFF;
            break;
        
        case BITWIDH_24:
            mask=0x00FFFFFF;
            break;

        case BITWIDH_32:
            mask=0xFFFFFFFF;
            break;

        case BITWIDH_64:
            mask=0xFFFFFFFF;
            break;

        default:
            mask=0xFFFFFFFF;
            break;
    } 

    if(Channel<TIMER_32_64_TIMER2)
    {
        channelPtrRegBase = GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs + Channel;
    }
    else if(Channel>=TIMER_32_64_TIMER2)
    {
        channelPtrRegBase = GPTM_TIMER2To5_32_64_P2strRegs+(Channel-TIMER_32_64_TIMER2);
    }

    /*Disable Timer (Pre-Cautionary) and according to datasheet some registers only written when this 
    bit is cleared*/
    channelPtrRegBase->GPTMCTL.fieldAccess.TAEN=0;

    /*Clear TIMERA Timeout Pending Interrupts*/;
    channelPtrRegBase->GPTMICR.fieldAccess.TATOCINT=1;
    #if CHANNEL_ACCESS_MODE == INDIVIDUAL_ACCESS  
    {
        /*Set Number of Ticks*/
        channelPtrRegBase->GPTMTAILR=Value & mask;

        if(GptChannelConfigs[Channel].channelsCfg.channelCountDirection==COUNT_UP_DIRECTION)
        {
            /*Todo: Write Prescaler*/
            
            /*Reset Counting Register*/
            channelPtrRegBase->GPTMTAV=0x00000000 & mask;
        }
        else
        {
            /*Todo: Write Prescaler*/
            
            /*Reset Counting Register*/
            channelPtrRegBase->GPTMTAV=0xFFFFFFFF & mask;
        }
    }
    #elif   CHANNEL_ACCESS_MODE == CONCATENATED_ACCESS
    {
         /*Todo:Handle Concatenated Access*/
        #warning Not Yet Implemented
    }   
    #else
        #error Wrong Access Configuration
    #endif



    /*ENABLE TimerA Timeout iNTERRUPT from mask register */
    channelPtrRegBase->GPTMIMR.fieldAccess.TATOIM=1;

    /*Enable Timer*/
    channelPtrRegBase->GPTMCTL.fieldAccess.TAEN=1;

    /*Flag Channel State as running*/
    Gpt_astrChannelsInfo[Channel].channelState = STATE_RUNNING;
}

extern void Gpt_StopTimer( Gpt_ChannelType Channel )
{

}

extern void Gpt_EnableNotification( Gpt_ChannelType Channel )
{

}
extern void Gpt_DisableNotification( Gpt_ChannelType Channel )
{

}

extern Std_ReturnType Gpt_GetPredefTimerValue( Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr )
{

}

#if 0
extern void Gpt_SetMode( Gpt_ModeType Mode )
{
    
}
#endif
/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/


