/*
 * File:   main.c
 * Author: Wildan
 *
 * Created on July 20, 2017, 10:18 AM
 */

#define FCY 8000000UL // FCY = FOSC / 2

#include <p30f2020.h>

#include <xc.h>
#include <stdio.h>
#include <libpic30.h>
#include "config.h"

// global variable
#define cs PORTEbits.RE5

void main(void){
    int i;
    
    // setting up external MCP4822 DAC
    SPI1CON1 = 0x0161; /* SPI master, PPRE=1:4, SPRE=1:7, Mode=16, ->1 */
    SPI1STAT = 0x0; /* SPI enable, clear SPIROV */
    TRISEbits.TRISE3 = 0x04; // SDI1
    TRISEbits.TRISE2 = 0xFEFF; // SCK1
    TRISEbits.TRISE5 = 0xFFFE; // CS
    
    while(1){
        for(i=0; i<4096; i++){
            cs = 0;
            SPI1BUF = 0x7000 | i;
            while(SPI1STATbits.SPITBF);
            cs = 1;
        }
    }
}