#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

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


#endif /* RCC_PRIVATE_H */
