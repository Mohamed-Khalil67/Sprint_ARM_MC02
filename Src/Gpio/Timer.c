#include "Led.h"
#include "Gpio.h"
#include "Timer.h"


TIMER1A_Handler()
{
	  if(TIMER1->MIS & 0x1)
		GPIOF->DATA  ^= LED_BLUE; /* toggle Blue LED*/
		TIMER1->ICR = 0x1;          /* Timer1A timeout flag bit clears*/
}

void Time1A_1sec_delay(void){
    SYSCTL->RCGCTIMER |= (1<<1);  /*enable clock Timer1 subtimer A in run mode */
    TIMER1->CTL = 0; /* disable timer1 output */
    TIMER1->CFG = 0x4; /*select 16-bit configuration option */
    TIMER1->TAMR = 0x02; /*select periodic down counter mode of timer1 */
    TIMER1->TAPR = 250-1; /* TimerA prescaler value */
    TIMER1->TAILR = 64000-1 ; /* TimerA counter starting count down value  */
    TIMER1->ICR = 0x1;          /* TimerA timeout flag bit clears*/
    TIMER1->IMR |=(1<<0); /*enables TimerA time-out  interrupt mask */
    TIMER1->CTL |= 0x01;        /* Enable TimerA module */
    NVIC->ISER[0] |= (1<<21); /*enable IRQ21 */
}