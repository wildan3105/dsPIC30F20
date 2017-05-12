/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * 
 * Created on April 27, 2017, 7:01 PM
 */

#define FCY 16000000UL
//#define _XTAL_FREQ 16000000
//#define __delay_ms(d) { __delay32( (unsigned long) (((unsigned long long) d)*(FCY)/1000ULL)); }

#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"


int main(){
            
    // DEFINE DIGITAL I/O
    ADPCFG = 0xffff; // all pins of port B are digital
    ADPCFGbits.PCFG5 = 1; // configures pin RB5 as digital
    TRISBbits.TRISB5 = 0; // configures pin RB5 of port B as output
//    TRISBbits.TRISB0 = 1; // configures pin RB0 of port B as input
    
    while(1){
        LATBbits.LATB5 = 1; // led ON
        __delay_ms(500);
        LATBbits.LATB5 = 0; // led OFF
        __delay_ms(500);
    }
    return 0;
}

