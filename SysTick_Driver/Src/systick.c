#include "stm32f4xx.h"
#include "systick.h"
// Check Cortex-M4 generic User guide to systick.
// calculate the 1 ms delay -> we know delay = N/16000000 => 1ms = 16000 cycles
#define SYSTICK_LOAD_VAL     16000
#define CTRL_ENABLE          (1U<<0)
#define CTRL_CLKSRC          (1U<<2)
#define CTRL_COUNTFLAG       (1U<<16)


void systickDelayMS(int delay)
{
	/* Reload with number of clock per millisecond */
	SysTick->LOAD  = SYSTICK_LOAD_VAL;

	/* Clear systick current value register */
	SysTick->VAL = 0;

	/*Enable systick and select internal clk src */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay; i++)
	{
		/* Wait until the COUNTFLAG is set */

		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
	}

	SysTick->CTRL = 0;

}
