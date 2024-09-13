/** 
 * @file adc_api.h
 * @author John Petrilli
 * @date 06.Sep.2024
 * @brief Provides enum for ADC channels, union for ADC byte data, 
 * and public function definitions
 */
#ifndef ADC_API_H_
#define ADC_API_H_

// System Libraries
#include <stdint.h>

// User Includes
#include "atmel_start.h"

/// @brief enum containing the possible mux positions for the ADC
enum _config_adc_channels{
	E_ADC_AIN_2		= ADC_INPUTCTRL_MUXPOS_PIN2_Val,				//ain 2 
	E_ADC_AIN_3		= ADC_INPUTCTRL_MUXPOS_PIN3_Val,				//ain 3
	E_ADC_AIN_4		= ADC_INPUTCTRL_MUXPOS_PIN4_Val,				//ain 4 
	E_ADC_AIN_5		= ADC_INPUTCTRL_MUXPOS_PIN5_Val,				//ain 5 
	E_ADC_AIN_6		= ADC_INPUTCTRL_MUXPOS_PIN6_Val, 				//ain 6 
	E_ADC_AIN_7		= ADC_INPUTCTRL_MUXPOS_PIN7_Val,				//ain 7 
	E_ADC_INT_GND	= ADC_INPUTCTRL_MUXNEG_GND_Val,					//internal ground reference
	E_ADC_IO_GND	= ADC_INPUTCTRL_MUXNEG_GND_Val,					//IO ground reference
};

/// @brief  ASF4 adc data is communicated in byte sized chunks from a buffer. This union
/// is a quick and easy way to convert the byte buffer data into an int of various sizes
union _config_adc_data{
	uint8_t		ui8_array[4];
	uint16_t	ui16_data;	
};

typedef union _config_adc_data adc_union_t;			///< typedef union for user access to painlessly convert ADC byte data to ints
typedef enum _config_adc_channels adc_ch_t;			///< typedef enum for user access to possible ADC mux positions

// Public Function Declarations
void adc_api_init(void);
void adc_api_deinit(void);
uint16_t adc_api_read(adc_ch_t channel);

#endif /* ADC_API_H_ */