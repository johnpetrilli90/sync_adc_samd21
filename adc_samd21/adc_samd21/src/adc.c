/** 
 * @file adc.c
 * @author John Petrilli
 * @date 06.Sep.2024
 * @brief Interfaces with the ADC API to read six ADC channels on a 
 * interrupt timer round-robin style. It also converts the raw ADC code
 * into the appropriate units such as mV or mA 
*/
#include "adc.h"

// System Libraries
#include <stdint.h>
#include <stdbool.h>

// User Includes
#include "atmel_start.h"
#include "adc_api.h"


// Defines
#define ItoV_RATIO			1				///< pre-processor directive to define the current-to-voltage ratio (1V/A)
#define ADC_VREF_MV			1650			///< pre-processor directive to define adc reference in milli-volts
#define ADC_RESOLUTION		65535			///< pre-processor directive to define adc resolution (16-bit)
#define ADC_TIMER_MILLIS	10				///< pre-processor directive to define the adc read interval in milliseconds

// Global Variables
volatile uint16_t g_adc_mux_results[NUM_ADC_MUX_POS];

// Private Functions Declarations
static struct timer_task ADC_TIMER_task1;
static void adc_timer_cb(const struct timer_task *const timer_task);
static uint16_t adc_convert_raw_data(uint16_t raw_adc_code, adc_ch_t adc_input);

// Public Functions
/// @brief  Initialize the timer interval which the ADC will perform the round-robin reads
/// @param  void
/// @return void
void adc_timer_init(void)
{
	ADC_TIMER_task1.interval = ADC_TIMER_MILLIS;
	ADC_TIMER_task1.cb       = adc_timer_cb;
	ADC_TIMER_task1.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &ADC_TIMER_task1);
	timer_start(&TIMER_0);
}

/// @brief  Converts the raw ADC code into voltage or current readings
/// @param  uint16_t -	raw ADC code
/// @param  adc_ch_t -	the ADC mux channel the data was measured on
/// @return uint16_t -	The voltage or current reading in milli-units
static uint16_t adc_convert_raw_data(uint16_t raw_adc_code, adc_ch_t adc_input){
	double adc_val = 0;
	
	adc_val = raw_adc_code * ADC_VREF_MV * ItoV_RATIO / ADC_RESOLUTION;
	
	return (uint16_t)adc_val;
}


/// @brief  Interrupt callback for the ADC timer. This function performs round-robin reading on the ADC. 
/// one channel is read and converted, then the mux channel is changed and the next timer callback this
/// channel will be read.
/// @param  const struct timer_task *const timer_task -
/// @return void
static void adc_timer_cb(const struct timer_task *const timer_task)
{
	static adc_ch_t adc_input = E_ADC_AIN_2;
	uint16_t adc_value = 0;
	
	switch(adc_input){
		case E_ADC_AIN_2:
			adc_value = adc_convert_raw_data(adc_api_read(E_ADC_AIN_2), E_ADC_AIN_2);
			g_adc_mux_results[0] = adc_value;
			adc_input = E_ADC_AIN_3;
			break;
		case E_ADC_AIN_3:
			adc_value = adc_convert_raw_data(adc_api_read(E_ADC_AIN_3), E_ADC_AIN_3);
			g_adc_mux_results[1] = adc_value;
			adc_input = E_ADC_AIN_4;
			break;
		case E_ADC_AIN_4:
			adc_value = adc_convert_raw_data(adc_api_read(E_ADC_AIN_4), E_ADC_AIN_4);
			g_adc_mux_results[2] = adc_value;
			adc_input = E_ADC_AIN_5;
			break;
		case E_ADC_AIN_5:
			adc_value = adc_convert_raw_data(adc_api_read(E_ADC_AIN_5), E_ADC_AIN_5);
			g_adc_mux_results[3] = adc_value;
			adc_input = E_ADC_AIN_6;
			break;
		case E_ADC_AIN_6:
			adc_value = adc_convert_raw_data(adc_api_read(E_ADC_AIN_6), E_ADC_AIN_6);
			g_adc_mux_results[4] = adc_value;
			adc_input = E_ADC_AIN_7;
			break;
		case E_ADC_AIN_7:
			adc_value = adc_convert_raw_data(adc_api_read(E_ADC_AIN_7), E_ADC_AIN_7);
			g_adc_mux_results[5] = adc_value;
			adc_input = E_ADC_AIN_2;
			break;
		default:
			adc_input = E_ADC_AIN_2;
			break;		
	}
}