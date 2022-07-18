#ifndef MACROS_H
#define MACROS_H


#define SET_BIT(reg,bitOffset)          (reg |=  (1<<(bitOffset)))
#define CLR_BIT(reg,bitOffset)          (reg &= ~(1<<(bitOffset)))
#define ASSIGN_BIT(reg,bitOffset,Val)   (reg ^=  ((Val)<<(bitOffset)))


/*Todo Add Enable/Disable All Interrupts API*/
#define ENTER_CRITICAL_SECTION()    
#define EXIT_CRITICAL_SECTION()     

#endif /* MACROS_H */
