/**********************************************************************************************************************
  *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpio.c
 *       Module:  Gpio
 *
 *  Description:  File for Gpio Module    
 * 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TM4C123GH6PM.h"
#include "Std_Types.h"
#include "Gpio.h"
#include "Gpio_Types.h"
#include "Mc_Hw.h"
#include "Common.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



void gpio_configure_pin_unlock(GPIOA_Type *GPIOx, uint16_t pin_no)
{
    GPIOx->LOCK = 0x4C4F434B; // Unlock the commit register
    GPIOx->CR |= (0x01 << pin_no); // Write 0x01 to the corresponding bit in commit register
}

void gpio_configure_pin_mode(GPIOA_Type *GPIOx, uint16_t pin_no, uint32_t mode)
{
    if(mode == GPIO_PIN_DIGITAL)
	{
        GPIOx->AMSEL = 0x00; //Disable analog mode
        GPIOx->DEN |= (0X01 << pin_no); // Enable digital I/O for the pin
    } 
	else if (mode == GPIO_PIN_ANALOG)
	{
		GPIOx->AMSEL |= (0x01 << pin_no); //Enbale Analog I/O for the pin
        GPIOx->DEN = 0X00; // Disable Digital
	}
}

void gpio_configure_pin_iotype(GPIOA_Type *GPIOx, uint16_t pin_no, uint32_t io_type)
{
    if(io_type == GPIO_PIN_OUTPUT)
	{
        GPIOx->DIR |= (0x01 << pin_no); // Set the bit to 1
    } 
	else if (io_type == GPIO_PIN_INPUT)
	{
        GPIOx->DIR &= ~(0x01 << pin_no); // Clear the bit as 0
    }
}

void gpio_configure_pin_pupd(GPIOA_Type *GPIOx, uint16_t pin_no, uint32_t pupd)
{
    if(pupd == GPIO_PIN_PULL_UP)
	{
        GPIOx->PUR |= (0x01 << pin_no); // Set the pull up register bit to 1
    } 
	else if(pupd == GPIO_PIN_PULL_DOWN) 
	{
        GPIOx->PDR |= (0x01 << pin_no); // Set the pull down register bit to 1
    } 
	else if (pupd == GPIO_PIN_OPEN_DRAIN) 
	{
        GPIOx->ODR |= (0x01 << pin_no); // Set the open drain register bit to 1
    }
}

/* TODO Continue implementation and testing */
void gpio_set_alt_function(GPIOA_Type *GPIOx, uint16_t Pin_id, uint32_t alt_fun_enable, uint32_t alt_fun_value)
{
    if(alt_fun_enable == GPIO_PIN_ENABLE_AF)
	{
		GPIOx->AFSEL |= (0x01 << Pin_id); // Enable alt func
		GPIOx->PCTL |= (alt_fun_value << (4 * Pin_id)); // Choose alt func
	} 
	else if (alt_fun_enable == GPIO_PIN_DISABLE_AF)
	{
		GPIOx->AFSEL &= ~(0x01 << Pin_id); // Disable alt func
    	GPIOx->PCTL &= (0x00 << (4 * Pin_id)); // Set PCTL to 0x0
	}
}

uint16_t gpio_read_from_pin(GPIOA_Type *GPIOx, uint16_t Pin_id)
{
    uint16_t Data;
    Data = ((GPIOx->DATA & (0x01 << Pin_id)) >> Pin_id);
    return Data;
}

void gpio_write_to_pin(GPIOA_Type *GPIOx, uint16_t Pin_id, uint8_t Level)
{
    if(Level) 
	{
		GPIOx->DATA |= (0x01 << Pin_id);
	} 
	else 
	{
		GPIOx->DATA &= ~(0x01 << Pin_id);
	}
}

void gpio_init(GPIOA_Type *GPIOx, gpio_pin_conf_t *gpio_pin_conf)
{
    gpio_configure_pin_unlock(GPIOx, gpio_pin_conf->pin);
	
    if(gpio_pin_conf->alternate != GPIO_PIN_UNSET)
	gpio_set_alt_function(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->enable_alt, gpio_pin_conf->alternate);
	
    if(gpio_pin_conf->mode != GPIO_PIN_UNSET)
	gpio_configure_pin_mode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->mode);
	
	if(gpio_pin_conf->io_type != GPIO_PIN_UNSET)
	gpio_configure_pin_iotype(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->io_type);
	
	if(gpio_pin_conf->pupd != GPIO_PIN_UNSET)
	gpio_configure_pin_pupd(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->pupd);
}

void gpio_configure_interrupt(GPIOA_Type *GPIOx, uint16_t Pin_id, uint32_t Level_Interrupt)
{
    if(Level_Interrupt == GPIO_INT_LEVEL){
		GPIOx->IS |= (0x01 << Pin_id);
	} else {
		GPIOx->IS &= ~(0x01 << Pin_id);
		switch(Level_Interrupt){
			case GPIO_INT_RISING_EDGE:
				GPIOx->IEV |= (0x01 << Pin_id);
				break;
			case GPIO_INT_FALLING_EDGE: /*Complement of RIsing Edge*/
				GPIOx->IEV &= ~(0x01 << Pin_id);
				break;
			case GPIO_INT_BOTH_EDGES:
				GPIOx->IBE |= (0x01 << Pin_id);
				break;
		}
	}
}

void gpio_enable_interrupt(GPIOA_Type *GPIOx, uint16_t Pin_id)
{
    GPIOx->IM |= (0x01 << Pin_id);
}


void gpio_clear_interrupt(GPIOA_Type *GPIOx, uint16_t Pin_id)
{
    /* If the mask interrupt status is 1, we need to clear it */
    if((GPIOx->MIS & (0x01 << Pin_id)) >> Pin_id){
		GPIOx->ICR |= (0x01 << Pin_id);
	}
}


void NVIC_enable_interrupt(uint16_t irq_no)
{
    uint32_t irq_pos = (irq_no % 32);
	if(irq_no <= REG0_END){
		EN0 |= (0x01 << irq_pos);
	} else if (irq_no >= REG1_START && irq_no <= REG1_END) {
		EN1 |= (0x01 << irq_pos);
	} else if (irq_no >= REG2_START && irq_no <= REG2_END) {
		EN2 |= (0x01 << irq_pos);
	} else if (irq_no >= REG3_START && irq_no <= REG3_END) {
		EN3 |= (0x01 << irq_pos);
	} else if (irq_no >= REG4_START && irq_no <= REG4_END) {
		EN4 |= (0x01 << irq_pos);
	}
}

void NVIC_disable_interrupt(uint16_t irq_no)
{
    uint32_t irq_pos = (irq_no % 32);
	// Enable the corresponding interrupt in NVIC
	if(irq_no <= REG0_END){
		DIS0 |= (0x01 << irq_pos);
	} else if (irq_no >= REG1_START && irq_no <= REG1_END) {
		DIS1 |= (0x01 << irq_pos);
	} else if (irq_no >= REG2_START && irq_no <= REG2_END) {
		DIS2 |= (0x01 << irq_pos);
	} else if (irq_no >= REG3_START && irq_no <= REG3_END) {
		DIS3 |= (0x01 << irq_pos);
	} else if (irq_no >= REG4_START && irq_no <= REG4_END) {
		DIS4 |= (0x01 << irq_pos);
	}
}

void NVIC_clear_interrupt(uint16_t irq_no)
{
    uint32_t irq_pos = (irq_no % 32);
	if(irq_no <= REG0_END){
		if((PEND0 & (0x01 << irq_pos)) >> irq_pos){
			UNPEND0 |= (0x01 << irq_pos);
		}
	} else if (irq_no >= REG1_START && irq_no <= REG1_END) {
		if((PEND1 & (0x01 << irq_pos)) >> irq_pos){
			UNPEND1 |= (0x01 << irq_pos);
		}
	} else if (irq_no >= REG2_START && irq_no <= REG2_END) {
		if((PEND2 & (0x01 << irq_pos)) >> irq_pos){
			UNPEND2 |= (0x01 << irq_pos);
		}
	} else if (irq_no >= REG3_START && irq_no <= REG3_END) {
		if((PEND3 & (0x01 << irq_pos)) >> irq_pos){
			UNPEND3 |= (0x01 << irq_pos);
		}
	} else if (irq_no >= REG4_START && irq_no <= REG4_END) {
		if((PEND4 & (0x01 << irq_pos)) >> irq_pos){
			UNPEND4 |= (0x01 << irq_pos);
		}
	}
}
/**********************************************************************************************************************
 *  END OF FILE: GPIO.c
 *********************************************************************************************************************/