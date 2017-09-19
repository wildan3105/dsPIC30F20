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

void Init_UART(void){
    __C30_UART = 1;
    
    _STSEL  = 0; // one stop bit
    _PDSEL0 = 0; // no parity
    _PDSEL1 = 0; // 8-bit
    _BRGH   = 1; // BRG generates 4 clocks per bit period (4x Baud Clock, high-speed mode)
    _UARTEN = 1; // enable UART
    
    /* Baudrate generator */
    // 38400    : 51    [check]
    // 57600    : 33    [check]
    // 115200   : 16    [check] (115.2Kbps)
    // 230400   : 8     [check] - unstable
    // 460800   : 3     []
    // 921600   : 1     []
    
    U1BRG   = 51; // baudrate
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
    
    Init_UART();
    
    while(1){
        printf("750,250 \n");
        __delay_ms(1000);
    };
    return -1;
}