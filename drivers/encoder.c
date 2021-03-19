/*
 * File:   encoder.c
 * Author: oliver
 *
 * Created on 4. Dezember 2020, 18:03
 */

#include <stdint.h>
#include <math.h>

#include "../common/maths.h"
#include "../dspic/board.h"
#include "../drivers/motor.h"

#include "encoder.h"

#define PERIMETER_WHEEL_UM  (uint32_t)188496
#define PULSES_PER_REV      16*33 
#define CNT_INC_PER_REV     4
#define MAX_CNT_PER_REV     (uint16_t)(PULSES_PER_REV*CNT_INC_PER_REV-1)
#define UM_PER_CNT          (float)(PERIMETER_WHEEL_UM/MAX_CNT_PER_REV)

static volatile int32_t DISTANCE_UM_L;      // overflow in 2,147 km
static volatile int32_t DISTANCE_UM_R;      // binary drift (loop closure?)

static volatile int16_t ANGLE_TICK_L;
static volatile int16_t ANGLE_TICK_R;

static volatile int16_t DIFF_CNT_L;
static volatile int16_t DIFF_CNT_R;

static volatile float VELOCITY_L;
static volatile float VELOCITY_R;

int32_t getDistanceLeft(void)
{
    return DISTANCE_UM_L;
}

int32_t getDistanceRight(void)
{
    return DISTANCE_UM_R;
}

int32_t getDistance(void)
{
    return (int32_t)(0.5f * (DISTANCE_UM_L + DISTANCE_UM_R));
}

float getLinearVelocityLeft(void)
{  
    return VELOCITY_L;
}

float getLinearVelocityRight(void)
{
    return VELOCITY_R;
}

float getLinearVelocity(void)
{
    return 0.5f * (VELOCITY_L + VELOCITY_R);
}

int16_t getAngleTickLeft(void)
{
    return ANGLE_TICK_L;
}

int16_t getAngleTickRight(void)
{
    return ANGLE_TICK_R;
}

void resetAngleTick(void)
{
    ANGLE_TICK_L = 0;
    ANGLE_TICK_R = 0;
}

int16_t getAngleDiffTick(void)
{
    return ANGLE_TICK_L - ANGLE_TICK_R;
}

float ticksToAngle(int16_t ticks)
{
    return (float)ticks/MAX_CNT_PER_REV * 360.0f;
}

float getAngle(void)
{
    return ticksToAngle(getAngleDiffTick());
}

int16_t getCounterDiff(uint16_t now, uint16_t prev)
{
    int16_t diff = now - prev;
    
    if (diff >= 0)
    {
        if (diff >= (int16_t)MAX_CNT_PER_REV/2)
            diff -= MAX_CNT_PER_REV;
    }
    else
    {
        if (diff < -(int16_t)MAX_CNT_PER_REV/2)
            diff += MAX_CNT_PER_REV;
    }
    return diff;
}

void updateEncoderReadings(uint16_t freq)
{
    static uint16_t prev_cnt_l = 0;
    static uint16_t prev_cnt_r = 0;
    
    uint16_t cnt_l = POS2CNT;           // motor left
    uint16_t cnt_r = POS1CNT;           // motor right
   
    DIFF_CNT_L = getCounterDiff(cnt_l, prev_cnt_l);
    DIFF_CNT_R = getCounterDiff(cnt_r, prev_cnt_r);

    DISTANCE_UM_L += (int32_t)(DIFF_CNT_L * UM_PER_CNT);
    DISTANCE_UM_R += (int32_t)(DIFF_CNT_R * UM_PER_CNT);
    
    ANGLE_TICK_L += DIFF_CNT_L;
    ANGLE_TICK_R += DIFF_CNT_R;
    
    VELOCITY_L = DIFF_CNT_L * (UM_PER_CNT * 1e-6) * freq;
    VELOCITY_R = DIFF_CNT_R * (UM_PER_CNT * 1e-6) * freq;
        
    if (prev_cnt_l != cnt_l) prev_cnt_l = cnt_l;
    if (prev_cnt_r != cnt_r) prev_cnt_r = cnt_r;
}

void qeiInit(void)
{         
    QEI1CONbits.QEISIDL = 0;        // Discontinue module operation when device enters Idle mode
    QEI2CONbits.QEISIDL = 0; 
    QEI1CONbits.QEIM = 0b111;       // Quadrature Encoder Interface enabled (x4 mode) with position counter reset by match (MAXxCNT)
    QEI2CONbits.QEIM = 0b111;
    QEI1CONbits.SWPAB = 1;          // Phase A and Phase B inputs not swapped
    QEI2CONbits.SWPAB = 0;
    
    MAX1CNT = MAX_CNT_PER_REV;  
    MAX2CNT = MAX_CNT_PER_REV;
    POS1CNT = 0;
    POS2CNT = 0;
    
    /* 
     * QEI ISR: 
     * - Reset of counters?
     */
    
    IFS3bits.QEI1IF = 0;
    IEC3bits.QEI1IE = 0;           
    IPC14bits.QEI1IP = 5;
    
    IFS4bits.QEI2IF = 0;
    IEC4bits.QEI2IE = 0;            
    IPC18bits.QEI2IP = 5;
}

void __attribute__((__interrupt__, no_auto_psv)) _QEI1Interrupt(void)
{
    /* Clear QEI1IF interrupt flag */
    IFS3bits.QEI1IF = 0;
    
}

void __attribute__((__interrupt__, no_auto_psv)) _QEI2Interrupt(void)
{
    /* Clear QEI2IF interrupt flag */
    IFS4bits.QEI2IF = 0;
    
}
