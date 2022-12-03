/*******************************************************************************
 System Interrupts File

  Company:
    Microchip Technology Inc.

  File Name:
    interrupt.c

  Summary:
    Interrupt vectors mapping

  Description:
    This file maps all the interrupt vectors to their corresponding
    implementations. If a particular module interrupt is used, then its ISR
    definition can be found in corresponding PLIB source file. If a module
    interrupt is not used, then its ISR implementation is mapped to dummy
    handler.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "interrupts.h"
#include "definitions.h"


// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

void application(void);
/****************************************************************************
 * CPU clock = 120MHz
 * Peripheral clock = CPU/2 = 60MHz
 * TMR3 configured to trigger ADC at 50KHz
 * Ignoring interrupt latency, the "max" count for "TMR2_count" should be: 
 * = 60MHz/50KHz = 1200 = Max count
 * 
 * In other words, during code execution if the "TMR2_count" has a value of 1200,
 * then, the "application" function is taking entire (1/50KHz) = 20uS
 * 
 * 1200 count = full 20uS is used by "application"
 * 
 * Example-1, if the "TMR2_count" has a value of 300,
 * then, the "application" function is taking (20/1200)*300 = 5uSec
 * 
 * 
 * Example-2, if the "TMR2_count" has a value of 800,
 * then, the "application" function is taking (20/1200)*800 = 13.3uSec
 *****************************************************************************/
uint16_t TMR2_Count;    // Used to get an idea about execution time



/* All the handlers are defined here.  Each will call its PLIB-specific function. */
void __ISR(_TIMER_3_VECTOR, ipl1SRS) TIMER_3_Handler (void)
{
//    uint32_t status = IFS0bits.T3IF;
    IFS0CLR = _IFS0_T3IF_MASK;    
}

void __ISR(_ADC_DATA1_VECTOR, ipl1SRS) ADC_DATA1_Handler (void)
{
    TMR2_CounterClearAndStart();    // Start counter
    application();                  // Application code here
    TMR2_Count = TMR2_CounterGetAndStop();  // End counter and read    
    X2CScope_Update();              // save value for debugging on X2CScope
    IFS3bits.AD1D1IF = 0;    
}




/*******************************************************************************
 End of File
*/
