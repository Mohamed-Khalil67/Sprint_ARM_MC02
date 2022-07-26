/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpio.h
 *       Module:  Gpio
 *
 *  Description:  header file for Gpio Module    
 *  
 *********************************************************************************************************************/
#ifndef GPIO_H
#define GPIO_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "TM4C123GH6PM.h"
#include "Std_Types.h"
#include "Mc_Hw.h"
#include "Gpio_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Set enable registers */
#define EN0										(*((volatile unsigned long *) 0xE000E100))
#define EN1										(*((volatile unsigned long *) 0xE000E104))
#define EN2										(*((volatile unsigned long *) 0xE000E108))
#define EN3										(*((volatile unsigned long *) 0xE000E10C))
#define EN4										(*((volatile unsigned long *) 0xE000E110))

/* Clear enable registers */
#define DIS0									(*((volatile unsigned long *) 0xE000E180))
#define DIS1									(*((volatile unsigned long *) 0xE000E184))
#define DIS2									(*((volatile unsigned long *) 0xE000E188))
#define DIS3									(*((volatile unsigned long *) 0xE000E18C))
#define DIS4									(*((volatile unsigned long *) 0xE000E190))
	
/* Set pending registers */
#define PEND0									(*((volatile unsigned long *) 0xE000E200))
#define PEND1									(*((volatile unsigned long *) 0xE000E204))
#define PEND2									(*((volatile unsigned long *) 0xE000E208))
#define PEND3									(*((volatile unsigned long *) 0xE000E20C))
#define PEND4									(*((volatile unsigned long *) 0xE000E210))
	
/* Clear pending registers */
#define UNPEND0								    (*((volatile unsigned long *) 0xE000E280))
#define UNPEND1								    (*((volatile unsigned long *) 0xE000E284))
#define UNPEND2								    (*((volatile unsigned long *) 0xE000E288))
#define UNPEND3								    (*((volatile unsigned long *) 0xE000E28C))
#define UNPEND4								    (*((volatile unsigned long *) 0xE000E290))
	
/* IRQn range */
#define REG0_START							       0
#define REG0_END								  31
#define REG1_START								  32
#define REG1_END								  63
#define REG2_START								  64
#define REG2_END								  95
#define REG3_START								  96
#define REG3_END								 127
#define REG4_START						         128
#define REG4_END								 131

/* GPIO unset flag */
/* For Verification unset registers */
#define GPIO_PIN_UNSET                     	    ((uint32_t)0x00)

/* GPIO mode setting values */
#define GPIO_PIN_ANALOG                     	((uint32_t)0x00)
#define GPIO_PIN_DIGITAL                    	((uint32_t)0x01)

/* Page 671 GPIO alt func setting values */
/* Reset Value is at 0x000.0000 controlled by GPIO registers */
#define GPIO_PIN_DISABLE_AF                   	((uint32_t)0x00)
#define GPIO_PIN_ENABLE_AF                   	((uint32_t)0x01)

/* GPIO direction setting values */
/* Page 663 Setting Pin Direction for comparison in functions */
#define GPIO_PIN_INPUT                     	    ((uint32_t)0x00)
#define GPIO_PIN_OUTPUT                    	    ((uint32_t)0x01)

/* GPIO pull up/down type selection values */
/* Page 676 setting variables globales For Comparison to choose Mode of State zero */
#define GPIO_PIN_NO_PUPD						((uint32_t)0x00)
#define GPIO_PIN_PULL_UP                        ((uint32_t)0x01)
#define GPIO_PIN_PULL_DOWN                      ((uint32_t)0x02)
#define GPIO_PIN_OPEN_DRAIN             		((uint32_t)0x03)

/* GPIO interrupt sense type selection values */
/* Page 664 setting variables globales For Comparison to choose Mode of interrupt */
#define GPIO_INT_RISING_EDGE				    ((uint32_t)0x00)
#define GPIO_INT_FALLING_EDGE				    ((uint32_t)0x01)
#define GPIO_INT_BOTH_EDGES					    ((uint32_t)0x02)
#define GPIO_INT_LEVEL	                        ((uint32_t)0x03)


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 /* Enable the clock for different ports using RCC registers */
#define RCC_GPIOF_CLK_ENABLE()      SYSCTL->RCGC2 |= (0x01 << 5);

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  APIs PROTOTYPES
 *********************************************************************************************************************/
 
void gpio_configure_pin_unlock(GPIOA_Type *GPIOx, uint16_t Pin_id);

void gpio_configure_pin_modse(GPIOA_Type *GPIOx, uint16_t Pin_id, uint32_t mode);

void gpio_configure_pin_iotype(GPIOA_Type *GPIOx, uint16_t Pin_id, uint32_t io_type);

void gpio_configure_pin_pupd(GPIOA_Type *GPIOx, uint16_t Pin_id, uint32_t pupd);

/* TODO Continue implementation and testing */
void gpio_set_alt_function(GPIOA_Type *GPIOx, uint16_t Pin_id, uint32_t alt_fun_enable, uint32_t alt_fun_value);

uint16_t gpio_read_from_pin(GPIOA_Type *GPIOx, uint16_t Pin_id);

void gpio_write_to_pin(GPIOA_Type *GPIOx, uint16_t Pin_id, uint8_t Level);

void gpio_init(GPIOA_Type *GPIOx, gpio_pin_conf_t *gpio_pin_conf);

void gpio_configure_interrupt(GPIOA_Type *GPIOx, uint16_t Pin_id, uint32_t int_conf);

void gpio_enable_interrupt(GPIOA_Type *GPIOx, uint16_t Pin_id);


void gpio_clear_interrupt(GPIOA_Type *GPIOx, uint16_t Pin_id);


void NVIC_enable_interrupt(uint16_t irq_no);

void NVIC_disable_interrupt(uint16_t irq_no);

void NVIC_clear_interrupt(uint16_t irq_no);

#endif /* Gpio_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpio.h
 *********************************************************************************************************************/
