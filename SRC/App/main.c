#include "Std_Types.h"
#include "IntrCtrl.h"
#include "Dio.h"
#include "Port.h"

extern Port_ConfigType Ports_astrConfig[];
int main(void)
{
    IntrCtrl_voidInit();
    //Dio_WriteChannel(PIN_A1,STD_HIGH);
    Port_Init(&Ports_astrConfig);
    while(1);

    return 1;
}	