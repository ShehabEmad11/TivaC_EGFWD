#ifndef INTRCTRL_PRIVATE_H
#define INTRCTRL_PRIVATE_H


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









#endif /* INTRCTRL_PRIVATE_H */
