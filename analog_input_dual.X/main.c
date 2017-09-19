/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * Read dual analog input from pair 1 (AN1, AN0)
 * Created on April 27, 2017, 7:01 PM
 */

// SPI port configuration
//#define SPI_DATA        _RE3
//#define SPI_CLK         _RE2
//#define SPI_CS_DAC      _RE5
//#define SPI_CS_PGA1     _RE4

#define FCY 8000000 // FCY = FOSC / 2 | 7.5 MIPS | PLL is disabled
//#define _XTAL_FREQ 16000000

#include <stdio.h>
#include <math.h>
#include <xc.h>
#include <libpic30.h>
#include "config.h"

// test sin table
//#define uint8_t unsigned char
//#define uint16_t unsigned short
//#define int16_t short

//#define TABLE_SIZE 64;
//int sineTable[64];
//int counter = 0;

//#include "spi.h"
//#include "spi_master.h"

unsigned int a1 = 0;
unsigned int a2 = 0;
//int N = 50;

// array
unsigned char adc_value[100];

////unsigned int* array_pointer = adc_value;
//unsigned int voltage[50];
//int offset = 0;

// SPI initialization
//void Init_SPI (void)
//{    
//        
//    // SPISTAT
//    _SPIRBF     = 0; // receive is not complete, SPIxRXB is empty
//    _SPITBF     = 1; // transmit not started yet, SPIxTXB is full
//    _SPIROV     = 0; // no overflow has occured
//    _SPISIDL    = 0; // continue module operation in idle mode
//    _SPIEN      = 1; // enable module and configures SCKx, SDOx, SDIx, and SSx as serial port pins
//    
//    // SPICON1
//    _PPRE0      = 0; // -(master mode) primary prescale 64:1 
//    _PPRE1      = 1; // -(master mode) primary prescale 64:1
//    _SPRE0      = 0;
//    _SPRE1      = 0;
//    _SPRE2      = 1;
//    _MSTEN      = 1; // master mode
//    _CKP        = 0; // -(clock polarity select bit) idle state for clock is a HIGH, active state is a LOW
//    _SSEN       = 0; // (slave select enable bit) not used by module
//    _CKE        = 0; // -(SPIx clock edge select bit) according to bit 6
//    _SMP        = 1; // (master) input data sampled at end of data output time
//    _MODE16     = 1; // 16-bits word-wide
//    _DISSDO     = 0; // -disable SDOx
//    _DISSCK     = 0;
//    _PPRE       = 0;
//    _SPRE       = 0;
//}

// 2nd version of spi master init
//void spi_master_init(void)
//{
//    /*SPI Pin configuration*/
//    TRISEbits.TRISE2    = 0;    // SCK1 -> output
//    TRISEbits.TRISE3    = 1;    // SDI1 -> output
//    TRISEbits.TRISE4    = 0;    // SS   -> input
//    
//    /*Allow to configure SPI*/
//    SPI1STATbits.SPIEN  = 0;
//    
//    /*Clear overflow flag*/
//    SPI1STATbits.SPIROV = 0;
//    
//    /*Framed SPI support*/
//    SPI1CON2bits.FRMEN  = 0;
//    SPI1CON2bits.SPIFSD = 0;
//    
//    /*Disable SDO*/
//    SPI1CON1bits.DISSDO = 0;
//    
//    /*Select 16bit or 8 bit mode*/
//    SPI1CON1bits.MODE16 = 0;    // 8bit mode
//    
//    /*Configure SPI Mode*/
//    SPI1CON1bits.SMP    = 0;    // Input data sampled at middle of data output time
//    SPI1CON1bits.CKE    = 0;    // Serial output data changes on transition from idle clock state to active clock state
//    SPI1CON1bits.CKP    = 0;    // Idle state for clock is a low level; active state is a high level
//    
//    /*Master Mode Enable*/
//    SPI1CON1bits.MSTEN  = 1;
//    
//    /*Prescalar speed configuration*/
//    SPI1CON1bits.PPRE   = 0b11; // Primary prescalar    -> 1:1
//    SPI1CON1bits.SPRE   = 0b111;// Secondary prescalar  -> 1:1
//    
//    /*SS pin set high*/
//    SS_PIN              = 1;
//    
//    /*Enable SPI*/
//    SPI1STATbits.SPIEN  = 1;
//}

/*=====================================================
 * @brief
 *     SPI Master transmit 1 byte data
 * @param
 *     byte_data:Transmit data
 * @return
 *     none:
 * @note
 *     none
 *===================================================*/
//void spi_master_send(char byte_data)
//{
//    unsigned char dummy;
//    
//    dummy = SPI1BUF;
//    
//    while(SPI1STATbits.SPITBF = 1){
//        ;
//    }
//    
//    SS_PIN = 0;
//    SPI1BUF = byte_data;
//    
//    /*wait for*/
//    while(SPI1STATbits.SPITBF == 1)
//    {
//        ;
//    }
//    
//    /*wait for*/
//    while(SPI1STATbits.SPIRBF == 0)
//    {
//        ;
//    }
//    SS_PIN = 1;
//    dummy = SPI1BUF;
//}

// Write to DAC
//void Write_DAC ( unsigned int data )
//{
//    SPI_CS_DAC = 0;                 // select slave device : DAC
//    SPI1BUF = data;              // write the data out to the SPI peripheral
//    while( !SPI1STATbits.SPIRBF );  // wait for the data to be sent out
//    SPI_CS_DAC  = 1;                // deselect slave device, transmission complete
//}

// UART initialization
void Init_UART(void){
    __C30_UART = 1;
    
    _STSEL  = 0; // one stop bit
    _PDSEL0 = 0; // no parity
    _PDSEL1 = 0; // 8-bit
    _BRGH   = 1; // BRG generates 4 clocks per bit period (4x Baud Clock, high-speed mode)
    _UARTEN = 1; // enable UART
    
    /* Baudrate generator */
    // 38400    : 51    [check]
    // 57600    : 33    [check]
    // 115200   : 16    [check] (115.2Kbps)
    // 230400   : 8     [check] - unstable
    // 460800   : 3     []
    // 921600   : 1     []
    
    U1BRG   = 51; // baudrate
}

// SPI wait
//void SPI_wait(){
//    while(!SPI1STATbits.SPIRBF);
//}

// SPI read
//void SPI_read(){
//    SPI_wait();
//    return(SPI1BUF);
//}

// offset voltage by DAC through SPI
// the value from DAC should be the negative side of input
//void DAC(void){
//    // [1]
//    // if DAC input code = 0 and Gain = 2 (bit 13 = 0)
//    // Vout = (2.048 * 0)/4096 & G
//    // Vout = (2.048 * 0)/4096 * 2 = 0
//    
//    // [2]
//    // if DAC input code = 4095 and Gain = 2 
//    // Vout = (2.048 * 4095)/4096 * 2 = 4.096 ~ since Vdd = 3.3v, so Vout = 3.3 volt
//    
//    // Example : set output to be 2.5 volt
//    // DAC input code : 2500 => 1001110001001000 => hex : 9C48
//
//}

// gain amplifier by PGA through SPI
//void PGA(void){
//    // 8 bytes instruction
//    // 8 bytes data
//    // used to amplify or attenuate incoming signal
//    // also to drive 2nd input to comparator inside PIC
//    // the comparator will initiate interrupt when input voltage cross the threshold set by internal DAC
//    // gain selection : 1, 2, 5, and 10
//    
//    // Example, set gain to be 1
//    // instruction register : 000x xxx0
//    // gain register        : xxxx x000
//        // default (gain = 1)   : 000
//        // gain = 2             : 001
//        // gain = 5             : 011
//        // gain = 10            : 101
//    // channel register     : xxxx x000 -> using CH0 and CH1 
//        // - CH0 (default)  : 000 (dari analog : penguatan 1x)
//        // - CH1            : 001 (dari analog : penguatan 10x)
//    
//}

//void Init_ADC(void)
//{
//    // TODO: instead of return a value each times, modify to return ~500 (based on available RAM bytes) adc value each times.
//    // Store the ADC values into char buffer array and send to user space application.
//    /*  Code example
//     * buffer = new byte[1024] -> 10-bit ADC
//       int i;
//       for(i=0; i<arr_size; i++){
//        value = exynos_adc_read_ch();
//        valueArr[i] = value;
//        sprintf(singleStr, "%d", valueArr[i]);
//        memcpy(str+pos, &singleStr, value_size);
//        pos += 5;
//       }
//      if(count >= sizeOf(str)){
//        int r = copy_to_user(buffer, str, sizeof(str));
//        return r ? r : sizeof(r);
//      } else {
//        return -EINVAL;
//      }
//     */
//    /*
//        2nd example
//     * int i;
//        for(i=0;i<N;i++)
//        {
//        ADCON1bits.SAMP = 1; // start sampling then ... 
//        // after 31Tad go to conversion 
//        while (!ADCON1bits.DONE); // conversion done? 
//          array[i] = ADCBUF0; // yes then get ADC value 
//        }
//     */
//	/* Set up the ADC Module */
//	
//	ADCONbits.ADSIDL    = 0;        /* Operate in Idle Mode	*/
//	ADCONbits.FORM      = 0;        /* Output in Integer Format	*/
//	ADCONbits.EIE       = 0;        /* Enable Early Interrupt */
//	ADCONbits.ORDER     = 0;        /* Even channel first */
//	ADCONbits.SEQSAMP   = 1;        /* Sequential Sampling Enabled */
//    
//    // sampling rate
//    // FADC / 14 = 1.25 MHz @ 7.5 MIPS
//	ADCONbits.ADCS      = 4;        /* Clock Divider is set up for Fadc/12 */
//	
//	ADPCFG              = 0;        /* ANx are analog input */
//	ADSTAT              = 0;        /* Clear the ADSTAT register */
//	ADCPC0bits.TRGSRC0  = 1;        /* Use SW trigger */
//	ADCPC0bits.IRQEN0	= 1;		/* Enable the interrupt	*/
//    
//    /* Set up the conversion rate (sampling rate) */
//    // ADCON3              = 0x0C04;   // Sample time = 12 Tad = 138.89 ns @ 18 MIPS -> 1/(12 * 138/89) = 600 ksps
//	
//	ADCONbits.ADON 	    = 1;        /* Start the ADC module	*/	
//			
//	/* Set up the Interrupts */
//	
//	IFS0bits.ADIF       = 0;        /* Clear AD Interrupt Flag */	
//	IPC2bits.ADIP       = 4;        /* Set ADC Interrupt Priority */
//	IEC0bits.ADIE       = 1;        /* Enable the ADC Interrupt */
//	
//	ADCPC0bits.SWTRG0   = 1;        /* Trigger the Conversion Pair 0 */	
//	
//}

//void __attribute__ ((interrupt, no_auto_psv)) _ADCInterrupt(void)
//{
//    a1                  = ADCBUF0;
//    
////    int i;
////    for(i=0; i<100; i++){
//////        ADCON1bits.SAMP = 1; // start sampling
//////        while(!ADCPC0bits.PEND0 == 0); // conversion done?
////        adc_value[i] = ADCBUF1;
//////        voltage[i] = ((adc_value[i] / 1023.0) * 5.0) - 2.5 + offset;
////    }
//    
//    a2                  = ADCBUF1;
////    a2                  = ((a2 / 1023) * 5);
//    
//    IFS0bits.ADIF       = 0; /* clear A/D interrupt */
//    ADSTATbits.P0RDY    = 0;
//    
//    // Voltage conversion
//    // Range assumption : +/- 3volt
//    // v[i] = ((y[i] / 1023) * 3.0) - 1.5 + offset
//}

int main(void){
    //int i;
    // LED indicator
    PORTA = 0xffff; 
    TRISAbits.TRISA9 = 0; 
   
    // initialize ADC
//    Init_ADC();
//    
//    // initialize UART
    Init_UART();
    
    // initialize SPI
    //Init_SPI();
    
    // 2nd version of SPI initialization
//    spi_master_init();
    
    while(1){
        
        // write to DAC
        //Write_DAC(0x3FFF);
        
        // 2nd write dummy SPI data
//        spi_master_send(0x1);
               
        // LED ON
        PORTAbits.RA9 = 1;
//        int i;
//        for(i=0; i<50; i++){
//            printf("%d", voltage[i]);
//            printf("\n");
//        }
        
//        printf("%d", a1);
//        printf(",");
//        printf("%d", a2);
//        printf("test");
        
        // test sine table
        printf("test \n");
        
        __delay_ms(10);    // 100 miliseconds
    }
    return -1;
}