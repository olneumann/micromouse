/*
 * File:   board.h
 * Author: oliver
 *
 * Created on 15. Dezember 2020, 12:02
 */

#ifndef BOARD_H
#define	BOARD_H

/* Frequencies */
#define FOSC        (80000000ULL)
#define FCY         (FOSC/2)  

/* LED */
#define LED_W       LATBbits.LATB11
#define LED_IND1    LATCbits.LATC1
#define LED_IND2    LATCbits.LATC2

#define LEDON       0
#define LEDOFF      1

/* Module control pins */

#define XSHUT_R     LATBbits.LATB2 // (active low)
#define XSHUT_F     LATBbits.LATB3 // (active low)
#define XSHUT_L     LATCbits.LATC0 // (active low)
#define UART_RX_IND LATCbits.LATC3 // (active low)

/* GPIO pins */
#define RP10        PORTBbits.RB10
#define AN1         PORTAbits.RA1

/* Button */
#define BTN         !PORTBbits.RB4 // (active low)

/**
 * \brief Initialize all board dependant functionality
 * \return 0 on success, -1 otherwise
 */
void boardInit(void);

#endif	/* BOARD_H */
