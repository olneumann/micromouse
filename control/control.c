/*
 * File:   control.c
 * Author: oliver
 *
 * Created on 12. March 2021, 18:10
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#include "../common/maths.h"
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
static volatile bool TURN_CONTROL   = false;

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

void toggleTurnControl(bool state)
{
    resetAngleTick();    
    TURN_CONTROL = state;
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
        return getLinearVelocityLeft();
    }
    else if (ctrl == PID_VELO_MOTOR_RIGHT)
    {
        return getLinearVelocityRight();
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
    else if (ctrl == PID_ROBOT_TURN_ANGLE)
    {
        return getDiffAngle();
    }
    
    return 0.0f;
}

void setSetpointLinearVelocity(float speed_ms)
{
    SETPOINT[PID_VELO_MOTOR_LEFT] = speed_ms;
    SETPOINT[PID_VELO_MOTOR_RIGHT] = speed_ms;
}

float getAbsSetpointLinearVelocity(void)
{
    return 0.5f * (fabs(SETPOINT[PID_VELO_MOTOR_LEFT]) + fabs(SETPOINT[PID_VELO_MOTOR_RIGHT]));
}

void setSetpointAngularVelocity(float speed_ms)
{
    SETPOINT[PID_VELO_MOTOR_LEFT] = speed_ms;       // pos. speed_ms cw. turn
    SETPOINT[PID_VELO_MOTOR_RIGHT] = -speed_ms;
}

void setSetpointTurnAngle(float angle, float speed_ms)
{
    SETPOINT[PID_ROBOT_TURN_ANGLE] = angle;
    SETPOINT[PID_VELO_MOTOR_LEFT] = speed_ms;       // pos. speed_ms cw. turn
    SETPOINT[PID_VELO_MOTOR_RIGHT] = -speed_ms;
    
}

void updateSetpointVelocity(void)
{    
    float commandSetpointLeft, commandSetpointRight;
    float errSide = (float)SIDE_CONTROL * pidData[PID_DIST_SENSOR_SIDE].Sum;
    float errTurn = (float)TURN_CONTROL * pidData[PID_ROBOT_TURN_ANGLE].Sum;
    float prevSetpointLeft = getSetpoint(PID_VELO_MOTOR_LEFT);
    float prevSetpointRight = getSetpoint(PID_VELO_MOTOR_RIGHT);
    
    // Adjust each setpoint velocity to compensate wall distance and allow turning
    commandSetpointLeft  = constrainf(prevSetpointLeft + errSide + errTurn,
                                     -fabs(prevSetpointLeft),
                                      fabs(prevSetpointLeft));
    commandSetpointRight = constrainf(prevSetpointRight - errSide - errTurn,
                                     -fabs(prevSetpointRight),
                                      fabs(prevSetpointRight));
    
    setSetpoint(PID_VELO_MOTOR_LEFT, commandSetpointLeft);
    setSetpoint(PID_VELO_MOTOR_RIGHT, commandSetpointRight);
}

float convDC(float velocity)
{
    return velocity/MAX_SPEED_MS;
}

void motorControl(void)
{
    // Limit output of secondary control loops based on the linear velocity setpoint
    if (SIDE_CONTROL)
    {
        pidRuntime.outMin[PID_DIST_SENSOR_SIDE] = -getAbsSetpointLinearVelocity();
        pidRuntime.outMax[PID_DIST_SENSOR_SIDE] =  getAbsSetpointLinearVelocity();
    }
    if (FRONT_CONTROL)
    {
        pidRuntime.outMin[PID_DIST_SENSOR_FRONT] = -getAbsSetpointLinearVelocity();
        pidRuntime.outMax[PID_DIST_SENSOR_FRONT] =  getAbsSetpointLinearVelocity();
    }
    if (TURN_CONTROL)
    {
        pidRuntime.outMin[PID_ROBOT_TURN_ANGLE] = -getAbsSetpointLinearVelocity();
        pidRuntime.outMax[PID_ROBOT_TURN_ANGLE] =  getAbsSetpointLinearVelocity();
    }
    
    pidController();
    updateSetpointVelocity();
    
    float controlLeft;
    float controlRight;
    
    controlLeft     = getSetpoint(PID_VELO_MOTOR_LEFT) 
                    + (float)MOTOR_CONTROL * pidData[PID_VELO_MOTOR_LEFT].Sum;
    controlRight    = getSetpoint(PID_VELO_MOTOR_RIGHT)
                    + (float)MOTOR_CONTROL * pidData[PID_VELO_MOTOR_RIGHT].Sum;
    
    driveLeft(convDC(controlLeft));
    driveRight(convDC(controlRight)); 
}