/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * Read dual analog input from pair 1 (AN1, AN0)
 * Created on April 27, 2017, 7:01 PM
 */

// SPI port configuration
#define SPI_DATA        _RE3
#define SPI_CLK         _RE2
#define SPI_CS_DAC      _RE5
#define SPI_CS_PGA1     _RE4

#define FCY 8000000 // FCY = FOSC / 2

#include <xc.h>
#include <libpic30.h>
#include <p30f2020.h>
#include "config.h"

#include "spi.h"

unsigned int a1 = 0;
unsigned int a2 = 0;

// SPI initialization
void Init_SPI (void)
{
    // SPISTAT
    _SPIRBF     = 0; // receive is not complete, SPIxRXB is empty
    _SPITBF     = 1; // transmit not started yet, SPIxTXB is full
    _SPIROV     = 0; // no overflow has occured
    _SPISIDL    = 0; // continue module operation in idle mode
    _SPIEN      = 1; // enable module and configures SCKx, SDOx, SDIx, and SSx as serial port pins
    
    // SPICON1
    _PPRE0      = 0; // (master mode) primary prescale 64:1 
    _PPRE1      = 0; // (master mode) primary prescale 64:1
    _SPRE0      = 0;
    _SPRE1      = 0;
    _SPRE2      = 0;
    _MSTEN      = 1; // master mode
    _CKP        = 0; // -(clock polarity select bit) idle state for clock is a HIGH, active state is a LOW
    _SSEN       = 0; // (slave select enable bit) not used by module
    _CKE        = 0; // -(SPIx clock edge select bit) according to bit 6
    _SMP        = 1; // (master) input data sampled at end of data output time
    _MODE16     = 1; // 16-bits word-wide
    _DISSDO     = 0; // -disable SDOx
    _DISSCK     = 0;
    _PPRE       = 0;
    _SPRE       = 0;
}

// UART initialization
void Init_UART(void){
    __C30_UART = 1;
    
    _STSEL  = 0; // one stop bit
    _PDSEL0 = 0; // no parity
    _PDSEL1 = 0; // 8-bit
    _BRGH   = 1; // BRG generates 4 clocks per bit period (4x Baud Clock, high-speed mode)
    _UARTEN = 1; // enable UART
    
    U1BRG = 51; // baudrate
}

void Write_DAC ( unsigned int data )
{
    SPI_CS_DAC = 0;                 // select slave device : DAC
    int temp;
    temp = SPI1BUF;                 // dummy read of the SPI1BUF register to clear the SPIRBF flag
    SPI1BUF = data;              // write the data out to the SPI peripheral
    while( !SPI1STATbits.SPIRBF );  // wait for the data to be sent out
    SPI_CS_DAC  = 1;                // deselect slave device, transmission complete
}

// random sinusoidal table

// offset voltage by DAC through SPI
// the value from DAC should be the negative side of input
void DAC(void){
    // [1]
    // if DAC input code = 0 and Gain = 2 (bit 13 = 0)
    // Vout = (2.048 * 0)/4096 & G
    // Vout = (2.048 * 0)/4096 * 2 = 0
    
    // [2]
    // if DAC input code = 4095 and Gain = 2 
    // Vout = (2.048 * 4095)/4096 * 2 = 4.096 ~ since Vdd = 3.3v, so Vout = 3.3 volt
    
    // Example : set output to be 2.5 volt
    // DAC input code : 2500 => 1001110001001000 => hex : 9C48
    
//    unsigned long MSBuffer, LSBuffer;
//    SPI_CS = 0; // low
//    
//    SPI1BUF = 0x07;
//    while (!SPI1STATbits.SPIRBF);   //4.Check if SPI Transfer Completed
//    MSBuffer = SPI1BUF;             //5.Read and Discard Data in SSPBUF 
//    __delay_ms(200);
//
//    SPI1BUF = 0xFF;   
//    while (!SPI1STATbits.SPIRBF); 
//    LSBuffer = SPI1BUF;
//
//    SPI_CS = 1;
}

// gain amplifier by PGA through SPI
void PGA(void){
    // 8 bytes instruction
    // 8 bytes data
    // used to amplify or attenuate incoming signal
    // also to drive 2nd input to comparator inside PIC
    // the comparator will initiate interrupt when input voltage cross the threshold set by internal DAC
    // gain selection : 1, 2, 5, and 10
    
    // Example, set gain to be 1
    // instruction register : 000x xxx0
    // gain register        : xxxx x000 -> default (gain = 1) : 000
    // channel register     : xxxx x000 -> using CH0 and CH1 
        // - CH0 (default)  : 000
        // - CH1            : 001
    
}

void Init_ADC(void)
{
		
	/* Set up the ADC Module */
	
	ADCONbits.ADSIDL    = 0;        /* Operate in Idle Mode	*/
	ADCONbits.FORM      = 0;        /* Output in Integer Format	*/
	ADCONbits.EIE       = 0;        /* Enable Early Interrupt */
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
    IFS0bits.ADIF       = 0; /* clear A/D interrupt */
    ADSTATbits.P0RDY    = 0;
}

int main(void){
    // LED indicator
    PORTA = 0xffff; 
    TRISAbits.TRISA9 = 0; 
   
    // initialize UART
    // Init_UART();
       
    // initialize ADC
    //Init_ADC();
    
    while(1){
        // initialize SPI
        Init_SPI();
        
        // write to DAC
        Write_DAC(0x9C48);
               
        // LED ON
        PORTAbits.RA9 = 1;
        
        printf("%d", a1);
        printf(" | ");
        printf("%d", a2);
        printf("\n");
        __delay_ms(100);    // 100 miliseconds
    }
    
    return 0;
}