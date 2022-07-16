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











/*System Control*/
#define SYSTEMCONTROL_BASE_ADDRESS         (0x400FE000ul)
#define SYSCTRL_P2strRegs                  (( volatile SysCtrlRegs_t *) (SYSTEMCONTROL_BASE_ADDRESS))

typedef struct
{
    uint32   MOSCDIS:1;
    uint32   :3;
    uint32   OSCSRC:2;
    uint32   XTAL:5;
    uint32   BYPASS:1;
    uint32   :1;
    uint32   PWRDN:1;
    uint32   :3;
	uint32   PWMDIV:3;
	uint32 	 USEPWMDIV:1;
	uint32   :1;
	uint32   USESYSDIV:1;
	uint32   SYSDIV:4;
	uint32   ACG:1;
	uint32   :4; 
}Rcc_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    Rcc_fieldAccess_t fieldAccess;
}Rcc_t;



typedef struct
{
    uint32   :4;
    uint32   OSCSRC2:3;
    uint32   :4;
    uint32   BYPASS2:1;
	uint32   :1;
	uint32   PWRDN2:1;
	uint32   USBPWRDN:1;
	uint32   :7;
	uint32   SYSDIV2LSB:1;
	uint32   SYSDIV2:6;
	uint32   :1;
	uint32   DIV400:1;
	uint32   USERCC2:1;	
}Rcc2_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    Rcc_fieldAccess_t fieldAccess;
}Rcc2_t;



typedef struct
{
	uint32 DID0       ;        /*Offset= 0x000*/ 
	uint32 DID1       ;        /*Offset= 0x004*/ 
							 
	/*Legacy*/               
	uint32 DC0		   ;	  /*Offset= 0x008*/ 
	
	uint32 Reserved0_0;

	uint32 DC1         ;      /*Offset= 0x010*/ 
	uint32 DC2         ;      /*Offset= 0x014*/ 
	uint32 DC3         ;      /*Offset= 0x018*/ 
	uint32 DC4         ;      /*Offset= 0x01C*/ 
	uint32 DC5         ;       /*Offset= 0x020*/ 
	uint32 DC6         ;       /*Offset= 0x024*/ 
	uint32 DC7         ;       /*Offset= 0x028*/ 
	uint32 DC8         ;       /*Offset= 0x02C*/ 
	/*Legacy END*/            
							  
	uint32 PBORCTL     ;       /*Offset= 0x030*/ 

	uint32 Reserved0[3];
							  
	 /*Legacy*/         
	uint32 SRCR0	   ;	  /*Offset= 0x040*/ 
	uint32 SRCR1       ;      /*Offset= 0x044*/ 
	uint32 SRCR2       ;      /*Offset= 0x048*/ 
	/*Legacy END*/            

	uint32 Reserved1;									
						  
	uint32 RIS         ;      /*Offset= 0x050*/ 
	uint32 IMC         ;      /*Offset= 0x054*/ 
	uint32 MISC        ;      /*Offset= 0x058*/ 
	uint32 RESC        ;      /*Offset= 0x05C*/ 
	Rcc_t  RCC         ;      /*Offset= 0x060*/ 

	uint32 Reserved2[2];

	uint32 GPIOHBCTL   ;      /*Offset= 0x06C*/ 
	Rcc2_t RCC2        ;      /*Offset= 0x070*/ 

	uint32 Reserved3[2];

	uint32 MOSCCTL     ;      /*Offset= 0x07C*/ 


	uint32 Reserved4[32];								
							  
	/*Legacy*/                
	uint32 RCGC0	   ;  	  /*Offset= 0x100*/
	uint32 RCGC1       ;      /*Offset= 0x104*/
	uint32 RCGC2       ;      /*Offset= 0x108*/
	/*Legacy END*/  

	uint32 Reserved5[14];          
							  
	uint32 DSLPCLKCFG  ;      /*Offset= 0x144*/ 

	uint32 Reserved6   ;

	uint32 SYSPROP     ;      /*Offset= 0x14C*/ 
	uint32 PIOSCCAL    ;      /*Offset= 0x150*/ 
	uint32 PIOSCSTAT   ;      /*Offset= 0x154*/ 

	uint32 Reserved7[2]  ;

	uint32 PLLFREQ0    ;      /*Offset= 0x160*/ 
	uint32 PLLFREQ1    ;      /*Offset= 0x164*/ 
	uint32 PLLSTAT     ;      /*Offset= 0x168*/ 		

	uint32 Reserved7_1[7]   ;

	uint32 SLPPWRCFG   ;      /*Offset= 0x188*/ 
	uint32 DSLPPWRCFG  ;      /*Offset= 0x18C*/ 

	uint32 Reserved8[9];

	uint32 LDOSPCTL    ;      /*Offset= 0x1B4*/ 
	uint32 LDOSPCAL    ;      /*Offset= 0x1B8*/ 
	uint32 LDODPCTL    ;      /*Offset= 0x1BC*/ 			
	uint32 LDODPCAL    ;      /*Offset= 0x1C0*/ 

	uint32 Reserved9[2];

	uint32 SDPMST      ;      /*Offset= 0x1CC*/ 

	uint32 Reserved10[76];

	uint32 PPWD        ;      /*Offset= 0x300*/ 
	uint32 PPTIMER     ;      /*Offset= 0x304*/ 
	uint32 PPGPIO      ;      /*Offset= 0x308*/ 
	uint32 PPDMA       ;      /*Offset= 0x30C*/ 

	uint32 Reserved11;
							  
	uint32 PPHIB       ;       /*Offset= 0x314*/ 
	uint32 PPUART      ;       /*Offset= 0x318*/ 
	uint32 PPSSI       ;       /*Offset= 0x31C*/ 
	uint32 PPI2C       ;       /*Offset= 0x320*/ 

	uint32 Reserved12;

	uint32 PPUSB       ;       /*Offset= 0x328*/ 

	uint32 Reserved13[2];

	uint32 PPCAN       ;       /*Offset= 0x334*/ 
	uint32 PPADC       ;       /*Offset= 0x338*/ 
	uint32 PPACMP      ;       /*Offset= 0x33C*/ 
	uint32 PPPWM       ;       /*Offset= 0x340*/ 
	uint32 PPQEI       ;       /*Offset= 0x344*/ 

	uint32 Reserved15[4];								

	uint32 PPEEPROM    ;       /*Offset= 0x358*/ 
	uint32 PPWTIMER    ;       /*Offset= 0x35C*/ 

	uint32 Reserved16[104];								

	uint32 SRWD        ;       /*Offset= 0x500*/ 
	uint32 SRTIMER     ;       /*Offset= 0x504*/ 
	uint32 SRGPIO      ;       /*Offset= 0x508*/ 
	uint32 SRDMA       ;       /*Offset= 0x50C*/ 

	uint32 Reserved17;

	uint32 SRHIB       ;       /*Offset= 0x514*/ 
	uint32 SRUART      ;       /*Offset= 0x518*/ 
	uint32 SRSSI       ;       /*Offset= 0x51C*/ 
	uint32 SRI2C       ;       /*Offset= 0x520*/ 

	uint32 Reserved18;

	uint32 SRUSB       ;       /*Offset= 0x528*/ 

	uint32 Reserved19[2];								


	uint32 SRCAN       ;       /*Offset= 0x534*/ 
	uint32 SRADC       ;       /*Offset= 0x538*/ 
	uint32 SRACMP      ;       /*Offset= 0x53C*/ 
	uint32 SRPWM       ;       /*Offset= 0x540*/ 
	uint32 SRQEI       ;       /*Offset= 0x544*/ 

	uint32 Reserved20[4];								

	uint32 SREEPROM    ;       /*Offset= 0x558*/ 
	uint32 SRWTIMER    ;       /*Offset= 0x55C*/ 

	uint32 Reserved21[40];

	uint32 RCGCWD      ;       /*Offset= 0x600*/ 
	uint32 RCGCTIMER   ;       /*Offset= 0x604*/ 
	uint32 RCGCGPIO		;      /*Offset= 0x608*/ 
	uint32 RCGCDMA      ;      /*Offset= 0x60C*/ 

	uint32 Reserved22;

	uint32 RCGCHIB      ;      /*Offset= 0x614*/ 
	uint32 RCGCUART     ;      /*Offset= 0x618*/ 
	uint32 RCGCSSI      ;      /*Offset= 0x61C*/ 
	uint32 RCGCI2C      ;      /*Offset= 0x620*/ 	

	uint32 Reserved23;

	uint32 RCGCUSB      ;      /*Offset= 0x628*/ 

	uint32 Reserved24[2];

	uint32 RCGCCAN      ;      /*Offset= 0x634*/ 
	uint32 RCGCADC      ;      /*Offset= 0x638*/ 
	uint32 RCGCACMP     ;      /*Offset= 0x63C*/ 
	uint32 RCGCPWM      ;      /*Offset= 0x640*/ 
	uint32 RCGCQEI      ;      /*Offset= 0x644*/

	uint32 Reserved25[4];
	 
	uint32 RCGCEEPROM   ;      /*Offset= 0x658*/ 			//395
	uint32 RCGCWTIMER   ;      /*Offset= 0x65C*/ 

	uint32 Reserved26[40];

	uint32 SCGCWD       ;      /*Offset= 0x700*/ 
	uint32 SCGCTIMER    ;      /*Offset= 0x704*/ 
	uint32 SCGCGPIO     ;      /*Offset= 0x708*/ 
	uint32 SCGCDMA      ;      /*Offset= 0x70C*/ 

	uint32 Reserved27;

	uint32 SCGCHIB      ;      /*Offset= 0x714*/ 
	uint32 SCGCUART     ;      /*Offset= 0x718*/ 
	uint32 SCGCSSI      ;      /*Offset= 0x71C*/ 
	uint32 SCGCI2C      ;      /*Offset= 0x720*/ 

	uint32 Reserved28;

	uint32 SCGCUSB      ;      /*Offset= 0x728*/ 

	uint32 Reserved29[2];

	uint32 SCGCCAN      ;     /*Offset= 0x734*/     
	uint32 SCGCADC		;	  /*Offset= 0x738*/ 
	uint32 SCGCACMP     ;     /*Offset= 0x73C*/ 
	uint32 SCGCPWM      ;     /*Offset= 0x740*/ 
	uint32 SCGCQEI      ;     /*Offset= 0x744*/ 

	uint32 Reserved30[4];

	uint32 SCGCEEPROM   ;     /*Offset= 0x758*/ 
	uint32 SCGCWTIMER   ;     /*Offset= 0x75C*/ 

	uint32 Reserved31[40];

	uint32 DCGCWD       ;     /*Offset= 0x800*/ 
	uint32 DCGCTIMER    ;     /*Offset= 0x804*/ 
	uint32 DCGCGPIO     ;     /*Offset= 0x808*/ 
	uint32 DCGCDMA      ;     /*Offset= 0x80C*/ 

	uint32 Reserved32;

	uint32 DCGCHIB      ;     /*Offset= 0x814*/ 
	uint32 DCGCUART     ;     /*Offset= 0x818*/ 
	uint32 DCGCSSI      ;     /*Offset= 0x81C*/ 
	uint32 DCGCI2C      ;     /*Offset= 0x820*/ 

	uint32 Reserved33;

	uint32 DCGCUSB      ;     /*Offset= 0x828*/ 

	uint32 Reserved34[2];

	uint32 DCGCCAN      ;     /*Offset= 0x834*/ 
	uint32 DCGCADC      ;     /*Offset= 0x838*/ 
	uint32 DCGCACMP     ;     /*Offset= 0x83C*/ 
	uint32 DCGCPWM      ;     /*Offset= 0x840*/ 
	uint32 DCGCQEI      ;     /*Offset= 0x844*/ 

	uint32 Reserved35[4];

	uint32 DCGCEEPROM   ;     /*Offset= 0x858*/ 
	uint32 DCGCWTIMER   ;     /*Offset= 0x85C*/ 

	uint32 Reserved36[104];

	uint32 PRWD         ;     /*Offset= 0xA00*/ 
	uint32 PRTIMER	 	;  	  /*Offset= 0xA04*/
	uint32 PRGPIO       ;  	  /*Offset= 0xA08*/
	uint32 PRDMA        ;  	  /*Offset= 0xA0C*/

	uint32 Reserved37;

	uint32 PRHIB        ;  	  /*Offset= 0xA14*/
	uint32 PRUART       ;  	  /*Offset= 0xA18*/
	uint32 PRSSI        ;  	  /*Offset= 0xA1C*/
	uint32 PRI2C        ;  	  /*Offset= 0xA20*/

	uint32 Reserved38;

	uint32 PRUSB        ;  	  /*Offset= 0xA28*/

	uint32 Reserved39[2];

	uint32 PRCAN        ;  	  /*Offset= 0xA34*/
	uint32 PRADC        ;  	  /*Offset= 0xA38*/
	uint32 PRACMP       ;  	  /*Offset= 0xA3C*/
	uint32 PRPWM        ;  	  /*Offset= 0xA40*/
	uint32 PRQEI        ;  	  /*Offset= 0xA44*/

	uint32 Reserved40[4];

	uint32 PREEPROM     ;  	  /*Offset= 0xA58*/
	uint32 PRWTIMER     ;  	  /*Offset= 0xA5C*/
}SysCtrlRegs_t;






/*General Purpose TIMERS*/
#define GPTM_TIMERx_BASE_ADDRESS         (0x40030000ul)
#define GPTM_TIMER2_32_64_BASE_ADDRESS   (0x4004C000ul)


#define GPTM_TIMER0_16_32_To_TIMER1_32_64_P2strRegs                  (( volatile GPTMRegs_t *) (GPTM_TIMERx_BASE_ADDRESS))
#define GPTM_TIMER2To5_32_64_P2strRegs    						     (( volatile GPTMRegs_t *) (GPTM_TIMER2_32_64_BASE_ADDRESS))

typedef struct
{
    uint32   TAEN:1;
    uint32   TASTALL:1;
    uint32   TAEVENT:2;
    uint32   RTCEN:1;
    uint32   TAOTE:1;
    uint32   TAPWML:1;
    uint32   :1;
    uint32   TBEN:1;
	uint32   TBSTALL:1;
	uint32 	 TBEVENT:2;
	uint32   :1;
	uint32   TBOTE:1;
	uint32   TBPWML:1;
	uint32   reserved:17; 
}GPTMCTL_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    GPTMCTL_fieldAccess_t fieldAccess;
}GPTMCTL_Union_t;



typedef struct
{
    uint32   TATOIM:1;
    uint32   CAMIM:1;
    uint32   CAEIM:1;
    uint32   RTCIM:1;
    uint32   TAMIM:1;
    uint32   :3;
    uint32   TBTOIM:1;
    uint32   CBMIM:1;
	uint32   CBEIM:1;
	uint32 	 TBMIM:1;
	uint32   :4;
	uint32   WUEIM:1;
	uint32   :15; 
}GPTMIMR_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    GPTMIMR_fieldAccess_t fieldAccess;
}GPTMIMR_Union_t;



typedef struct
{
    uint32   TAMR:2;
    uint32   TACMR:1;
    uint32   TAAMS:1;
    uint32   TACDIR:1;
    uint32   TAMIE:1;
    uint32   TAWOT:1;
    uint32   TASNAPS:1;
    uint32   TAILD:1;
	uint32   TAPWMIE:1;
	uint32 	 TAMRSU:1;
	uint32   TAPLO:1;
	uint32   :20;
}GPTMTAMR_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    GPTMTAMR_fieldAccess_t fieldAccess;
}GPTMTAMR_Union_t;

typedef struct
{
    uint32   TATOCINT:1;
    uint32   CAMCINT:1;
    uint32   CAECINT:1;
    uint32   RTCCINT:1;
    uint32   TAMCINT:1;
    uint32   :3;
    uint32   TBTOCINT:1;
    uint32   CBMCINT:1;
	uint32   CBECINT:1;
	uint32 	 TBMCINT:1;
	uint32   :4;
	uint32   WUECINT:1;
	uint32   :15;
}GPTMICR_fieldAccess_t;

typedef union 
{
    uint32 regAccess;
    GPTMICR_fieldAccess_t fieldAccess;
}GPTMICR_Union_t;

typedef struct
{
	uint32 GPTMCFG					;  /*Offset=0x000*/
	GPTMTAMR_Union_t GPTMTAMR     	;  /*Offset=0x004*/
	uint32 GPTMTBMR     			;  /*Offset=0x008*/
	GPTMCTL_Union_t GPTMCTL     	;  /*Offset=0x00C*/
	uint32 GPTMSYNC     			;  /*Offset=0x010*/
	
	uint32 reserved0				;

	GPTMIMR_Union_t GPTMIMR      	;  /*Offset=0x018*/
	uint32 GPTMRIS      			;  /*Offset=0x01C*/
	uint32 GPTMMIS      			;  /*Offset=0x020*/
	GPTMICR_Union_t GPTMICR      	;  /*Offset=0x024*/
	uint32 GPTMTAILR    			;  /*Offset=0x028*/
	uint32 GPTMTBILR    			;  /*Offset=0x02C*/
	uint32 GPTMTAMATCHR 			;  /*Offset=0x030*/
	uint32 GPTMTBMATCHR 			;  /*Offset=0x034*/
	uint32 GPTMTAPR     			;  /*Offset=0x038*/
	uint32 GPTMTBPR     			;  /*Offset=0x03C*/
	uint32 GPTMTAPMR    			;  /*Offset=0x040*/
	uint32 GPTMTBPMR    			;  /*Offset=0x044*/
	uint32 GPTMTAR      			;  /*Offset=0x048*/
	uint32 GPTMTBR      			;  /*Offset=0x04C*/
	uint32 GPTMTAV      			;  /*Offset=0x050*/
	uint32 GPTMTBV      			;  /*Offset=0x054*/
	uint32 GPTMRTCPD    			;  /*Offset=0x058*/
	uint32 GPTMTAPS     			;  /*Offset=0x05C*/
	uint32 GPTMTBPS     			;  /*Offset=0x060*/
	uint32 GPTMTAPV     			;  /*Offset=0x064*/
	uint32 GPTMTBPV     			;  /*Offset=0x068*/
	
	uint32 reserved1[981]			;
	
	uint32 GPTMPP       			;  /*Offset=0xFC0*/

	uint32 reserved2[15]			;

}GPTMRegs_t;

#endif /* MCU_HW_H */
