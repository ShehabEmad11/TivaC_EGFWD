#ifndef RCC_H
#define RCC_H

#include "Std_Types.h"
#include "Rcc_Types.h"


extern void Rcc_InitSysClock(void);
extern void Rcc_voidEnablePeripheral(Rcc_PeripheralType Peripheral);
extern void Rcc_GpioAllUseAHB(void);
extern void Rcc_GpioUseAHB(uint8 PortId);
#endif /* RCC_H */
