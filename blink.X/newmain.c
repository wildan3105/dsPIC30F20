/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 *
 * Created on April 27, 2017, 7:01 PM
 */

#define FCY 16000000
#define _XTAL_FREQ 16000000
#define __delay_ms(d) { __delay32( (unsigned long) (((unsigned long long) d)*(FCY)/1000ULL)); }

#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void delay(void) {
    long i = 65535;
    while(i--);        
}

int main(){
    ADPCFG = 1; // Setup A/D PORT CONFIGURATION REGISTER as digital
    TRISB = 0; // configures port B as output
    TRISBbits.TRISB5= 0; // configures pin RB5 of port B as output
    LATBbits.LATB5 = 1; // set pin as high
    
    while(1){
        LATBbits.LATB5 = 1; // set pin as high
        delay();
        LATBbits.LATB5 = 0; // set pin as low
        delay();
    }
    return 0;
}

