/*
 * File:   main.c
 * Author: Wildan
 *
 * Created on July 17, 2017, 1:20 PM
 */

#define FCY 8000000UL // FCY = FOSC / 2

#include <xc.h>
#include <stdio.h>
#include <libpic30.h>
#include <p30F2020.h>
#include "config.h"

// FLOWCHART
/*
    1. Initialization (configuration bits and required)     [-]
    2. Read ADC from 2 channels                             []                    
    3. SPI Communication (DAC-offset & PGA-gain selection)  []
    4. Serial comm (with GUI)                               []
    5. Serial comm to LabVIEW                               []
 */

// ANALOG INPUT
// Converting 4 channels, auto-sample start, TAD conversion start, simultaneous sampling code
ADPCFG  = 0xFF78;   // RB0, RB1, RB2, & RB7 = analog -> should AN0-AN3
ADCON1  = 0x00EC;   // SIMSAT bit = 1 implies simultaneous sampling
                    // ASAM = 1 for auto sample after convert
ADCHS   = 0x0007;   // Connect AN7 as CH0 input

ADCSSL  = 0;
ADCON3  = 0x0302;   // Auto sampling 3 TAD, TAD = internal 2 TCY
ADCON2  = 0x030C;   // CHPS = 1x implies simultaneous cample CH0 to CH3. SMPI = 0011 for interrupt after 4 converts


ADCON1bits.ADON = 1;// turn ADC ON
while(1){
    ADC16Ptr        = &ADCBUF0;     // initialize ADCBUF pointer
    OutDataPtr      = &OutData[0];  // point to first TXbuffer value
    IFS0bits.ADIF   = 0;            // clear the interrupt
    while(IFS0bits.ADIF);
    for(count=0; count<4; count++){
        ADCValue = *ADC16Ptr++;
        LoadADC(ADCValue);
    }
}                   // repeat

// DAC
/*
    1. Output for offset1 and offset2
    2. Input range : 2.7 - 5.5 volt
    3. Output range : Vss to G * Vref (Gain : 1x or 2x) => 0 - 4.096 volt
    4. Comm : SPI
 */

// PGA 

// 