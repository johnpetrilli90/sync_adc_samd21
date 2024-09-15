/** 
 * @file adc_api.c
 * @author John Petrilli
 * @date 29.July.2024
 * @brief Provides access to the on-chip ADC peripheral.
*/
#include "adc_api.h"

// System Libraries
#include <stdint.h>
#include <atmel_start.h>

/// @brief  Initialize the on-chip ADC peripheral w/ ASF4 synchronous driver
/// @param  void
/// @return void
void adc_api_init(void){
	adc_sync_enable_channel(&ADC_0, 0);
}

/// @brief  De-initialize the on-chip ADC peripheral w/ ASF4 synchronous driver
/// @param  void
/// @return void
void adc_api_deinit(void){
	adc_sync_disable_channel(&ADC_0, 0);
}

/// @brief  Reads and returns the raw digital code from the adc
/// @param  adc_ch_t -	passes in the ADC mux channel to be read
/// @return uint16_t -	returns the 16bit adc code
uint16_t adc_api_read(adc_ch_t input){
	adc_union_t data;
	
	adc_sync_set_inputs(&ADC_0, input, E_ADC_INT_GND, 0);
	adc_sync_read_channel(&ADC_0, 0, &data.ui8_array[0], 2);
	
	return data.ui16_data;
}

