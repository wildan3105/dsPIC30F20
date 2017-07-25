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
#include "config.h"

// 1. ANALOG INPUT
int main(void)
{
	int channel1Result;
		
	/* Set up the ADC Module */
	
	ADCONbits.ADSIDL    = 0;        /* Operate in Idle Mode	*/
	ADCONbits.FORM      = 0;        /* Output in Integer Format	*/
	ADCONbits.EIE       = 1;        /* Enable Early Interrupt */
	ADCONbits.ORDER     = 0;        /* Even channel first */
	ADCONbits.SEQSAMP   = 1;        /* Sequential Sampling Enabled */
	ADCONbits.ADCS      = 5;        /* Clock Divider is set up for Fadc/14 */
	
	ADPCFG              = 0xFFFC;   /* AN0 and AN1 are analog inputs */
	ADSTAT              = 0;        /* Clear the ADSTAT register */
	ADCPC0bits.TRGSRC0  = 1;        /* Use SW trigger */
	ADCPC0bits.IRQEN0	  = 1;		  /* Enable the interrupt	*/
	
	ADCONbits.ADON 	    = 1;        /* Start the ADC module	*/	
			
	/* Set up the Interrupts */
	
	IFS0bits.ADIF       = 0;        /* Clear AD Interrupt Flag */	
	IPC2bits.ADIP       = 4;        /* Set ADC Interrupt Priority */
	IEC0bits.ADIE       = 1;        /* Enable the ADC Interrupt */
	
	ADCPC0bits.SWTRG0   = 1;        /* Trigger the Conversion Pair 0 */	
    
    // 2. SERIAL COMM
    U1BRG = 8; // baudrate
    U1MODEbits.UARTEN = 1; // enable UART
    
    int resistance;
	
	while (1)
	{
		while(ADCPC0bits.PEND0);    /* Wait for the 2nd conversion to
		                               complete	*/
		channel1Result 	= ADCBUF1;  /* Read the result of the second
		                               conversion	*/	
		ADCPC0bits.SWTRG0	= 1;    /* Trigger another conversion */	
        
        resistance = channel1Result;
        printf("Resistance %d \n", resistance);
        
        __delay32(30000000);
	}
}

void __attribute__ ((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
	/* AD Conversion complete early interrupt handler */
	
	int channel0Result;                  
	
	IFS0bits.ADIF       = 0;        /* Clear ADC Interrupt Flag */
	channel0Result      = ADCBUF0;  /* Get the conversion result */
	ADSTATbits.P0RDY    = 0;        /* Clear the ADSTAT bits */	
}

// DAC
/*
    1. Output for offset1 and offset2
    2. Input range : 2.7 - 5.5 volt
    3. Output range : Vss to G * Vref (Gain : 1x or 2x) => 0 - 4.096 volt
    4. Comm : SPI
 */

// PGA 

// 