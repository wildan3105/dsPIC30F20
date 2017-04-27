/* 
 * File:   newmain.c
 * Author: Wildan S. Nahar
 *
 * Created on April 27, 2017, 7:01 PM
 */

// dsPIC30F2020 blink example
 
#include <xc.h>
#include <libpic30.h>

// configuration settings
_FOSC(CSW_FSCM_OFF & FRC_PLL16); // Fosc = 16x7.5 Mhz, i.e 30 MIPS
_FWDT(WDT_OFF);
_FBORPOR(MCLR_DIS);

int main(void)
{
	// Make RDO as a digital output
	_TRISD0 = 0;

	// Blink LED on RD0
	while(1)
	{
		_LATD0 = 1;
		__delay32(15000000);
		_LATD0 = 0;
		__delay32(15000000);
	}
}