/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Std_Types.h
 *    Component:  -
 *       Module:  -
 *
 *  Description:  Provision of Standard Types
 *
 *********************************************************************************************************************/



#ifndef STD_TYPES_H
#define STD_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

# include "Platform_Types.h"
# include "Compiler.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define STD_HIGH     1u /* Physical state 5V or 3.3V */
# define STD_LOW      0u /* Physical state 0V */

# define STD_ACTIVE   1u /* Logical state active */
# define STD_IDLE     0u /* Logical state idle */

# define STD_ON       1u
# define STD_OFF      0u

# define TRUE       true
# define FALSE     false
# define ENABLED       1
# define DISABLED      0
# define SET           1
# define CLEAR         0
# define SUCCESS       0
# define ERROR		  -1

#ifndef NULL
#define NULL  ((void*)0)
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint8 Std_ReturnType;
#define E_OK          0u
#define E_NOT_OK      1u

typedef unsigned char             uint8_t;
typedef signed char               sint8_t;
typedef unsigned int              uint32_t;
typedef signed int                sint32_t;
typedef signed int                Std_ReturnType;
typedef unsigned short            uint16_t;
typedef signed short              sint16_t;
typedef signed long long int      sint64_t;
typedef unsigned long long int    uint64_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* STD_TYPES_H */
/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
