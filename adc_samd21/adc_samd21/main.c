#include <atmel_start.h>
#include "adc.h"
#include "adc_api.h"

extern volatile uint16_t g_adc_mux_results[NUM_ADC_MUX_POS];

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	adc_api_init();
	adc_timer_init();
	
	/* Replace with your application code */
	while (1) {
		asm("nop");
	}
}
