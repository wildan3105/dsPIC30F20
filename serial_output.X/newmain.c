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
#include "uart.h"

char buf[10];

int main(){
    InitUART1();
//    InitUART2();
    while(1){
        WriteStringUART1("RECEIVED NOTHING!");
//        printf("Hello from DSPIC! \n\r");
    }
    return 0;
}

