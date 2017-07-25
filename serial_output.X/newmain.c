/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * 
 * Created on April 27, 2017, 7:01 PM
 */

#define FCY 8000000UL // FCY = FOSC / 2

#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include <p30F2020.h>
#include "config.h"

void Delay(void)
{
    int temp;
    for(temp = 0; temp < 1000; temp++ );
}

int main(void){
    // baudrate - U1BRG with BRG = 0
    /* 
        1. 38400    : 12    checked
        2. 57600    : 8     checked
        3. 115200   : 4     
            - 4 NOT COMPATIBLE
            - 5 NOT WORKING
            - 3 NOT COMPATIBLE
        4. 230400   : 2
     * max baudrate should : 1Mbps
     */
    
    U1BRG = 12; // baudrate
    U1MODEbits.UARTEN = 1; // enable UART
    
    printf("test \n"); 
   Delay();
    while(1);
    return -1;
}