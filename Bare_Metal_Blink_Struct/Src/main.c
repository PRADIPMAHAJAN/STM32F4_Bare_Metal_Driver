#include<stdint.h>
#define PERIPH_BASE        (0x40000000UL)
#define AHB1PERIPH_OFFSET  (0x00020000UL)
#define AHB1PERIPH_BASE    (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET       (0x0000U)

#define GPIOA_BASE         (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET         (0x3800UL)
#define RCC_BASE           (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN            (1U << 0)

#define PIN5               (1U << 5)
#define LED_PIN            PIN5


#define __IO volatile

typedef struct
{
	volatile uint32_t Dummy[12];
	volatile uint32_t AHB1ENR;
} RCC_Type_Def;

typedef struct
{
	volatile uint32_t MODER;       /* GPIO Port Mode register after offset :0x00    */
	volatile uint32_t Dummy[4];
	volatile uint32_t ODR;         /*GPIO port output data Register Address Offset :0x14 */
} GPIO_Type_Def;

#define RCC 		((RCC_Type_Def*) RCC_BASE)
#define GPIOA  		((GPIO_Type_Def*) GPIOA_BASE)


int main(void) {
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA5 as an Output Pin */
    GPIOA->MODER |= (1U << (5 * 2)); // Set Bit 10 to 1 (5 * 2 = 10)
    GPIOA->MODER &= ~(1U << (5 * 2 + 1)); // Set Bit 11 to 0 (5 * 2 + 1 = 11)

    while (1) {
        /* Set PA5 High */
        GPIOA->ODR ^= LED_PIN;
        for(int i=0; i<100000; i++){}
    }
}
