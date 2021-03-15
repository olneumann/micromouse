/*
 * File:   control.c
 * Author: oliver
 *
 * Created on 12. March 2021, 18:10
 */

#include <stdint.h>
#include <stddef.h>

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

void getFrontSensorError(void)
{
    
}

void getSideSensorError(void)
{
    
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
        
    }
    else if (ctrl == PID_DIST_SENSOR_FRONT)
    {
        
    }
    
    return 0.0f;
}

float convSpeedtoDC(float pidsum, int ctrl)
{
    return (SETPOINT[ctrl] + pidsum)/MAX_SPEED_MS;
    
}

void motorControl(void)
{
    pidController();
    
    float controlLeft;
    float controlRight;
    
    controlLeft = pidData[PID_VELO_MOTOR_LEFT].Sum;
               //+ pidData[PID_DIST_SENSOR_SIDE].Sum      // sign!!
               //+ pidData[PID_DIST_SENSOR_FRONT].Sum;
    
    controlRight = pidData[PID_VELO_MOTOR_RIGHT].Sum;
                //+ pidData[PID_DIST_SENSOR_SIDE].Sum      // sign!!
                //+ pidData[PID_DIST_SENSOR_FRONT].Sum;
    
    driveLeft(convSpeedtoDC(controlLeft, 0));
    driveRight(convSpeedtoDC(controlRight, 1)); 
}