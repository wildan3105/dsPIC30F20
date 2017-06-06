/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * 
 * Created on April 27, 2017, 7:01 PM
 */

#define FCY 8294400UL // FCY = FOSC / 2
//#define _XTAL_FREQ 16000000
//#define __delay_ms(d) { __delay32( (unsigned long) (((unsigned long long) d)*(FCY)/1000ULL)); }

#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include <p30F2020.h>
#include "config.h"
//#include "uart.h"


int main(void){
    
    U1BRG = 12; // 38400 baudrate
    U1MODEbits.UARTEN = 1; // enable UART
    
    printf("before \n");
    __delay_ms(1000);
    printf("after \n");
    while(1);
    return -1;
    
}
