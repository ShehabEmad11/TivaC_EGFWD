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
#include "Gpt_Private.h"
#include "Macros.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
const  Gpt_ConfigType*  P2GptConfig;
static Gpt_ModeType Gpt_Driver_State=uninitialized; 
static GptInternal_ChannelInfo          ChannelsArrInfo[NUMBER_GPT_CHANNELS];
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
    /*Create channelConfigIdxator (it will iterate over CONFIGURED channels only not all channels)*/
    uint16 channelConfigIdx;

    Gpt_ChannelType              channelID;
    GptChannelMode               channelMode;
    GptInternal_FreqType         channelFreqHz ;
    Gpt_ValueType                channelTickValMax;   
    GptPtrNotificationCbkType    channelNotificationCbk;

    GptInternal_CountDirectionType  channelCountDirection;
    GptInternal_BitSizeType         channelBitWidth;
    GptInternal_PrescalerType       channelPrescaler;

    GptInternal_StateType           channelState;
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
        /*Copy Configuration to file scope static variable*/
        P2GptConfig=ConfigPtr;
        
        for(channelConfigIdx=0; channelConfigIdx< ConfigPtr->numberChannels; channelConfigIdx++)
        {
            channelID=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelID;
            channelMode=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelMode;
            /*TODO: Configured but not yet used in driver*/
            channelFreqHz=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelFreqHz;
            /*TODO: Configured but not yet used in driver*/
            channelTickValMax=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelTickValMax;

            channelCountDirection=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelCountDirection;
            
            /*TODO: Configured but not yet used in driver*/
            channelBitWidth=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelBitWidth;
            /*TODO: Configured but not yet used in driver*/
            channelPrescaler=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelPrescaler;
            
            
            /*ChannelsArrStates is static variable with STATE_NOT_INITIALIZED by default*/
            channelState=ChannelsArrInfo[channelID].channelState ;

            if(channelState != STATE_NOT_INITIALIZED)
            {
                /*Error Channel Already Initialized*/
                return;
            }

            ChannelsArrInfo[channelID].channelCbk=ConfigPtr->p2ChannelsCfg[channelConfigIdx].channelNotificationCbk;

            if(channelBitWidth!=BITWIDH_16 && channelBitWidth!=BITWIDH_24
                && channelBitWidth!=BITWIDH_32 && channelBitWidth != BITWIDH_64)
            {
                /*Error Wrong Channel Width*/
                return;
            }

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

            /*Adjust Prescaler*/
            #if CHANNEL_ACCESS_MODE == INDIVIDUAL_ACCESS
                if(channelCountDirection==COUNT_DOWN_DIRECTION)
                {
                    channelPtrRegBase->GPTMTAPR = channelPrescaler;   
                }
                else if(channelCountDirection==COUNT_UP_DIRECTION)
                {
                    /*Todo Handle Prescaler in upCounting Direction*/   
                }
                else
                {
                    /*Error*/
                }
            #else
                #warning "PreScaler has no effect in CONCATENATED MODE"
            #endif
            

            /*Disable All GPT Interrupts*/
            channelPtrRegBase->GPTMIMR.regAccess=0x00;

            /*Set Channel State as initialized*/
            ChannelsArrInfo[channelID].channelState=STATE_INITIALIZED;
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

    /*channelConfigIdx will be used to extract info from configurations*/
    uint16 channelConfigIdx=0;
    uint16 configIter;

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
    if(ChannelsArrInfo[Channel].channelState == STATE_NOT_INITIALIZED)
    {
        EXIT_CRITICAL_SECTION();
        /*Error Channel Not Initialized Yet*/
        return;
    }
    else if(ChannelsArrInfo[Channel].channelState == STATE_RUNNING)
    {
        EXIT_CRITICAL_SECTION();
        /*Error Re-entrant*/
        return;
    }
    EXIT_CRITICAL_SECTION();


    if(Channel>NUMBER_GPT_CHANNELS)
    {
        /*Error Wrong Channel Number*/
        return;
    }

    for(configIter=0;configIter< P2GptConfig->numberChannels; configIter++)
    {
        /*Check if passed channel is configured*/
        if(Channel == P2GptConfig->p2ChannelsCfg[configIter].channelID)
        {
            channelConfigIdx=configIter;
            break;
        }
    }
    if(channelConfigIdx != configIter)
    {
        /*If Channel Not Configured*/
        return;
    }

    if(Value==0 || Value > P2GptConfig->p2ChannelsCfg[channelConfigIdx].channelTickValMax)
    {
        /*Error Wrong Value Passed*/
        return;
    }

    switch(P2GptConfig->p2ChannelsCfg[channelConfigIdx].channelBitWidth)
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
        /*Reset Counting Register*/
        channelPtrRegBase->GPTMTAILR = (Value & P2GptConfig->p2ChannelsCfg[configIter].channelTickValMax );
    }
    #elif CHANNEL_ACCESS_MODE == CONCATENATED_ACCESS
    {
         /*Todo:Handle Concatenated Access*/
        if(Channel>=TIMER_16_32_TIMER0 && Channel<TIMER_32_64_TIMER0)
        {
            channelPtrRegBase->GPTMTAILR = (Value & P2GptConfig->p2ChannelsCfg[configIter].channelTickValMax );
        }
        else if(Channel>=TIMER_32_64_TIMER0 && Channel<=TIMER_32_64_TIMER5)
        {
            /*TODO HANDLE Load register with 64 bit values divided in CHANNELA & CHANNELB*/
        }
        else
        {
            /*Error*/
        }
    }
    #else
        #error Wrong Register Access Mode Configurations
    #endif  


    /*Enable Channel Notification*/
    ChannelsArrInfo[Channel].channelNotificationStatus=STD_ON;

    /*ENABLE TimerA Timeout iNTERRUPT from mask register */
    channelPtrRegBase->GPTMIMR.fieldAccess.TATOIM=1;

    /*Enable Timer*/
    channelPtrRegBase->GPTMCTL.fieldAccess.TAEN=1;

    /*Flag Channel State as running*/
    ChannelsArrInfo[Channel].channelState = STATE_RUNNING;
}

/******************************************************************************
* \Syntax          : void Gpt_StopTimer(Gpt_ChannelType Channel)        
* \Description     : Service to Stop Timer of specific channel                               
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant (not for same channel ID)                                          
* \Parameters (in) : Channel <channel ID>                
* \Parameters (out): None                                                      
* \Return value:   : void  
*                                   
*******************************************************************************/
extern void Gpt_StopTimer( Gpt_ChannelType Channel )
{
    uint32 mask;
    GPTMRegs_t *channelPtrRegBase=NULL_PTR;

    /*channelConfigIdx will be used to extract info from configurations*/
    uint16 channelConfigIdx=0;
    uint16 configIter;

    ENTER_CRITICAL_SECTION();
    if(ChannelsArrInfo[Channel].channelState == STATE_NOT_INITIALIZED)
    {
        EXIT_CRITICAL_SECTION();
        /*Error Channel Not Initialized Yet*/
        return;
    }
    else if(ChannelsArrInfo[Channel].channelState != STATE_RUNNING)
    {
        EXIT_CRITICAL_SECTION();
        /*Channel Not running   (this is not an error accoding to AUTOSAR)*/
        return;
    }
    EXIT_CRITICAL_SECTION();


    if(Channel>NUMBER_GPT_CHANNELS)
    {
        /*Error Wrong Channel Number*/
        return;
    }

    for(configIter=0;configIter< P2GptConfig->numberChannels; configIter++)
    {
        /*Check if passed channel is configured*/
        if(Channel == P2GptConfig->p2ChannelsCfg[configIter].channelID)
        {
            channelConfigIdx=configIter;
            break;
        }
    }
    if(channelConfigIdx != configIter)
    {
        /*If Channel Not Configured*/
        return;
    }

    switch(P2GptConfig->p2ChannelsCfg[channelConfigIdx].channelBitWidth)
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

    /*Disable Timer */
    channelPtrRegBase->GPTMCTL.fieldAccess.TAEN=0;

    /*Clear TIMERA Timeout Pending Interrupts*/;
    channelPtrRegBase->GPTMICR.fieldAccess.TATOCINT=1;

    /*Flag Channel State as running*/
    ChannelsArrInfo[Channel].channelState = STATE_STOPPED;
}

extern void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
    /*Enable Channel Notification*/
    ChannelsArrInfo[Channel].channelNotificationStatus=STD_ON;
}
extern void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
    /*Disable Channel Notification*/
    ChannelsArrInfo[Channel].channelNotificationStatus=STD_OFF;
}

extern Std_ReturnType Gpt_GetPredefTimerValue( Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr )
{

}


/*===========================START OF TIMER CB NOTIFICATIONS==========================================*/
extern void Gpt_Notification_TIMER0A(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER0].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER0].channelCbk != 0) 
    {
        if(ChannelsArrInfo[TIMER_16_32_TIMER0].channelNotificationStatus==STD_ON)
        {
            ChannelsArrInfo[TIMER_16_32_TIMER0].channelCbk();
        }
    }

    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER0].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER0].channelState = STATE_EXPIRED;
    }
}

extern void Gpt_Notification_TIMER0B(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER0].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER0].channelCbk != 0) 
    {
        if(ChannelsArrInfo[TIMER_16_32_TIMER0].channelNotificationStatus==STD_ON)
        {
            ChannelsArrInfo[TIMER_16_32_TIMER0].channelCbk();
        }
    }
    
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER0].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER0].channelState = STATE_EXPIRED;
    }
}
#if 0
extern void Gpt_Notification_TIMER1A(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER1].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER1].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER1].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER1].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER1].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER1B(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER1].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER1].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER1].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER1].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER1].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER2A(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER2].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER2].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER2].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER2].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER2].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER2B(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER2].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER2].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER2].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER2].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER2].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER3A(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER3].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER3].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER3].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER3].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER3].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER3B(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER3].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER3].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER3].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER3].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER3].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER4A(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER4].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER4].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER4].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER4].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER4].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER4B(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER4].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER4].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER4].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER4].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER4].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_TIMER5A(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER5].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER5].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER5].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER5].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER5].channelState = STATE_EXPIRED;
    }
}

extern void Gpt_Notification_TIMER5B(void)
{

    if(ChannelsArrInfo[TIMER_16_32_TIMER5].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_16_32_TIMER5].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_16_32_TIMER5].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_16_32_TIMER5].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_16_32_TIMER5].channelState = STATE_EXPIRED;
    }
}
#endif



extern void Gpt_Notification_WTIMER0A(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER0].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER0].channelCbk != 0) 
    {
        if(ChannelsArrInfo[TIMER_32_64_TIMER0].channelNotificationStatus==STD_ON)
        {
            ChannelsArrInfo[TIMER_32_64_TIMER0].channelCbk();
        }
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER0].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER0].channelState = STATE_EXPIRED;
    }
}

extern void Gpt_Notification_WTIMER0B(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER0].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER0].channelCbk != 0) 
    {
        if(ChannelsArrInfo[TIMER_32_64_TIMER0].channelNotificationStatus==STD_ON)
        {
            ChannelsArrInfo[TIMER_32_64_TIMER0].channelCbk();
        }
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER0].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER0].channelState = STATE_EXPIRED;
    }
}

#if 0
extern void Gpt_Notification_WTIMER1A(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER1].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER1].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER1].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER1].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER1].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER1B(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER1].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER1].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER1].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER1].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER1].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER2A(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER2].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER2].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER2].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER2].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER2].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER2B(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER2].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER2].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER2].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER2].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER2].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER3A(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER3].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER3].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER3].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER3].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER3].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER3B(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER3].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER3].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER3].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER3].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER3].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER4A(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER4].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER4].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER4].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER4].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER4].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER4B(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER4].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER4].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER4].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER4].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER4].channelState = STATE_EXPIRED;
    }
}
extern void Gpt_Notification_WTIMER5A(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER5].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER5].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER5].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER5].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER5].channelState = STATE_EXPIRED;
    }
}

extern void Gpt_Notification_WTIMER5B(void)
{

    if(ChannelsArrInfo[TIMER_32_64_TIMER5].channelCbk != NULL_PTR 
    && ChannelsArrInfo[TIMER_32_64_TIMER5].channelCbk != 0) 
    {
        ChannelsArrInfo[TIMER_32_64_TIMER5].channelCbk();
    }
    if(P2GptConfig->p2ChannelsCfg[TIMER_32_64_TIMER5].channelMode==GPT_CH_MODE_ONESHOT)
    {
        /*Flag Channel State as EXPIRED in case of one SHot mode*/
        ChannelsArrInfo[TIMER_32_64_TIMER5].channelState = STATE_EXPIRED;
    }
}
#endif
/*============================END of timer CB Notifications==================================*/

/*============================START ISR Definations=========================================*/
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
/*============================END ISR Definations=======================================*/



#if 0
extern void Gpt_SetMode( Gpt_ModeType Mode )
{
    
}
#endif
/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/


