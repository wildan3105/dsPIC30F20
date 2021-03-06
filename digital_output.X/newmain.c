/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * 
 * Created on April 27, 2017, 7:01 PM
 */

#define FCY 8000000UL

#include <xc.h>
#include <libpic30.h>
#include "config.h"

int main(void){
            
    // DEFINE DIGITAL I/O
//    ADPCFG = 0xffff; // all pins of port B are digital
//    ADPCFGbits.PCFG5 = 1; // configures pin RB5 as digital
//    TRISBbits.TRISB5 = 0; // configures pin RB5 of port B as output
    
    PORTA = 0xffff; 
    TRISAbits.TRISA9 = 0; 
    while(1){
//        LATBbits.LATB5 = 1; // led ON
        PORTAbits.RA9 = 1;
        __delay_ms(1000);
    }
    return 0;
}

