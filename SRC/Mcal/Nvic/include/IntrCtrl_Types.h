#ifndef INTRCTRL_TYPES_H
#define INTRCTRL_TYPES_H


typedef enum 
{   
    /*InterruptName*/                       /*VectorTableNumber*/
    INTERRUPT_INIT_SP							=    0   ,
    INTERRUPT_Reset 							=    1   ,
    INTERRUPT_NMI                     			=    2   ,
    INTERRUPT_Hard_Fault						=    3   ,
    INTERRUPT_Memory_Management					=    4   ,
    INTERRUPT_Bus_Fault							=    5   ,
    INTERRUPT_Usage_Fault 						=    6   ,

    INTERRUPT_SVCall 							=   11   ,
    INTERRUPT_Debug_Monitor 					=   12   ,

    INTERRUPT_PendSV 							=   14   ,
    INTERRUPT_SysTick 							=   15   ,
    INTERRUPT_GPIO_Port_A                       =   16   ,
    INTERRUPT_GPIO_Port_B                       =   17   ,
    INTERRUPT_GPIO_Port_C                       =   18   ,
    INTERRUPT_GPIO_Port_D                       =   19   ,
    INTERRUPT_GPIO_Port_E                       =   20   ,
    INTERRUPT_UART0                             =   21   ,
    INTERRUPT_UART1                             =   22   ,
    INTERRUPT_SSI0                              =   23   ,
    INTERRUPT_I2C0                              =   24   ,
    INTERRUPT_PWM0_Fault                        =   25   ,
    INTERRUPT_PWM0_Generator_0                  =   26   ,
    INTERRUPT_PWM0_Generator_1                  =   27   ,
    INTERRUPT_PWM0_Generator_2                  =   28   ,
    INTERRUPT_QEI0                              =   29   ,
    INTERRUPT_ADC0_Sequence_0                   =   30   ,
    INTERRUPT_ADC0_Sequence_1                   =   31   ,
    INTERRUPT_ADC0_Sequence_2                   =   32   ,
    INTERRUPT_ADC0_Sequence_3                   =   33   ,
    INTERRUPT_Watchdog_Timers_0_1	            =   34   ,
    INTERRUPT_16_32Timer_0A                   		=   35   ,
    INTERRUPT_16_32Timer_0B                   		=   36   ,
    INTERRUPT_16_32Timer_1A                   		=   37   ,
    INTERRUPT_16_32Timer_1B                   		=   38   ,
    INTERRUPT_16_32Timer_2A                   		=   39   ,
    INTERRUPT_16_32Timer_2B                   		=   40   ,
    INTERRUPT_Analog_Comparator_0               =   41   ,
    INTERRUPT_Analog_Comparator_1               =   42   ,

    INTERRUPT_System_Control                    =   44   ,
    INTERRUPT_Flash_Memory_Control_and_EEPROM   =   45   ,
    INTERRUPT_GPIO_Port_F                       =   46   ,

    INTERRUPT_UART2                             =   49   ,
    INTERRUPT_SSI1                              =   50   ,
    INTERRUPT_Timer_3A          			    =   51   ,
    INTERRUPT_Timer_3B          			    =   52   ,
    INTERRUPT_I2C1                              =   53   ,
    INTERRUPT_QEI1                              =   54   ,
    INTERRUPT_CAN0                              =   55   ,
    INTERRUPT_CAN1                              =   56   ,

    INTERRUPT_Hibernation_Module                =   59   ,
    INTERRUPT_USB                               =   60   ,
    INTERRUPT_PWM_Generator_3                   =   61   ,
    INTERRUPT_DMA_Software                      =   62   ,
    INTERRUPT_DMA_Error                         =   63   ,
    INTERRUPT_ADC1_Sequence_0                   =   64   ,
    INTERRUPT_ADC1_Sequence_1                   =   65   ,
    INTERRUPT_ADC1_Sequence_2                   =   66   ,
    INTERRUPT_ADC1_Sequence_3                   =   67   ,

    INTERRUPT_SSI2                              =   73   ,
    INTERRUPT_SSI3                              =   74   ,
    INTERRUPT_UART3                             =   75   ,
    INTERRUPT_UART4                             =   76   ,
    INTERRUPT_UART5                             =   77   ,
    INTERRUPT_UART6                             =   78   ,
    INTERRUPT_UART7                             =   79   ,

    INTERRUPT_I2C2                              =   84   ,
    INTERRUPT_I2C3                              =   85   ,
    INTERRUPT_Timer_4A                   		=   86   ,
    INTERRUPT_Timer_4B                   		=   87   ,

    INTERRUPT_Timer_5A   			            =   108  ,
    INTERRUPT_Timer_5B   			            =   109  ,
    INTERRUPT_32_64_Timer_0A   			            =   110  ,
    INTERRUPT_32_64_Timer_0B   			            =   111  ,
    INTERRUPT_32_64_Timer_1A   			            =   112  ,
    INTERRUPT_32_64_Timer_1B                          =   113  ,
    INTERRUPT_32_64_Timer_2A                          =   114  ,
    INTERRUPT_32_64_Timer_2B                          =   115  ,
    INTERRUPT_32_64_Timer_3A                          =   116  ,
    INTERRUPT_32_64_Timer_3B                          =   117  ,
    INTERRUPT_32_64_Timer_4A                          =   118  ,
    INTERRUPT_32_64_Timer_4B                          =   119  ,
    INTERRUPT_32_64_Timer_5A                          =   120  ,
    INTERRUPT_32_64_Timer_5B                          =   121  ,
    INTERRUPT_System_Exception                  =   122  ,

    INTERRUPT_PWM1_Generator_0                  =   150  ,
    INTERRUPT_PWM1_Generator_1                  =   151  ,
    INTERRUPT_PWM1_Generator_2                  =   152  ,
    INTERRUPT_PWM1_Generator_3                  =   153  ,
    INTERRUPT_PWM1_Fault                        =   154
}InterruptEnu_t;



typedef struct 
{
    uint8 isConfigurable:1;
    uint8 isEnabled:1;
    uint8 groupPriority:3;
    uint8 subGroupPriority:3;

    uint8 exceptionID;
}ExceptionConfigstr_t;

#endif /* INTRCTRL_TYPES_H */
