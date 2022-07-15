#include "Std_Types.h"
#include "IntrCtrl.h"
#include "Dio.h"
#include "Port.h"
#include "Rcc.h"

#if 0
void TIM_CallBack(void)
{
    #define ON_PERIOD    (1u)
    #define OFF_PERIOD   (0u)
    static uint32 timePassed=0;

    static uint8 currentPeriod=OFF_PERIOD;

    timePassed+=TIMER_TICK;

    switch (currentPeriod)
    {
        case ON_PERIOD:
            if(timePassed>=ON_TIME)
            {
                Dio_FlipChannel(PIN_A0);
                timePassed=0;
                currentPeriod=OFF_PERIOD;
            }
            else
            {
                /*do Nothing wait for time to pass*/
            }
            break;
        
        case OFF_PERIOD:
            if(timePassed>=OFF_TIME)
            {
                Dio_FlipChannel(PIN_A0);
                timePassed=0;
                currentPeriod=ON_PERIOD;
            }
            else
            {
                /*do Nothing wait for time to pass*/
            }
            break;
        default:
        break;
    }
    if(timePassed==ON_PERIOD)
    Dio_FlipChannel(PIN_A0);
}
#endif



extern const Port_ConfigType Ports_astrConfig[];
int main(void)
{
    /*Enable System Clock*/
    Rcc_InitSysClock();
    /*Enable GPIOA Clock*/
    Rcc_voidEnablePeripheral(PERIPH_GPIO_RUN_PA);
    /*Enable TIMER_16_32_TIMER0 's Clock*/
    Rcc_voidEnablePeripheral(PERIPH_TIMER_16_32_RUN_TIMER0);
    /*Enable TIMER_32_64_TIMER0 's Clock*/
    Rcc_voidEnablePeripheral(PERIPH_TIMER_32_64_RUN_TIMER0);

    /*Set AHB the bus for all GPIOs*/
    Rcc_GpioAllUseAHB();
    IntrCtrl_voidInit();
    Port_Init(&Ports_astrConfig[0]);
 
    while(1);

    return 1;
}	
