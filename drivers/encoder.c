/*
 * File:   encoder.c
 * Author: oliver
 *
 * Created on 4. Dezember 2020, 18:03
 */

#include <stdint.h>
#include <math.h>

#include "motor.h"

#include "xc.h"
#include "encoder.h"

#define PULSES_PER_REV      16*33 
#define CNT_INC_PER_REV     4
#define MAX_CNT_PER_REV     (PULSES_PER_REV*CNT_INC_PER_REV-1)

long rotCnt1;
long rotCnt2;

double getAngle1(void)
{
    static long hist_poscnt[2] = {0,0};
    hist_poscnt[1] = hist_poscnt[0];
    hist_poscnt[0] = POS1CNT + rotCnt1;

    double dAng = (double)(hist_poscnt[0] % MAX_CNT_PER_REV) / MAX_CNT_PER_REV;
    
    return dAng;
}

double getAngle2(void)
{
    static long hist_poscnt[2] = {0,0};
    hist_poscnt[1] = hist_poscnt[0];
    hist_poscnt[0] = POS2CNT + rotCnt2;

    double dAng = (double)(hist_poscnt[0] % MAX_CNT_PER_REV) / MAX_CNT_PER_REV;
    
    return dAng;
}

direction getDir1(void)
{
    direction dir = POS;
    if (QEI1CONbits.UPDN == 1)
    {
        dir = POS;
    }
    else if (QEI1CONbits.UPDN == 0)
    {
        dir = NEG;
    }
    return M1_dir*dir;
}

direction getDir2(void)
{
    direction dir = POS;
    if (QEI2CONbits.UPDN == 1)
    {
        dir = POS;
    }
    else if (QEI2CONbits.UPDN == 0)
    {
        dir = NEG;
    }
    return M2_dir*dir;
}

void qeiInit(uint16_t init_poscnt)
{         
    QEI1CONbits.QEISIDL = 0;        // Discontinue module operation when device enters Idle mode
    QEI2CONbits.QEISIDL = 0; 
    QEI1CONbits.QEIM = 0b111;       // Quadrature Encoder Interface enabled (x4 mode) with position counter reset by match (MAXxCNT)
    QEI2CONbits.QEIM = 0b111;
    QEI1CONbits.SWPAB = 0;          // Phase A and Phase B inputs not swapped
    QEI2CONbits.SWPAB = 0;
    
    MAX1CNT = MAX_CNT_PER_REV;
    MAX2CNT = MAX_CNT_PER_REV;
    POS1CNT = init_poscnt;
    POS2CNT = init_poscnt;
    rotCnt1 = 0;
    rotCnt2 = 0;
    
    IFS3bits.QEI1IF = 0;
    IEC3bits.QEI1IE = 1;            // Enable QEI1 interrupt
    IPC14bits.QEI1IP = 5;
    
    IFS4bits.QEI2IF = 0;
    IEC4bits.QEI2IE = 1;            // Enable QEI2 interrupt
    IPC18bits.QEI2IP = 5;
}

void __attribute__((__interrupt__, no_auto_psv)) _QEI1Interrupt(void)
{
    /* Clear QEI1IF interrupt flag */
    IFS3bits.QEI1IF = 0;
    
    if (POS1CNT < MAX1CNT>>1)
    {
        rotCnt1 += (long) 0x10000;    // positive roll-over
    }
    else
    {
        rotCnt1 -= (long) 0x10000;    // negative roll-over
    }
}

void __attribute__((__interrupt__, no_auto_psv)) _QEI2Interrupt(void)
{
    /* Clear QEI2IF interrupt flag */
    IFS4bits.QEI2IF = 0;
    
    if (POS2CNT < MAX2CNT>>1)
    {
        rotCnt2 += (long) 0x10000;    // positive roll-over
    }
    else
    {
        rotCnt2 -= (long) 0x10000;    // negative roll-over
    }
}
