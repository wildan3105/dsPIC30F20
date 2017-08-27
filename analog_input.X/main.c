/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * Read analog input from AN1 
 * Created on April 27, 2017, 7:01 PM
 */

#define FCY 8000000UL // FCY = FOSC / 2

#include <xc.h>
#include <stdio.h>
#include <libpic30.h>
#include "config.h"
#include "p30f2020.h"

/*******************************************************************************
; * © 2006 Microchip Technology Inc.
; *
; * FileName:        main.c
; * Dependencies:    Header (.inc) files if applicable, see below
; * Processor:       dsPIC30F2020
; * Compiler:        MPLAB® C30 v3.00 or higher
; * IDE:             MPLAB® IDE v7.52 or later
; * Dev. Board Used: Sync Buck Converter Using SMPS dsPIC
; *
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
*
* REVISION HISTORY:
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Author            Date      Comments on this revision
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Sunil Fernandes  09/26/06  First release of source file
; * Sagar Khare      12/04/06  Hard-coded configuration bits setting
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; *
; * Description:
; * This code example sets up ADC  pair 0 (AN1,AN0) conversion to be triggered 	
; *  by software trigger. The EIE feature is enabled. In this example, the FRC 
; *  with Hi-Range is set up to run at  frequency of 14.55MHz. This will result
; *  in Fcy = 29.1 MHz.   The input clock to the ADC  clock divider will be
; *  Fadc = 232.8 MHz.
; *
; * Tcy = 34.364 nsec  													
; * Time required for one conversion  = 721.64 nsec		
; * Fadc = 232.8 MHz.
; *
; * The first end-of-conversion is detected by the ADC interrupt while the 
; * second end-of-conversion is detected by polling the PEND0 bit in the ADPC0
; * register.
; *
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
	
    // enable UART communication
    U1BRG = 8; // baudrate
    U1MODEbits.UARTEN = 1; // enable UART
    
    PORTA = 0xffff; 
    TRISAbits.TRISA9 = 0; 
    
	while (1)
	{
		while(ADCPC0bits.PEND0);    /* Wait for the 2nd conversion to
		                               complete	*/
		channel1Result 	= ADCBUF1;  /* Read the result of the second
		                               conversion	*/	
		ADCPC0bits.SWTRG0	= 1;    /* Trigger another conversion */

        printf("Resistance : %d", channel1Result);
        printf("\n");
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
