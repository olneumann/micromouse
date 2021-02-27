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

#include "board.h"

void ioInit(void)
{    
    /*
     * Change I/O State of Pins 
     * All port pins are defined as inputs after a reset.
     * Pheripheral Module Enable can trigger output state automatically.
     */
    
    TRISBbits.TRISB11 = 0;          // [OUT] WATCHDOG LED
    
    TRISBbits.TRISB2 = 0;           // [OUT] SHUT_R
    TRISBbits.TRISB3 = 0;           // [OUT] SHUT_F
    TRISCbits.TRISC0 = 0;           // [OUT] SHUT_L
    
    TRISCbits.TRISC1 = 0;           // [OUT] LED_IND1
    TRISCbits.TRISC2 = 0;           // [OUT] LED_IND2
    
    TRISCbits.TRISC3 = 0;           // [OUT] UART_RX_IND
    
    /*
     * Remapping
     */
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    
    /*
     * Input Mapping
     * PERIPHERAL <- PIN (Pin Diagrams RPn)
     */
    
    // QEI
    RPINR14bits.QEA1R = 22;         // [IN] M1_A (<- RP22) 
    RPINR14bits.QEB1R = 23;         // [IN] M1_B (<- RP23)
    RPINR16bits.QEA2R = 24;         // [IN] M2_A (<- RP24)
    RPINR16bits.QEB2R = 25;         // [IN] M2_B (<- RP25)
    
    // UART
    RPINR18bits.U1RXR = 21;         // [IN] UART_RX (<- RP21)
    
    // INT
    // INT0 hard-coded on RP7 - INT_L
    RPINR0bits.INT1R = 6;           // [IN] INT_F (<- RP6)
    RPINR1bits.INT2R = 5;           // [IN] INT_R (<- RP5)
    
    /*
     * Analog Port Pins
     * The AD1PCFGL register has a default value of 0x0000; 
     * therefore, all pins that share ANx functions are analog
     * (not digital) by default.
     */
    
    AD1PCFGL = 0xFFFF;              // all analog pins now digital
    AD1PCFGLbits.PCFG0 = 0;         // [IN] BAT_SENSE
   
    /*
     * Output Mapping
     * PIN <- PERIPHERAL (RPnR codes | table 11-2)
     */   
    
    // UART
    RPOR10bits.RP20R = 0b00011;       // [OUT] UART_TX (-> RP21)
    
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    DELAY_150uS;
}

void boardInit(void)
{
    /* OSCILLATOR setup
     * [FIN]    20 MHz 
     * [N1]     4       -> [FPLLI]  5   MHz
     * [M]      25      -> [FVCO]   125 MHz
     * [N2]     2       -> [FOSC]   62.5  MHz
     * 
     * [FCY]    31.25 MHz  -> [TCYC]   32 ns
     */
    PLLFBDbits.PLLDIV = 23;             // M  = PLLDIV + 2
    CLKDIVbits.PLLPRE = 2;              // N1 = PLLPRE + 2
    CLKDIVbits.PLLPOST = 0;             // N2 = 2(PLLPOST + 1)
        
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    while (OSCCONbits.COSC != 0b011);
    while (OSCCONbits.LOCK != 1);
    
    ioInit();
    
    // board setup (avoid floating tristates)
    LED_IND1 = LEDOFF;
    LED_IND2 = LEDOFF;
    LED_W = LEDOFF;
    
    XSHUT_R = 1;
    XSHUT_F = 1;
    XSHUT_L = 1; 
    
    UART_RX_IND = 0;
}