#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
/**************************************************************************
 *
 *
 **************************************************************************/
#define ADC_VREF                (3.3f)
#define ADC_MAX_COUNT           (4095)
/**************************************************************************
 *
 *
 **************************************************************************/
int16_t adc_count0, adc_count1;
float input_voltage0, input_voltage2;
volatile bool result_ready = false;
/**************************************************************************
 *
 *
 **************************************************************************/
void application(void)
{
    /* Read the ADC result */
    if(ADCHS_ChannelResultIsReady(ADCHS_CH0))   // We will check status of ADC-0 data only
    {
        adc_count0 = ADCHS_ChannelResultGet(ADCHS_CH0);  
    }
    adc_count1 = ADCHS_ChannelResultGet(ADCHS_CH1); // For ADC-1, check is not needed, since ISR is for ADC-1
    
    input_voltage0 = (float)adc_count0 * ADC_VREF / ADC_MAX_COUNT;
    input_voltage2 = (float)adc_count1 * ADC_VREF / ADC_MAX_COUNT;
	input_voltage2 = 0;

    result_ready = true;    
}
/**************************************************************************
 *
 *
 **************************************************************************/