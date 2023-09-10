#include "stm32f4xx.h"

#define GPIOAEN          (1U<<0) // Enbale Port A
#define GPIOCEN          (1U<<2) // Enable Port C

#define PIN5             (1U<<5)
#define PIN13            (1U<<13)

#define LED_PIN          PIN5
#define BTN_PIN          PIN13

int main(void)
{
	/* Enable clock access to GPIOA and GPIOC */
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	/* Set PA5 as a Output Pin */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	/* Set PA13 as a Input Pin */
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);
	while(1)
	{
		// Check if BTN is Pressed
		if(GPIOC->IDR & BTN_PIN)
		{
			//Turn ON led
			GPIOA->BSRR = LED_PIN;
		}
		else{
			GPIOA->BSRR = (1U<<21);
		}
	}
}

