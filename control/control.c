/*
 * File:   control.c
 * Author: oliver
 *
 * Created on 12. March 2021, 18:10
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "../drivers/motor.h"
#include "../drivers/encoder.h"
#include "../drivers/ranging.h"
#include "../control/pid.h"
#include "../control/primitives.h"

#include "control.h"

#ifdef CONTROL_DEBUG
#include "../drivers/serial_uart.h"
#include <math.h>
#endif

static volatile float SETPOINT[PID_ITEM_COUNT];
static volatile bool MOTOR_CONTROL  = false;
static volatile bool SIDE_CONTROL   = false;
static volatile bool FRONT_CONTROL  = false;

void toggleMotorControl(bool state)
{
    MOTOR_CONTROL = state;
}

void toggleSideControl(bool state)
{
    SIDE_CONTROL = state;
}

void toggleFrontControl(bool state)
{
    FRONT_CONTROL = state;
}

void setSetpoint(int ctrl, float val)
{
    SETPOINT[ctrl] = val;
}

float getSetpoint(int ctrl)
{
    return SETPOINT[ctrl];
}

float getInput(int ctrl)
{
    if (ctrl == PID_VELO_MOTOR_LEFT)
    {
        return getVelocityLeft();
    }
    else if (ctrl == PID_VELO_MOTOR_RIGHT)
    {
        return getVelocityRight();
    }
    else if (ctrl == PID_DIST_SENSOR_SIDE)
    {
        /* 
         * [D]      [L]             [R]
         * [R-L]    (+)             (-)
         * [DC-L]   (+)             (-)
         * [DC-R]   (-)             (+)
         */
        return getRangeRight() - getRangeLeft();
    }
    else if (ctrl == PID_DIST_SENSOR_FRONT)
    {
        return getRangeFront();
    }
    
    return 0.0f;
}

void setVeloSetpoint(float speed_ms)
{
    SETPOINT[PID_VELO_MOTOR_LEFT] = speed_ms;
    SETPOINT[PID_VELO_MOTOR_RIGHT] = speed_ms;
}

float getVeloSetpoint(void)
{
    return 0.5f * (SETPOINT[PID_VELO_MOTOR_LEFT] + SETPOINT[PID_VELO_MOTOR_RIGHT]);
}

float convDC(float pidsum, int ctrl)
{
    return (SETPOINT[ctrl] - pidsum)/MAX_SPEED_MS;
}

void motorControl(void)
{
    if (SIDE_CONTROL)
    {
        pidRuntime.outMin[PID_DIST_SENSOR_SIDE] = -getVeloSetpoint();
        pidRuntime.outMax[PID_DIST_SENSOR_SIDE] =  getVeloSetpoint();
    }
    if (FRONT_CONTROL)
    {
        pidRuntime.outMin[PID_DIST_SENSOR_FRONT] = -getVeloSetpoint();
        pidRuntime.outMax[PID_DIST_SENSOR_FRONT] =  getVeloSetpoint();
    }
    
    pidController();
    
    float controlLeft;
    float controlRight;
    
    controlLeft = (float)MOTOR_CONTROL * pidData[PID_VELO_MOTOR_LEFT].Sum
                + (float)SIDE_CONTROL  * pidData[PID_DIST_SENSOR_SIDE].Sum
                + (float)FRONT_CONTROL * (SETPOINT[PID_VELO_MOTOR_LEFT] + pidData[PID_DIST_SENSOR_FRONT].Sum);
    
    controlRight = (float)MOTOR_CONTROL * pidData[PID_VELO_MOTOR_RIGHT].Sum
                 - (float)SIDE_CONTROL  * pidData[PID_DIST_SENSOR_SIDE].Sum
                 + (float)FRONT_CONTROL * (SETPOINT[PID_VELO_MOTOR_RIGHT] + pidData[PID_DIST_SENSOR_FRONT].Sum);
    
    driveLeft(convDC(controlLeft, PID_VELO_MOTOR_LEFT));
    driveRight(convDC(controlRight, PID_VELO_MOTOR_RIGHT)); 
}