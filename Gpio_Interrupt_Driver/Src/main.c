#include<stdio.h>
#include "stm32f4xx.h"
#include "exti.h"

/* Led */
#define GPIOAEN          (1U<<0)
#define PIN5             (1U<<5)
#define LED_PIN          PIN5
/* ---------------------*/

static void exti_callback(void);

int main(void)
{
	/* LED */
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);
	/*--------------------------*/
	pc13_exti_init();
	while(1)
	{

	}
}

static void exti_callback(void)
{
	printf("BTN Pressed....\n\r"); // use UART2 for print this.
	GPIOA->BSRR = LED_PIN;
	for(int i=0; i<1000000; i++){}
	GPIOA->BSRR = (1U<<21);
}

void EXTI15_10_IRQHandler(void)
{
	/* Set 1 Pending register of EXTI_PR*/
	if((EXTI->PR & LINE13) != 0)
	{
		/* Clear PR Flag*/
		EXTI->PR |= LINE13;
		/* Do something...*/
		exti_callback();
	}
}
