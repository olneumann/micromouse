/*
 * File:   board.h
 * Author: oliver
 *
 * Created on 15. Dezember 2020, 12:02
 */

#ifndef BOARD_H
#define	BOARD_H

/* FREQUENCIES */
#define FOSC        (80000000ULL)
#define FCY         (FOSC/2)  

/* LED */
#define LED4        LATBbits.LATB15
#define LED5        LATBbits.LATB14
#define LED6        LATBbits.LATB13
#define LED7        LATBbits.LATB12
#define LEDON       0
#define LEDOFF      1

/* IOx Pins */
#define IO5         PORTBbits.RB2
#define IO6         PORTBbits.RB3
#define IO7         PORTBbits.RB6
#define IO8         PORTBbits.RB7
#define IO10        PORTBbits.RB11

/* Switches */
#define SW1         !PORTBbits.RB5 // (active low)

/**
 * \brief Initialize all board dependant functionality
 * \return 0 on success, -1 otherwise
 */
void boardInit(void);

#endif	/* BOARD_H */
