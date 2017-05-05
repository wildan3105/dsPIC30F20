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
