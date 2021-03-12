/*
 * File:   control.c
 * Author: oliver
 *
 * Created on 12. März 2021, 18:10
 */

#include <stdint.h>
#include <stddef.h>

#include "../drivers/motor.h"
#include "../drivers/encoder.h"
#include "../drivers/ranging.h"
#include "../control/pid.h"

#include "control.h"

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

float offsetConv(float offset)
{
    /*
     * Output has to be between -1 and 1 to control the motors.
     * 
     */
    return offset;
}

void motorControl(void)
{
    pidController();
    
    float offsetLeft;
    float offsetRight;
    
    offsetLeft = pidData[PID_VELO_MOTOR_LEFT].Sum;
               //+ pidData[PID_DIST_SENSOR_SIDE].Sum      // sign!!
               //+ pidData[PID_DIST_SENSOR_FRONT].Sum;
    
    offsetRight = pidData[PID_VELO_MOTOR_RIGHT].Sum;
                //+ pidData[PID_DIST_SENSOR_SIDE].Sum      // sign!!
                //+ pidData[PID_DIST_SENSOR_FRONT].Sum;
    
    driveLeft(offsetConv(offsetLeft));
    driveRight(offsetConv(offsetRight));   
}