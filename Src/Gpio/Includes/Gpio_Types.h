/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpio_Types.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef GPIO_TYPES_H
#define GPIO_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CONFIGURE_GPIO_PINS 10
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum{
    NORMAL_MODE = 0,
    SPECIAL_MODE = 1
}PortPinMode;

typedef enum{ /* Page 677 */
    PullUp = 0,
    PullDown = 1,
    OpenDrain = 3
}AttachType;

typedef enum{ /* Page 673 */
    R2R = 0,
    R4R = 1,
    R8R = 2
}CurrentSelect;

typedef enum{ 
    LOW = 0,
    HIGH = 1
}LevelType;

typedef enum{ /* Page 663 */
    INPUT = 0,
    OUTPUT = 1
}DirectionMode;

typedef enum{
    PIN0 =0,
    PIN1 =1,
    PIN2 =2,
    PIN3 =3,
    PIN4 =4,
    PIN5 =5,
    PIN6 =6,
    PIN7 =7
}PinType;

typedef enum{ /* Page 688 */
    PortA,
    PortB,
    PortC,
    PortD,
    PortE,
    PortF
}PortType;

typedef struct{
    PinType Pin;
    PortType Port;
}ChannelType;


typedef struct{
    PortPinMode Mode;
    DirectionMode Direction;
    LevelType Level;
    CurrentSelect Current;
    AttachType Attach;
    ChannelType Channel;
}ConfigType;

typedef struct {
    uint16_t pin;
    uint32_t mode;
    uint32_t io_type;
    uint32_t pupd;
	uint32_t enable_alt;
    uint32_t alternate;
} gpio_pin_conf_t;

#endif /* GPIO_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Types.h
 *********************************************************************************************************************/
