/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 *
 * Created on April 27, 2017, 7:01 PM
 */

// dsPIC30F2020 blink example

// DSPIC30F2020 Configuration Bit Settings
// 'C' source line config statements

#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include <p30F2020.h>

// xtal
#define _XTAL_FREQ 160000000


// DSPIC30F2020 Configuration Bit Settings

// 'C' source line config statements

// FBS
#pragma config BWRP = BWRP_OFF          // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Code Protection (No Boot Segment)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (General Segment may be written)
#pragma config GSS = GSS_OFF            // General Segment Code Protection (Disabled)

// FOSCSEL
#pragma config FNOSC = PRIOSC           // Oscillator Mode (Primary Oscillator (HS, EC))

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = OSC2_CLKO     // OSCI/OSCO Pin Function (OSCO pin has clock out function)
#pragma config FRANGE = FRC_HI_RANGE    // Frequency Range Select (High Range)
#pragma config FCKSM = CSW_FSCM_OFF     // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config WDTPS = WDTPOST_PS32768  // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA0 = WDTPRE_PR128    // WDT Prescaler (1:128)
#pragma config WWDTEN = WINDIS_OFF      // Watchdog Timer Window (Non-Window mode)
#pragma config FWDTEN = FWDTEN_OFF      // Watchdog Timer Enable (Disable)

// FPOR
#pragma config FPWRT = PWRT_128         // POR Timer Value (128ms)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// #1 version
//void delay(void){
//    long i=65535;
//    while(i--);
//}
//
//int main(){
//    ADPCFG  = 0xFFFF;
//    TRISA   = 0x0000;
//    TRISB   = 0x0000;
//    
//    TRISD   = 0x0000;
//    TRISE   = 0x0000;
//    TRISF   = 0x0000;
//    
//    while(1){
//        PORTA   = 0xFFFF;
//        PORTB   = 0xFFFF;
//        
//        PORTD   = 0xFFFF;
//        PORTE   = 0xFFFF;
//        PORTF   = 0xFFFF;
//        delay();
//        
//        PORTA   = 0x0000;
//        PORTB   = 0x0000;
//        
//        PORTD   = 0x0000;
//        PORTE   = 0x0000;
//        PORTF   = 0x0000;
//        delay();
//    }
//    return 0;
//}

// #2 version
//int main(void)
//{
//	// Make RDO as a digital output
//	_TRISD0 = 0;
//
//	// Blink LED on RD0
//	while(1)
//	{
//		_LATD0 = 0xff;
//		__delay32(150000000);
//		_LATD0 = 0x00;
//		__delay32(150000000);
//	}
//}

// #3 version
int main(){
    _TRISD0 = 0x00;
    
    while(1){
        _RD0 = 0xff;
        __delay32(150000000);
        _RD0 = 0x00;
        __delay32(150000000);
    }
    return 0;
}

// #4 version
//void Delay(unsigned int a);
//int main(){
//    TRISDbits.TRISD0 = 0;
//    LATDbits.LATD0 = 0;
//    
//    while(1){
//        LATDbits.LATD0 = ~LATDbits.LATD0;
//        Delay(6000);
//    }
//    return 0;
//}
//
//void Delay(unsigned int a){
//    unsigned int i;
//    for(i=0; i<a; i++)
//        ;
//}