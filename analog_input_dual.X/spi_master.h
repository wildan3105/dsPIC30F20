/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _SPI_MASTER_H
#define _SPI_MASTER_H

#include <xc.h> // include processor files - each processor file is guarded.  

/* select SS pin*/
#define SS_PIN PORTEbits.RE4

/* Prototype of function */
/*=====================================================
 * @brief
 *     Initialize SPI(Master)
 * @param
 *     none:
 * @return
 *     none:
 * @note
 *     Enable SPI1
 *     Pin45:SCK1(EMUC3/INT0/RF6) -> OUTPUT
 *     Pin43:SDO1(EMUD3/RF8)      -> OUTPUT
 *     Pin44:SDI1(RF7)            -> INPUT
 *     Pin52:SS(RA14/INT3)        -> OUTPUT
 *===================================================*/
void spi_master_init(void);

/*=====================================================
 * @brief
 *     SPI Master transmit 1 byte data
 * @param
 *     byte_data:Transmit data
 * @return
 *     none:
 * @note
 *     none
 *===================================================*/
void spi_master_send(char byte_data);

#endif