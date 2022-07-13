#include "Std_Types.h"
#include "IntrCtrl.h"
#include "Dio.h"
#include "Port.h"

extern const Port_ConfigType Ports_astrConfig[];
int main(void)
{
    IntrCtrl_voidInit();
    Port_Init(&Ports_astrConfig);
 
    while(1);

    return 1;
}	
