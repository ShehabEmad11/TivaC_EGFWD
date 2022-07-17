#include "Std_Types.h"
#include "IntrCtrl.h"
#include "Dio.h"
#include "Port.h"
#include "Rcc.h"
#include "Gpt.h"




//#define DEBUG


#ifdef DEBUG
#include "Mcu_Hw.h"
extern volatile uint32 TIMER0_TICK;
extern volatile uint32 TIMER1_TICK;
#endif
extern volatile uint32 WTIMER0_TICK;


void App_WTIM0_CallBack(void)
{
    #define ON_STATE    (1u)
    #define OFF_STATE   (0u)
    #define ON_TIME      2
    #define OFF_TIME     1

    static uint32 timePassed=0;
    static uint8 currentPeriod=ON_STATE;

    timePassed+=WTIMER0_TICK;

    switch (currentPeriod)
    {
        case ON_STATE:
            if(timePassed>=ON_TIME)
            {
                Dio_FlipChannel(PIN_A0);
                timePassed=0;
                currentPeriod=OFF_STATE;
            }
            else
            {
                /*do Nothing wait for time to pass*/
            }
            break;
        
        case OFF_STATE:
            if(timePassed>=OFF_TIME)
            {
                Dio_FlipChannel(PIN_A0);
                timePassed=0;
                currentPeriod=ON_STATE;
            }
            else
            {
                /*do Nothing wait for time to pass*/
            }
            break;
        default:
        break;
    }
    if(timePassed==ON_TIME)
    Dio_FlipChannel(PIN_A0);
}

#ifdef DEBUG
volatile uint32 tempRegVal,tempRegVal2;
#endif

extern const Port_ConfigType Ports_astrConfig[];
extern const Gpt_ConfigType GptConfig;



int main(void)
{
#ifdef DEBUG
    GPTMRegs_t *channelPtrRegBase=NULL_PTR;
#endif

    uint32 tempVal=0;

    uint32 i;
    /*Enable System Clock*/
    Rcc_InitSysClock();
    /*Enable GPIOA Clock*/
    Rcc_voidEnablePeripheral(PERIPH_GPIO_RUN_PA);

    #ifdef DEBUG
    /*Enable TIMER_16_32_TIMER0 's Clock*/
    Rcc_voidEnablePeripheral(PERIPH_TIMER_16_32_RUN_TIMER0);
    /*Enable TIMER_16_32_TIMER1 's Clock*/
    Rcc_voidEnablePeripheral(PERIPH_TIMER_16_32_RUN_TIMER1);
    #endif
    /*Enable TIMER_32_64_TIMER0 's Clock*/
    Rcc_voidEnablePeripheral(PERIPH_TIMER_32_64_RUN_TIMER0);

    /*Set AHB the bus for all GPIOs*/
    Rcc_GpioAllUseAHB();
    IntrCtrl_voidInit();
    
    Port_Init(&Ports_astrConfig[0]);
    
    Gpt_Init(&GptConfig);

#ifdef DEBUG
    for(i=0;i<50000;i++)
    {
        uint8 x;
        x++;
    }
    //Gpt_StartTimer(TIMER_16_32_TIMER0,5000ul);
#endif

    Gpt_StartTimer(TIMER_32_64_TIMER0,16000000ul);
 
    while(1)
    {
        #ifdef DEBUG
            i++;
            channelPtrRegBase = GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs+6;

            channelPtrRegBase->GPTMCTL.regAccess=tempVal;
            tempVal ^=1;

            tempRegVal=(GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs + 6)->GPTMTAR;
            tempRegVal2=(GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs + 6)->GPTMTAILR;
        #endif
    }

    return 1;
}	
