#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;
typedef signed char sint8;
typedef signed short int sint16;
typedef signed long int sint32;

/* NULL_PTR define with a void pointer to zero definition*/
#define NULL_PTR       ((void *)0)

typedef enum
{
    STD_LOW=0,
    STD_HIGH=1
}Std_ValuesType;


#define TRUE    (1u)
#define FALSE   (0u)

typedef enum
{    
    E_OK=0,
    E_NOK=1      
}Std_ReturnType;

#define STD_OFF (0u)
#define STD_ON  (1u)

#endif /* STD_TYPES_H */
