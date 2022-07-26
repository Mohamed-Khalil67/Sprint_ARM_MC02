#include "Gpio.h"
#include "Led.h"
#include "Timer.h"
#include "TM4C123GH6PM.h"

#define SW_PIN  GPIO_SW2_PIN

int main(void) {
	
		 GPIOF->DIR       |= LED_BLUE; // set blue pin as a digital output pin
		 GPIOF->DEN       |= LED_BLUE;  // Enable PF2 pin as a digital pin
		 Time1A_1sec_delay();
		while(1)
		{
			// do nothing wait for the interrupt to occur
		}

}
