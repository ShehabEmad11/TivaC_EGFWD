#ifndef MACROS_H
#define MACROS_H


#define SET_BIT(reg,bitOffset)          (reg |=  (1<<(bitOffset)))
#define CLR_BIT(reg,bitOffset)          (reg &= ~(1<<(bitOffset)))
#define ASSIGN_BIT(reg,bitOffset,Val)   (reg ^=  ((Val)<<(bitOffset)))
#endif /* MACROS_H */
