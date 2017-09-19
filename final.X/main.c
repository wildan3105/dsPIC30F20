/*
 * File:   main.c
 * Author: Wildan S. Nahar
 *
 * Created on September 18, 2017, 12:37 PM
 */

// load libraries
#include "config.h"
#define FCY 8000000
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "xc.h"
#include <libpic30.h>
#include "formatter.h"

// define variables
unsigned int a1;
unsigned int a2;
float v2;

// init ADC
void Init_ADC(void)
{
    // TODO: instead of return a value each times, modify to return ~500 (based on available RAM bytes) adc value each times.
    // Store the ADC values into char buffer array and send to user space application.
	/* Set up the ADC Module */
	
	ADCONbits.ADSIDL    = 0;        /* Operate in Idle Mode	*/
	ADCONbits.FORM      = 0;        /* Output in Integer Format	*/
	ADCONbits.EIE       = 0;        /* Enable Early Interrupt */
	ADCONbits.ORDER     = 0;        /* Even channel first */
	ADCONbits.SEQSAMP   = 1;        /* Sequential Sampling Enabled */
    
    // sampling rate
    // FADC / 14 = 1.25 MHz @ 7.5 MIPS
	ADCONbits.ADCS      = 4;        /* Clock Divider is set up for Fadc/12 */
	
	ADPCFG              = 0;        /* ANx are analog input */
	ADSTAT              = 0;        /* Clear the ADSTAT register */
	ADCPC0bits.TRGSRC0  = 1;        /* Use SW trigger */
	ADCPC0bits.IRQEN0	= 1;		/* Enable the interrupt	*/
    
    /* Set up the conversion rate (sampling rate) */
    // ADCON3              = 0x0C04;   // Sample time = 12 Tad = 138.89 ns @ 18 MIPS -> 1/(12 * 138/89) = 600 ksps
	
	ADCONbits.ADON 	    = 1;        /* Start the ADC module	*/	
			
	/* Set up the Interrupts */
	
	IFS0bits.ADIF       = 0;        /* Clear AD Interrupt Flag */	
	IPC2bits.ADIP       = 4;        /* Set ADC Interrupt Priority */
	IEC0bits.ADIE       = 1;        /* Enable the ADC Interrupt */
	
	ADCPC0bits.SWTRG0   = 1;        /* Trigger the Conversion Pair 0 */	
    
    v2 = (float) ADCBUF1 / 1023 * 5;
    v2 = v2 - 2.5;
}

void __attribute__ ((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
    a1                  = ADCBUF0;
    a2                  = ADCBUF1;
    
    IFS0bits.ADIF       = 0; /* clear A/D interrupt */
    ADSTATbits.P0RDY    = 0;
}

// init UART
void Init_UART(void){
    __C30_UART = 1;
    
    _STSEL  = 0; // one stop bit
    _PDSEL0 = 0; // no parity
    _PDSEL1 = 0; // 8-bit
    _BRGH   = 1; // BRG generates 4 clocks per bit period (4x Baud Clock, high-speed mode)
    _UARTEN = 1; // enable UART
    
    /* Baudrate generator */
    // 9600     : 207   [check]
    // 19200    : 103   [check]
    // 38400    : 51    [check]
    // 57600    : 34    [check] - rev (19/9/2017)
    // 115200   : 16    [check] (115.2Kbps)
    // 230400   : 8     [check] - unstable
    // 460800   : 3     []
    // 921600   : 1     []
    
    U1BRG   = 16; // baudrate
}

int main(void) {
    Init_ADC();
    
    // FLOAT TO STRING CONVERSION
    float f = v2;
    char str[30];
    floatToString(f, str);
	       
    Init_UART();
       
    while(1){
//        printf("%d", a1);
//        printf(",");
//        printf("%d", a2);
//        printf(",");
        printf("0");
        printf(",");
        printf("%s", str);
        printf("\n");
        __delay_ms(10);
    }
    return 0;
}
