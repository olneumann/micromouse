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

#include "control.h"

#ifdef CONTROL_DEBUG
#include "../drivers/serial_uart.h"
#include <math.h>
#endif

static volatile float SETPOINT[PID_ITEM_COUNT];
static volatile bool MOTOR_CONTROL  = true;
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

float convDC(float pidsum, int ctrl)
{
    return (SETPOINT[ctrl] + pidsum)/MAX_SPEED_MS;  
}

void motorControl(void)
{
    pidController();
    
    float controlLeft;
    float controlRight;
    
    controlLeft = MOTOR_CONTROL * pidData[PID_VELO_MOTOR_LEFT].Sum
                + SIDE_CONTROL  * pidData[PID_DIST_SENSOR_SIDE].Sum
                - FRONT_CONTROL * pidData[PID_DIST_SENSOR_FRONT].Sum;
    
    controlRight = MOTOR_CONTROL * pidData[PID_VELO_MOTOR_RIGHT].Sum
                 - SIDE_CONTROL  * pidData[PID_DIST_SENSOR_SIDE].Sum
                 - FRONT_CONTROL * pidData[PID_DIST_SENSOR_FRONT].Sum;
    
    driveLeft(convDC(controlLeft, 0));
    driveRight(convDC(controlRight, 1)); 
}