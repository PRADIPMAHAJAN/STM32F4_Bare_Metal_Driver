/* Connect Channel 1 ADC1 -> PA1 -> A1 */

#include "stm32f4xx.h"
#include "adc.h"
#include "stdio.h"
#include "stdint.h"

uint32_t sensor_value;

int main(void)
{
	pa1_adc_init();
	start_conversion();
	while(1)
	{
		sensor_value =  adc_read();
		printf("Sensor Value : %d \n\r", (int)sensor_value);
	}
}
