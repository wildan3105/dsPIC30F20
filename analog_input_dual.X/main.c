/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * Read dual analog input from pair 1 (AN1, AN0)
 * Created on April 27, 2017, 7:01 PM
 */

// SPI port configuration
#define SPI_OUT     _RE5
#define SPI_CLK     _RE2
#define SPI_CS      _RE5

#define FCY 8000000 // FCY = FOSC / 2

#include <xc.h>
#include <libpic30.h>
#include <p30f2020.h>
#include "config.h"

#include "spi.h"
#include "my_spi.h"

unsigned int a1 = 0;
unsigned int a2 = 0;

// SPI initialization
void Init_SPI(void)
{
    // setup the SPI peripheral
    SPI1STAT = 0x0;                             // disable the SPI module (just in case)
    SPI1CON1 = 0x0161;                          // FRAMEN = 0, SPIFSD = 0, DISSDO = 0, MODE16 = 0; SMP = 0; CKP = 1; CKE = 1; SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
    SPI1CON1bits.CKE = 0x00;
    SPI1CON1bits.CKP = 0x00;
    SPI1STAT = 0x8000;                          // enable the SPI module
}

// offset voltage by DAC over SPI
// the value from DAC should be the negative side of input
void DAC(void){
    // [1]
    // if DAC input code = 0 and Gain = 2 (bit 13 = 0)
    // Vout = (2.048 * 0)/4096 & G
    // Vout = (2.048 * 0)/4096 * 2 = 0
    
    // [2]
    // if DAC input code = 4095 and Gain = 2 
    // Vout = (2.048 * 4095)/4096 * 2 = 4.096 ~ since Vdd = 3.3v, so Vout = 3.3 volt
    
    unsigned long MSBuffer, LSBuffer;
    SPI_CS = 0; // low
    
    SPI1BUF = 0x07;
    while (!SPI1STATbits.SPIRBF);   //4.Check if SPI Transfer Completed
    MSBuffer = SPI1BUF;             //5.Read and Discard Data in SSPBUF 
    __delay_ms(200);

    SPI1BUF = 0xFF;   
    while (!SPI1STATbits.SPIRBF); 
    LSBuffer = SPI1BUF;

    SPI_CS = 1;
}

// gain amplifier by PGA over SPI
void PGA(void){
    // used to amplify or attenuate incoming signal
    // also to drive 2nd input to comparator inside PIC
    // the comparator will initiate interrupt when input voltage cross the threshold set by internal DAC
    
}

void Init_ADC(void)
{
		
	/* Set up the ADC Module */
	
	ADCONbits.ADSIDL    = 0;        /* Operate in Idle Mode	*/
	ADCONbits.FORM      = 0;        /* Output in Integer Format	*/
	ADCONbits.EIE       = 1;        /* Enable Early Interrupt */
	ADCONbits.ORDER     = 0;        /* Even channel first */
	ADCONbits.SEQSAMP   = 1;        /* Sequential Sampling Enabled */
	ADCONbits.ADCS      = 5;        /* Clock Divider is set up for Fadc/14 */
	
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
	
}

void __attribute__ ((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
    
    a1                  = ADCBUF0;
    a2                  = ADCBUF1;
    
    IFS0bits.ADIF       = 0;
}

int main(void){
    // LED indicator
    PORTA = 0xffff; 
    TRISAbits.TRISA9 = 0; 
    
    // initialize SPI
    Init_SPI();
    
    // initialize ADC
    Init_ADC();
    
    // UART config
    __C30_UART = 1;
    U1BRG = 12; // baudrate
    U1MODEbits.UARTEN = 1; // enable UART
    
    while(1){
        // LED ON
        PORTAbits.RA9 = 1;
        
        printf("%d", a1);
        printf(" | ");
        printf("%d", a2);
        printf("\n");
        __delay_ms(100);    // 100 miliseconds
    }
}