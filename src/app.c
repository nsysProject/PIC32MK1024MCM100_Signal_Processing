#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "trig.h"
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
#define TAYLOR_SERIES_IMPLEMENTATION
/**************************************************************************
 *
 *
 **************************************************************************/
void application(void)
{
    /* Read the ADC result. This code is kept for future use. */
    if(ADCHS_ChannelResultIsReady(ADCHS_CH0))   // We will check status of ADC-0 data only
    {
        adc_count0 = ADCHS_ChannelResultGet(ADCHS_CH0);  
    }
    adc_count1 = ADCHS_ChannelResultGet(ADCHS_CH1); // For ADC-1, check is not needed, since ISR is for ADC-1
    
//    input_voltage0 = (float)adc_count0 * ADC_VREF / ADC_MAX_COUNT;
//    input_voltage2 = (float)adc_count1 * ADC_VREF / ADC_MAX_COUNT;
    
#ifdef TAYLOR_SERIES_IMPLEMENTATION    
//====================TMR2_Count = 200========================================
    // Angle is incremented at (200/50000) * (2*PI) = 0.0251 radians
    // This is an arbitrary angle increment rate, used for testing purpose
    Taylor_SincosParm.angle += (200.0*((2.0*M_PI)/TMR_3_ADC_TRIGGER_FREQ));
    
    // Angle range is from 0 to (2*PI) radians or 0 to 360 degrees. After that, roll.
    // This is unsigned format for angle. Use either the unsigned or signed format. Not both.
//    if(Taylor_SincosParm.angle >= (2*M_PI))
//    {
//        Taylor_SincosParm.angle = Taylor_SincosParm.angle - (2*M_PI); 
//    }
    
    // Angle range is from -PI to PI radians or -180 to 180 degrees. After that, roll.
    // This is signed format for angle. Use either the unsigned or signed format. Not both.
    if(Taylor_SincosParm.angle >= (M_PI))
    {
        Taylor_SincosParm.angle = (M_PI - Taylor_SincosParm.angle) + (-M_PI);
    }
    
    Taylor_SinCos(&Taylor_SincosParm);
//========================================================================
#endif
    result_ready = true;    
}
/**************************************************************************
 *
 *
 **************************************************************************/