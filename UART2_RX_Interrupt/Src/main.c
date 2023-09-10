#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"


#define GPIOAEN				   (1U<<0) // Port A Enable
#define GPIOA_5				   (1U<<5) // LED

#define LED_PIN				   GPIOA_5

#define MAX_BUFFER_SIZE     128 // Maximum sentence length

char buffer[MAX_BUFFER_SIZE];
uint8_t buffer_index = 0;

static void uart_callback(void);

int main(void)
{

	/*1.Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	uart2_rx_interrupt_init();

	while(1)
	{

	}
}

// ------ If Want to led ON ----------
//static void uart_callback(void)
//{
//	key =  USART2->DR;
//
//	if(key == '1')
//		{
//			GPIOA->ODR |= LED_PIN;
//		}
//		else{
//			GPIOA->ODR &= ~LED_PIN;
//		}
//}

//------------ Read Data from Serial --------------
static void uart_callback(void)
{
    char received_char = USART2->DR;

    if (received_char != '\n' && buffer_index < MAX_BUFFER_SIZE - 1)
    {
        buffer[buffer_index++] = received_char;
    }
    else
    {
        buffer[buffer_index] = '\0'; // Null-terminate the buffer
        buffer_index = 0; // Reset the buffer index
        printf("Received: %s\n", buffer);
    }

}

void USART2_IRQHandler(void)
{
	/*ChecK if RXNE is set*/
	if(USART2->SR & SR_RXNE)
	{
		//Do something
		uart_callback();
	}
}



