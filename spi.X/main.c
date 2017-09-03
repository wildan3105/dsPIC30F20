/*
 * File:   main.c
 * Author: Wildan
 *
 * Created on July 20, 2017, 10:18 AM
 */

#define FCY 8000000UL // FCY = FOSC / 2

#include <p30f2020.h>
#include <stdio.h>
#include <libpic30.h>
#include "config.h"

// global variable
#define SPI_CS      _RE5  
#define SPI_CLK     _RE2
#define SPI_DATA    _RE3

const int GAIN      = 0x1;

void main(void){
    int i;
    
    // setting up external MCP4822 DAC
    SPI1STAT = 0x0;             // disable the SPI module (just in case)
    SPI1CON1 = 0x0161;          // FRAMEN = 0, SPIFSD = 0, DISSDO = 0, MODE16 = 0; SMP = 0; CKP = 1; CKE = 1; SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
    SPI1CON1bits.CKE = 0x00;
    SPI1CON1bits.CKP = 0x00;
    SPI1STATbits.SPIEN = 0x1;
    
    SPI_DATA    = 0x04; // SDI1
    SPI_CLK     = 0xFEFF; // SCK1
    SPI_CS      = 0x1; // CS
    
    int SPIExchange(int sendValue){e
        while(SPI1STATbits.SPITBF);
        SPI1BUF = sendValue;
        while(!SPI1STATbits.SPIRBF);
        return SPI1BUF;
    }
    
    // UART config
    __C30_UART = 1;
    U1BRG = 12; // baudrate
    U1MODEbits.UARTEN = 1; // enable UART
    
    while(1){
        for(i=0; i<4096; i++){
            SPI_CS = 0;
            SPI1BUF = 0x9C48 | i;
            while(SPI1STATbits.SPITBF);
            SPI_CS = 1;
        }
        __delay_ms(10);
    }
}