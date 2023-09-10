#include "exti.h"

#define GPIOCEN      (1U<<2)
#define SYSCFGEN     (1U<<14)


void pc13_exti_init(void)
{
	/*Disable global interrupt*/
	__disable_irq();

	/*Enable clock access for GPIOC*/
	RCC->AHB1ENR |= GPIOCEN;

	/* Set PC13 as Input */
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	/*Enable clock access for SYSCFG*/
	RCC->APB2ENR |= SYSCFGEN;

	/*Select PORTC for EXTI1 -> External Interrupt configuration register 4 start from 0 then 3*/
	SYSCFG->EXTICR[3] |= (1U<<5);

	/*Unmask EXTI13 interrupt mask register */
	EXTI->IMR |= (1U<<13);

	/*Select falling edge trigger Falling trigger selection register*/
	EXTI->FTSR |= (1U<<13);

	/*Enable EXTI13 line in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/*Enable global interrupt*/
	__enable_irq();
}
