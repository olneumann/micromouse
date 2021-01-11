/*
 * File:   board.c
 * Author: oliver
 *
 * Created on 15. Dezember 2020, 12:02
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "../common/defines.h"
#include "../drivers/serial_uart.h"

#include "xc.h"
#include "board.h"

void ioInit(void)
{    
    /*
     * Change I/O State of Pins 
     */
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB6 = 0;
    
    /*
     * Remapping
     */
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    
    /*
     * Input Mapping
     * PERIPHERAL <- PIN (Pin Diagrams RPn)
     */
    
    // QEI
    //RPINR14bits.QEA1R = 6;          // QEI1 A -> RP6
    //RPINR14bits.QEB1R = 7;          // QEI1 B -> RP7
    //RPINR16bits.QEA2R = 6;          // QEI2 A -> RPx
    //RPINR16bits.QEB2R = 7;          // QEI2 B -> RPx
    
    // UART
    RPINR18bits.U1RXR = 10;         // U1RX -> RP10 (IO9)
    
    // AD Switch
    //AD1PCFGLbits.PCFG4 = 1;
    //AD1PCFGLbits.PCFG5 = 1;
   
    /*
     * Output Mapping
     * PIN <- PERIPHERAL (RPnR codes | table 11-2)
     */   
    
    // UART
    RPOR5bits.RP11R = 0b00011;       // RP11 <- U1TX (IO10)
    
    __builtin_write_OSCCONL(OSCCON | 0x40);
        
    DELAY_150uS;
}

//#define TEST_OSZ 

void boardInit(void)
{
    /* OSCILLATOR setup
     * The external oscillator runs at 20 MHz
     * PLL is used to generate 80 MHz clock (FOSC)
     * The relationship between oscillator and cycle frequency: FCY = FOSC/2
     * Have a look at "PLL Configuration" paragraph in the mcu manual
     */
    
#ifdef TEST_OSZ
    /* Result: FCY = 0.5 * (20 MHz*32/(4*2)) = 40.0 MIPS, which is 
     * not exactly Tcycle=25nsec, but close enough for our purposes
     */
    PLLFBDbits.PLLDIV = 30;                     // M  = PLLDIV + 2
    CLKDIVbits.PLLPRE = 2;                      // N1 = PLLPRE + 2
    CLKDIVbits.PLLPOST = 0;                     // N2 = 2(PLLPOST + 1)
#else
     /* Result: FCY = 0.5 * (7.3728 MHz*20/(2*2)) = 26.73 MIPS, which is 
      * not exactly Tcycle=37.5nsec, but close enough for our purposes
      */
    PLLFBDbits.PLLDIV = 128;                    // M  = PLLDIV + 2
    CLKDIVbits.PLLPRE = 4;                      // N1 = PLLPRE + 2
    CLKDIVbits.PLLPOST = 0;                     // N2 = 2(PLLPOST + 1)
#endif
    
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);
    
    /* IO setup
     */
    ioInit();
}