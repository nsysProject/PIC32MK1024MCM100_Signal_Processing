/*******************************************************************************
  TMR Peripheral Library Interface Source File

  Company
    Microchip Technology Inc.

  File Name
    plib_tmr2.c

  Summary
    TMR2 peripheral library source file.

  Description
    This file implements the interface to the TMR peripheral library.  This
    library provides access to and control of the associated peripheral
    instance.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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

#include "device.h"
#include "plib_tmr2.h"
#include "definitions.h"


void TMR2_Initialize(void)
{
    /* Disable Timer */
    T2CON = 0;

    T2CONbits.TCKPS = 0b000;    // 1:1

    /* Clear counter */
    TMR2 = 0x0;

    /*Set period */
    PR2 = 0xFFFF;

//    Disable TMR-2 interrupt, we want to use the count feature
    IEC0bits.T2IE = 0;
}


void TMR2_Start(void)
{
    T2CONbits.ON  = 1;
}


void TMR2_Stop (void)
{
    T2CONbits.ON  = 0;
}

void TMR2_PeriodSet(uint16_t period)
{
    PR2  = period;
}

uint16_t TMR2_PeriodGet(void)
{
    return (uint16_t)PR2;
}

uint16_t TMR2_CounterGet(void)
{
    return (uint16_t)(TMR2);
}

void TMR2_CounterClear(void)
{
    TMR2 = 0;
}

void TMR2_CounterClearAndStart(void)
{
    TMR2_CounterClear();
    TMR2_Start();
}

uint16_t TMR2_CounterGetAndStop(void)
{
    uint16_t count = TMR2_CounterGet();
    TMR2_Stop();
    return(count);
}