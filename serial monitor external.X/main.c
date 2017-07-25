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

int main(void){
    U1BRG = 12; // 38400 baudrate
    U1MODEbits.UARTEN = 1; // enable UART
    
    printf("test \n");
    while(1);
    return -1;
}