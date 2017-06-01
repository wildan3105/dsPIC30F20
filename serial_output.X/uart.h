/* 
 * File:   uart.c
 * Author: Harry
 *
 * Created on May 12, 2017, 4:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p30f2020.h>
#include <math.h>
#define UART1_BAUD 9600
#define UBRG1_VALUE (FCY/UART1_BAUD)/16 - 1

void InitUART1(void){
    U1BRG = UBRG1_VALUE; // baudrate 9600
    U1MODEbits.ALTIO = 0;
    IEC0bits.U1RXIE = 1;
    U1STA&=0xfffc;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
}

void WriteUART1(unsigned int data){
    while (U1STAbits.TRMT == 0);
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}
void WriteUART1dec2string(unsigned int data){
    unsigned char temp;
    data = 10;
    temp = data/100;
    WriteUART1(temp+'0');
    data=data-temp*1000;
    WriteUART1(temp+'0');
}

void WriteStringUART1(const char * s){
    while(*s)
        WriteUART1(*s++);
}