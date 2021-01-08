/*
 * File:   TIMERconfig.c
 * Author: oliver
 *
 * Created on 11. November 2020, 17:39
 */

#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>

#include "../dspic/board.h"
#include "../common/defines.h"

#include "serial_uart.h"
#include "dma.h"

#include "xc.h"
#include "timer.h"

/**
 * \brief Calculation of register bits for optimal accuracy
 * \param[in] _ms - period [ms]
 * \param[out] pTiCON - Timer Control register
 * \param[out] pTMR - Timer Count register
 * \param[out] pPR - Timer Period register
 * \return 0 on sucess, -1 otherwise
 */
int timerParams(int _ms, volatile uint16_t* pTiCON, volatile uint16_t* pTMR, volatile uint16_t* pPR)
{
    int err = -1;
    
    long double ticks = _ms * 1e-3 * FCY; 
    int iTCKPS[4] = {1,8,64,256};                   // (00 | 01 | 10 | 11)
    char maskTCKPS[4] = {0x00,0x10,0x20,0x30};      // mask for setting 2 bits (xxxx.xxxx xx--.xxxx)
    int i = 0;

    do {
        long double dPR = ticks/iTCKPS[i];
        if (dPR <= 65535)                           // 16bit register
        {
            *pPR = (uint16_t)dPR - 1;               // set PRi register
            *pTMR = 0;                              // reset timer
            *pTiCON |= maskTCKPS[i];                // set prescaler
            err = 0;
            break;
        }
        i++;
        err = -1;
    } while(i < 4); 
    
    return err;
}

void enableTimer(void)
{
    T1CONbits.TON = 1; 
    T2CONbits.TON = 0;
}

void disableTimer(void)
{
    T1CONbits.TON = 0; 
    T2CONbits.TON = 0;
}

void timerInit(void)
{
    // timer params
    timerParams(250, &T1CON, &TMR1, &PR1); // in ms
    timerParams(10, &T2CON, &TMR2, &PR2); // in ms
    
    // interrupt params
    IPC0bits.T1IP = 2;
    IPC1bits.T2IP = 5;      // timer2 gets a higher prio then timer1
    
    IFS0bits.T1IF = 0;      // reset both flags
    IFS0bits.T2IF = 0;
    
    IEC0bits.T1IE = 1;      // enable both
    IEC0bits.T2IE = 1;
}

void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
    /* Clear Timer1 interrupt flag */
    IFS0bits.T1IF = 0;
    
    unsigned int adc_buf = SENSOR_1;
    
    char str[30];
    sprintf(str, "SENSOR_1 = %d\n", adc_buf);
    uartWrite(str);
}

void __attribute__((__interrupt__,no_auto_psv)) _T2Interrupt(void)
{
    /* Clear Timer2 interrupt flag */
    IFS0bits.T2IF = 0;
    
}