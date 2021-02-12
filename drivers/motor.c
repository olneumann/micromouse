/*
 * File:   motor.c
 * Author: oliver
 *
 * Created on 5. Dezember 2020, 15:47
 */

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "../dspic/board.h"

#include "motor.h"

void pwmParams(int pwm_freq_hz, volatile uint16_t* pTCON, volatile uint16_t* pPiTPER)
{
    long double ticks = FCY / pwm_freq_hz; 
    int iTCKPS[4] = {1,4,16,64};                    // (00 | 01 | 10 | 11)
    char maskTCKPS[4] = {0x00,0x4,0x8,0x12};        // mask for setting 2 bits (xxxx.xxxx xxxx.--xx)
    int i = 0;

    do {
        long double dPR = ticks/iTCKPS[i];
        if (dPR <= 32767)                           // 15bit register
        {
            *pPiTPER = (uint16_t)dPR - 1;           // set PiTPER register
            *pTCON |= maskTCKPS[i];                 // set prescaler
            break;
        }
        i++;
    } while(i < 4); 
}

void setDC(double DC, volatile uint16_t* pPxDCy, uint16_t PxTPER)
{
    double dPxDCy = DC * (double)(PxTPER<<1); // times 2, 'cause shift in register   
    *pPxDCy = (uint16_t)dPxDCy;
}

void motorInit(void) 
{
    /*
     Setup of main (PWM1L|Hx) motor pwm generator, each motor uses one (duty cycle) channel
     */
    P1TCONbits.PTEN = 0;                        // PWM Time Base Timer Disable 
    pwmParams(1000, &P1TCON, &P1TPER);          // [Hz] Possible Range: [15Hz; 26.6MHz]
    PWM1CON1bits.PMOD1 = 1;                     // PWM I/O pin pair is in Independent Output mode
    PWM1CON1bits.PMOD2 = 1;
    
    PWM1CON1bits.PEN1H = 1;                     // PWMxHy I/O Enable bits
    PWM1CON1bits.PEN2H = 1;                   
    PWM1CON1bits.PEN1L = 1;                     
    PWM1CON1bits.PEN2L = 1;
    
    P1TCONbits.PTEN = 1;                        // PWM Time Base Timer Enable 
    P1DC1 = 0;                                  // PWM Duty Cycle 1 Value
    P1DC2 = 0;                                  // PWM Duty Cycle 2 Value
}

/* -- Motor 1 --
 * PH/PWM mode
 PH -| (0|1) -> PIN: PWM1L1 
 PWM-| (PWM) -> PIN: PWM1H1 
 */
void driveM1(double percent)
{
    if (percent > 0) 
    {
        /* -- Forward --
         * PH:  1 (static)
         * PWM: 1
         */  
        P1OVDCONbits.POVD1L = 0;                
        P1OVDCONbits.POUT1L = 1;                // PH -> static (high)
        P1OVDCONbits.POVD1H = 1;                // PWM -> PWM
        setDC(fabs(percent), &P1DC1, P1TPER);
    }
    else if (percent < 0)
    {
        /* -- Backward --
         * PH:  0 (static)
         * PWM: 1
         */  
        P1OVDCONbits.POVD1L = 0;                
        P1OVDCONbits.POUT1L = 0;                // PH -> static (low)
        P1OVDCONbits.POVD1H = 1;                // PWM -> PWM
        setDC(fabs(percent), &P1DC1, P1TPER);
    }
    else if (percent == 0)
    {
        /* -- Brake (slow decay) --
         * PH:  0|1 (static)
         * PWM: 0
         */  
        P1OVDCONbits.POVD1L = 0;                
        P1OVDCONbits.POUT1L = 0;                // PH -> static (low)
        P1OVDCONbits.POVD1H = 0;                
        P1OVDCONbits.POUT1H = 0;                // PWM -> static (low)
    }
    else
    {
        // n.def.
    } 
}

/* -- Motor 2 --
 * PH/PWM mode
 PH -| (0|1) -> PIN: PWM1L2
 PWM-| (PWM) -> PIN: PWM1H2 
 */
void driveM2(double percent)
{
    if (percent > 0) 
    {
        /* -- Forward --
         * PH:  1 (static)
         * PWM: 1
         */  
        P1OVDCONbits.POVD2L = 0;                
        P1OVDCONbits.POUT2L = 1;                // PH -> static (high)
        P1OVDCONbits.POVD2H = 1;                // PWM -> PWM
        setDC(fabs(percent), &P1DC2, P1TPER);
    }
    else if (percent < 0)
    {
        /* -- Backward --
         * PH:  0 (static)
         * PWM: 1
         */  
        P1OVDCONbits.POVD2L = 0;                
        P1OVDCONbits.POUT2L = 0;                // PH -> static (low)
        P1OVDCONbits.POVD2H = 1;                // PWM -> PWM
        setDC(fabs(percent), &P1DC2, P1TPER);
    }
    else if (percent == 0)
    {
        /* -- Brake (slow decay) --
         * PH:  0|1 (static)
         * PWM: 0
         */  
        P1OVDCONbits.POVD2L = 0;                
        P1OVDCONbits.POUT2L = 0;                // PH -> static (low)
        P1OVDCONbits.POVD2H = 0;                
        P1OVDCONbits.POUT2H = 0;                // PWM -> static (low)
    }
    else
    {
        // n.def.
    } 
}