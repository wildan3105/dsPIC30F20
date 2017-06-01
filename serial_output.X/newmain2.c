/*********************************************************************
 *
 *      PIC32MX UART Library Interface Example
 *
 *********************************************************************
 * FileName:        uart_basic.c
 * Dependencies:    plib.h
 *
 * Processor:       PIC32MX
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the ?Company?) for its PIC32MX Microcontroller is intended
 * and supplied to you, the Company?s customer, for use solely and
 * exclusively on Microchip Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *********************************************************************
 * The purpose of this example code is to demonstrate the PIC32MX
 * peripheral library macros and functions supporting the UART
 * module and its various features.
 *
 * Platform: Explorer-16 with PIC32MX PIM
 *
 * Features demonstrated:
 *    - UART perepheral library usage
 *
 * Description:
 *      This program uses the UART library to communicate through
 *      the serial port on the Explorer-16. With an RS232 cable
 *      attatched to the Explorer-16 and a pc, the program will
 *      output text and recieve input using a terminal program.
 *
 * Notes:
 *    - PIC32MX 2xx PIMS are unconnected to the Explorer-16 DB9
 *      connector. It must be soldered to the test points on top of
 *      the PIM for proper functionality. The README file contains
 *      a list of the connections that need to be made.
 ********************************************************************/
#include <plib.h>

#if defined (__32MX360F512L__) || (__32MX460F512L__) || (__32MX795F512L__) || (__32MX430F064L__) || (__32MX450F256L__) || (__32MX470F512L__)
// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 80 MHz (SYSCLK / FPBDIV)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#define SYS_FREQ (80000000L)

#elif defined (__32MX220F032D__) || (__32MX250F128D__)
// Configuration Bit settings
// SYSCLK = 48 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 48 MHz (SYSCLK / FPBDIV)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
#pragma config FPLLMUL = MUL_24, FPLLIDIV = DIV_2, FPLLODIV = DIV_2, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#define SYS_FREQ (16000000UL)
#endif

#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)

#if defined (__32MX430F064L__) || (__32MX450F256L__) || (__32MX470F512L__)
#define UART_MODULE_ID UART1 // PIM is connected to Explorer through UART1 module
#else
#define UART_MODULE_ID UART2 // PIM is connected to Explorer through UART2 module
#endif

// Function Prototypes
void SendDataBuffer(const char *buffer, UINT32 size);
UINT32 GetMenuChoice(void);
UINT32 GetDataBuffer(char *buffer, UINT32 max_size);

// Constant Data
const char mainMenu[] =
{
    "Welcome to PIC32 UART Peripheral Library Demo!\r\n"\
    "Here are the main menu choices\r\n"\
    "1. View Actual BAUD rate\r\n"\
    "2. Use AUTOBAUD\r\n"\
    "3. Set Line Control\r\n"\
    "4. ECHO\r\n"
    "\r\n\r\nPlease Choose a number\r\n"
};

const char lineMenu[] =
{
    "Line Control Menu\r\n"\
    "You may need to change your line control on your terminal to see data\r\n"\
    "1. 8-N-1\r\n"\
    "2. 8-E-1\r\n"\
    "3. 8-O-1\r\n"\
    "4. 8-N-2\r\n"\
    "5. 8-E-2\r\n"\
    "6. 8-O-2\r\n"\
    "\r\n\r\nPlease Choose a number\r\n"
};

const UINT32 lineControl[] =
{
    (UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1),
    (UART_DATA_SIZE_8_BITS | UART_PARITY_EVEN | UART_STOP_BITS_1),
    (UART_DATA_SIZE_8_BITS | UART_PARITY_ODD | UART_STOP_BITS_1),
    (UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_2),
    (UART_DATA_SIZE_8_BITS | UART_PARITY_EVEN | UART_STOP_BITS_2),
    (UART_DATA_SIZE_8_BITS | UART_PARITY_ODD | UART_STOP_BITS_2)
};

int main(void)
{
    UINT32  menu_choice;
    UINT8   buf[1024];

    #if defined (__32MX220F032D__) || defined (__32MX250F128D__)
    PPSInput(2,U2RX,RPB5); // Assign RPB5 as input pin for U2RX
    PPSOutput(4,RPB0,U2TX); // Set RPB0 pin as output for U2TX
    #elif defined (__32MX430F064L__) || (__32MX450F256L__) || (__32MX470F512L__)
    PPSInput(2,U1RX,RPF4); // Assign RPF4 as input pin for U1RX
    PPSOutput(2,RPF5,U1TX); // Set RPF5 pin as output for U1TX
    #endif

    UARTConfigure(UART_MODULE_ID, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART_MODULE_ID, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART_MODULE_ID, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART_MODULE_ID, GetPeripheralClock(), 57600);
    UARTEnable(UART_MODULE_ID, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    SendDataBuffer(mainMenu, sizeof(mainMenu));

    while(1)
    {
        menu_choice = GetMenuChoice();

        switch(menu_choice)
        {
        case 1:
            sprintf(buf, "Actual Baud Rate: %ld\r\n\r\n", UARTGetDataRate(UART_MODULE_ID, GetPeripheralClock()));
            SendDataBuffer(buf, strlen(buf));
            break;
        
        case 2:
            SendDataBuffer("Press 'U' to allow AUTO BAUD to sync\r\n", strlen("Press 'U' to allow AUTO BAUD to sync\r\n"));
            
            UARTStartAutoDataRateDetect(UART_MODULE_ID);

            while(!UARTDataRateDetected(UART_MODULE_ID))
                ;

            sprintf(buf, "Actual Baud Rate: %ld\r\n\r\n", UARTGetDataRate(UART_MODULE_ID, GetPeripheralClock()));
            SendDataBuffer(buf, strlen(buf));
            break;

        case 3:
            SendDataBuffer(lineMenu, sizeof(lineMenu));
            menu_choice = GetMenuChoice();
            menu_choice--;

            if(menu_choice >= 6)
            {
                SendDataBuffer("Invalid Choice", sizeof("Invalid Choice"));
                SendDataBuffer(mainMenu, sizeof(mainMenu));
                break;
            }

            SendDataBuffer("Press Any Character after re-configuring your terminal\r\n", strlen("Press Any Character after re-configuring your terminal\r\n"));
            UARTSetLineControl(UART_MODULE_ID, lineControl[menu_choice]);

            menu_choice = GetMenuChoice();
            SendDataBuffer(mainMenu, sizeof(mainMenu));
           break;
            
        case 4:
            {
                UINT32 rx_size;

                SendDataBuffer("Type a message (less than 100 characters) and press return\r\n", strlen("Type a message (less than 100 characters) and press return\r\n"));
                
                rx_size = GetDataBuffer(buf, 1024);

                SendDataBuffer("You Typed:\r\n\r\n", strlen("You Typed:\r\n\r\n"));
                SendDataBuffer(buf, rx_size);
                SendDataBuffer("\r\n\r\nPress any key to continue", strlen("\r\n\r\nPress any key to continue"));
                GetMenuChoice();
            }
            break;

        default:
            SendDataBuffer(mainMenu, sizeof(mainMenu));

        }
    }

    return -1;
}
// *****************************************************************************
// void UARTTxBuffer(char *buffer, UINT32 size)
// *****************************************************************************
void SendDataBuffer(const char *buffer, UINT32 size)
{
    while(size)
    {
        while(!UARTTransmitterIsReady(UART_MODULE_ID))
            ;

        UARTSendDataByte(UART_MODULE_ID, *buffer);

        buffer++;
        size--;
    }

    while(!UARTTransmissionHasCompleted(UART_MODULE_ID))
        ;
}
// *****************************************************************************
// UINT32 GetDataBuffer(char *buffer, UINT32 max_size)
// *****************************************************************************
UINT32 GetDataBuffer(char *buffer, UINT32 max_size)
{
    UINT32 num_char;

    num_char = 0;

    while(num_char < max_size)
    {
        UINT8 character;

        while(!UARTReceivedDataIsAvailable(UART_MODULE_ID))
            ;

        character = UARTGetDataByte(UART_MODULE_ID);

        if(character == '\r')
            break;

        *buffer = character;

        buffer++;
        num_char++;
    }

    return num_char;
}
// *****************************************************************************
// UINT32 GetMenuChoice(void)
// *****************************************************************************
UINT32 GetMenuChoice(void)
{
    UINT8  menu_item;

    while(!UARTReceivedDataIsAvailable(UART_MODULE_ID))
        ;

    menu_item = UARTGetDataByte(UART_MODULE_ID);

    menu_item -= '0';

    return (UINT32)menu_item;
}
