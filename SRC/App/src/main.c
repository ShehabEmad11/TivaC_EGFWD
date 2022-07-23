#include "Std_Types.h"
#include "IntrCtrl.h"
#include "Dio.h"
#include "Port.h"
#include "Rcc.h"
#include "Gpt.h"


#define ON_TIME      2
#define OFF_TIME     1

void App_WTIM0_CallBack(void)
{
    #define ON_STATE    (1u)
    #define OFF_STATE   (0u)


    static uint32 timePassed=0;
    static uint8 currentPeriod=ON_STATE;

    timePassed+=1;

    switch (currentPeriod)
    {
        case ON_STATE:
            if(timePassed>=ON_TIME)
            {
                Dio_WriteChannel(PIN_A0,STD_LOW);
                timePassed=0;
                currentPeriod=OFF_STATE;
            }
            else
            {
                Dio_WriteChannel(PIN_A0,STD_HIGH);
                /*do Nothing wait for time to pass*/
            }
            break;
        
        case OFF_STATE:
            if(timePassed>=OFF_TIME)
            {
                Dio_WriteChannel(PIN_A0,STD_HIGH);
                timePassed=0;
                currentPeriod=ON_STATE;
            }
            else
            {
                Dio_WriteChannel(PIN_A0,STD_LOW);
                /*do Nothing wait for time to pass*/
            }
            break;
        default:
        break;
    }
}


extern const Port_ConfigType Ports_astrConfig[];
extern const Gpt_ConfigType GptConfig;
extern const ExceptionConfigstr_t Exceptions_astrConfig[];

int main(void)
{
    uint32 tempVal=0;

    uint32 i;
    /*Enable System Clock*/
    Rcc_InitSysClock();
    /*Enable GPIOA Clock*/
    Rcc_voidEnablePeripheral(PERIPH_GPIO_RUN_PA);

    /*Enable TIMER_32_64_TIMER0 's Clock*/
    Rcc_voidEnablePeripheral(PERIPH_TIMER_32_64_RUN_TIMER0);

    /*Set AHB the bus for all GPIOs*/
    Rcc_GpioAllUseAHB();
    IntrCtrl_voidInit();
    
    Port_Init(&Ports_astrConfig[0]);
    
    Gpt_Init(&GptConfig);

    Gpt_StartTimer(TIMER_32_64_TIMER0,16000000ul);
 
    while(1)
    {

    }

    return 1;
}	
