#ifndef MCU_HW_H
#define MCU_HW_H

#include "Std_Types.h"


/* Application Interrupt and Reset Control (APINT)*/
#define CORE_PERIPHERALS_BASE          (0xE000E000ul)
#define OFFSET_APPINT_FROM_COREBASE    (0xD0Cul     )
#define APINT_VECTKEY                  (0xFA050000ul)
#define APINT                          ( (volatile Apint_t*) (CORE_PERIPHERALS_BASE + OFFSET_APPINT_FROM_COREBASE) )

/*Field access has no effect for write with this register*/
typedef struct
{
    uint32   VECTRESET:1;
    uint32   VECTCLRACT:1;
    uint32   SYSRESREQ:1;
    uint32   Reserved0:5;
    uint32   PRIGROUP:3;
    uint32   Reserved1:4;
    uint32   ENDIANESS:1;
    uint32   VECTKEY:16 ; 
}Apint_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    Apint_fieldAccess_t fieldAccess;
}Apint_t;


/*===========================*/

/*Priority Registers*/
#define OFFSET_PRI0_FROM_COREBASE      (0x400ul)
#define PRIOx   ( (volatile Priox_t*) (CORE_PERIPHERALS_BASE + OFFSET_PRI0_FROM_COREBASE) ) 
typedef struct
{
    uint32   Reserved0:5;
    uint32   INTA:3;
    uint32   Reserved1:5;
    uint32   INTB:3;
    uint32   Reserved2:5;
    uint32   INTC:3;
    uint32   Reserved3:5;
    uint32   INTD:3; 
}Priox_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    Priox_fieldAccess_t fieldAccess;
}Priox_t;


/*========================*/
#define OFFSET_EN0_FROM_COREBASE      (0x100ul)
#define OFFSET_DIS0_FROM_COREBASE      (0x180ul)
#define ENx     ( (volatile ENx_t*)   (CORE_PERIPHERALS_BASE + OFFSET_EN0_FROM_COREBASE) ) 
#define DISx     ( (volatile DISx_t*)   (CORE_PERIPHERALS_BASE + OFFSET_DIS0_FROM_COREBASE) ) 

typedef struct
{
    uint32   NO_NEED;
}NotUsed_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    NotUsed_fieldAccess_t fieldAccess;
}ENx_t;

typedef union 
{
    uint32 regAccess;
    NotUsed_fieldAccess_t fieldAccess;
}DISx_t;



/*************************GPIO**********************************/
#define GPIO_BASE_ADDRESS_AHB       (0x40058000ul)
/*Expand GPIO_astr as casting of GPIOA_AHB's Address as pointer to structure*/
#define GPIO_P2str                  (( volatile GpioRegs_t *) (GPIO_BASE_ADDRESS_AHB))

typedef struct 
{
    uint32 GPIODATA[256]     ;    		/*Offset=0x000*/ 

	uint32 GPIODIR      	 ;    		/*Offset=0x400*/ 
	uint32 GPIOIS       	 ;    		/*Offset=0x404*/ 
	uint32 GPIOIBE      	 ;    		/*Offset=0x408*/ 
	uint32 GPIOIEV      	 ;    		/*Offset=0x40C*/ 
	uint32 GPIOIM       	 ;    		/*Offset=0x410*/ 
	uint32 GPIORIS      	 ;    		/*Offset=0x414*/ 
	uint32 GPIOMIS      	 ;    		/*Offset=0x418*/ 
	uint32 GPIOICR      	 ;    		/*Offset=0x41C*/ 
	uint32 GPIOAFSEL    	 ;    		/*Offset=0x420*/
							 
	uint32 Reserved0[55]	 ;

	uint32 GPIODR2R   		 ;     		/*Offset=0x500*/ 
	uint32 GPIODR4R   		 ;     		/*Offset=0x504*/ 
	uint32 GPIODR8R   		 ;     		/*Offset=0x508*/ 
	uint32 GPIOODR    		 ;     		/*Offset=0x50C*/ 
	uint32 GPIOPUR    		 ;     		/*Offset=0x510*/ 
	uint32 GPIOPDR    		 ;     		/*Offset=0x514*/ 
	uint32 GPIOSLR    		 ;     		/*Offset=0x518*/ 
	uint32 GPIODEN    		 ;     		/*Offset=0x51C*/ 
	uint32 GPIOLOCK   		 ;     		/*Offset=0x520*/ 
	uint32 GPIOCR     		 ;     		/*Offset=0x524*/ 
	uint32 GPIOAMSEL  		 ;     		/*Offset=0x528*/ 
	uint32 GPIOPCTL   		 ;     		/*Offset=0x52C*/ 
	uint32 GPIOADCCTL 		 ;     		/*Offset=0x530*/ 
	uint32 GPIODMACTL 		 ;     		/*Offset=0x534*/ 

	uint32 Reserved1[678]	 ;	  

	uint32 GPIOPeriphID4     ;			/*Offset=0xFD0*/ 
	uint32 GPIOPeriphID5     ;			/*Offset=0xFD4*/ 
	uint32 GPIOPeriphID6     ;			/*Offset=0xFD8*/ 
	uint32 GPIOPeriphID7     ;			/*Offset=0xFDC*/ 
	uint32 GPIOPeriphID0     ;			/*Offset=0xFE0*/ 
	uint32 GPIOPeriphID1     ;			/*Offset=0xFE4*/ 
	uint32 GPIOPeriphID2     ;			/*Offset=0xFE8*/ 
	uint32 GPIOPeriphID3     ;			/*Offset=0xFEC*/ 
	uint32 GPIOPCellID0      ;			/*Offset=0xFF0*/ 
	uint32 GPIOPCellID1      ;			/*Offset=0xFF4*/ 
	uint32 GPIOPCellID2      ;			/*Offset=0xFF8*/ 
	uint32 GPIOPCellID3      ;			/*Offset=0xFFC*/ 
}GpioRegs_t;

#endif /* MCU_HW_H */
