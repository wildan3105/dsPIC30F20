/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 * 
 * Created on April 27, 2017, 7:01 PM
 */

#include "config.h"

#define FCY 8000000 // FCY = FOSC / 2

#include <xc.h>
#include <libpic30.h>


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
    
    while(1){
        printf("test \n");
        __delay_ms(1000);
    };
    return -1;
}