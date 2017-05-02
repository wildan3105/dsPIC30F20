/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 *
 * Created on April 27, 2017, 7:01 PM
 */

// dsPIC30F2020 blink example

// DSPIC30F2020 Configuration Bit Settings
// 'C' source line config statements

// xtal
#define _XTAL_FREQ 20000000

// FBS
#pragma config BWRP = BWRP_OFF          // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Code Protection (No Boot Segment)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (General Segment may be written)
#pragma config GSS = GSS_OFF            // General Segment Code Protection (Disabled)

// FOSCSEL
#pragma config FNOSC = PRIOSC_PLL       // Oscillator Mode (Primary Oscillator (HS, EC) w/ PLL)

// FOSC
#pragma config POSCMD = PRIOSC_OFF      // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = OSC2_CLKO     // OSCI/OSCO Pin Function (OSCO pin has clock out function)
#pragma config FRANGE = FRC_HI_RANGE    // Frequency Range Select (High Range)
#pragma config FCKSM = CSW_FSCM_OFF     // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config WDTPS = WDTPOST_PS32768  // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA0 = WDTPRE_PR128    // WDT Prescaler (1:128)
#pragma config WWDTEN = WINDIS_OFF      // Watchdog Timer Window (Non-Window mode)
#pragma config FWDTEN = FWDTEN_ON       // Watchdog Timer Enable (Enable)

// FPOR
#pragma config FPWRT = PWRT_128         // POR Timer Value (128ms)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <libpic30.h>

int main(void)
{
	// Make RDO as a digital output
	_TRISD0 = 0;

	// Blink LED on RD0
	while(1)
	{
		_LATD0 = 1;
		__delay32(150000000);
		_LATD0 = 0;
		__delay32(150000000);
	}
}