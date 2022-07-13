#ifndef RCC_CFG_H
#define RCC_CFG_H


#define PERCISION_INTERNAL_OSCILATOR            (0u)
#define PERCISION_INTERNAL_OSCILATOR_DIV4       (1u)
#define MAIN_OSCILATOR                          (2u)
#define LFIOSC                                  (3u)  /*Low Frequency Internal Oscilator*/
#define HMOSC                                   (4u)  /*Hibernation Module Oscillator*/
#define PLL_OUT                                 (5u)

#define SYSTEM_CLOCK             PERCISION_INTERNAL_OSCILATOR

#define PLL_CLK_SOURCE           PERCISION_INTERNAL_OSCILATOR   /*Only Applicable if SYSTEM_CLOCK == PLL_OUT*/

#if  (PLL_CLK_SOURCE !=  PERCISION_INTERNAL_OSCILATOR  \
    && PLL_CLK_SOURCE !=  PERCISION_INTERNAL_OSCILATOR_DIV4)
#error Wrong PLL_SOURCE CONFIG
#endif


#define SYSTEM_CLOCK_DIVIDER                STD_OFF

#if SYSTEM_CLOCK_DIVIDER == STD_ON
    #define SYSTEM_CLOCK_DIVIDER_VALUE          (0x00u)
#endif


#endif /* RCC_CFG_H */
