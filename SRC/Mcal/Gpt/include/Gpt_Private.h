#ifndef GPT_PRIVATE_H
#define GPT_PRIVATE_H

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

#endif /* GPT_PRIVATE_H */
