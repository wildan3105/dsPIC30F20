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
#include <p30F2020.h>
#include "config.h"
//#include "uart.h"


int main(){
    int resistance;
    
    U1BRG = 26; // 19200 baudrate, 16000000 FCY
    U1MODEbits.UARTEN = 1;
    
    while(1){
//        resistance = analogRead(0); // read from A0
        resistance = 12;
        printf("as %d \n", resistance);
        __delay_ms(1000);
    }
    return 0;
}
