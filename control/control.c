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

#define MAX_DELTA_SIDE      42.0f // in mm

static volatile float SETPOINT[PID_ITEM_COUNT];
static volatile float SLIDING_SETPOINT_VELO_L, SLIDING_SETPOINT_VELO_R;
static volatile float SPEED_LIMIT   = 0.2f * MAX_SPEED_MS;

static volatile bool MOTOR_CONTROL  = false;
static volatile bool SIDE_CONTROL   = false;
static volatile bool FRONT_CONTROL  = false;
static volatile bool TURN_CONTROL   = false;

void setSpeedLimit(float speed_ms)
{
    SPEED_LIMIT = speed_ms;
}

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

void setSetpointDeltaSide(float delta)
{
    SETPOINT[PID_DIST_SENSOR_SIDE] = delta;
}

void updateSetpointVelocity(void)
{       
    float errSide = (float)SIDE_CONTROL * pidData[PID_DIST_SENSOR_SIDE].Sum;
    float errTurn = (float)TURN_CONTROL * pidData[PID_ROBOT_TURN_ANGLE].Sum;
    float errFront = (float)FRONT_CONTROL * pidData[PID_DIST_SENSOR_FRONT].Sum;
    float idealSetpointLeft  = getSetpoint(PID_VELO_MOTOR_LEFT);
    float idealSetpointRight = getSetpoint(PID_VELO_MOTOR_RIGHT);
    
    // Limit output of secondary control loops
    if (SIDE_CONTROL)
    {
        pidRuntime.outMin[PID_DIST_SENSOR_SIDE] = -SPEED_LIMIT;
        pidRuntime.outMax[PID_DIST_SENSOR_SIDE] =  SPEED_LIMIT;
    }
    if (FRONT_CONTROL)
    {
        pidRuntime.outMin[PID_DIST_SENSOR_FRONT] = -SPEED_LIMIT;
        pidRuntime.outMax[PID_DIST_SENSOR_FRONT] =  SPEED_LIMIT;
    }
    if (TURN_CONTROL)
    {
        pidRuntime.outMin[PID_ROBOT_TURN_ANGLE] = -SPEED_LIMIT;
        pidRuntime.outMax[PID_ROBOT_TURN_ANGLE] =  SPEED_LIMIT;
    }
    
    // Adapt side control of jump in measurement (over threshold)
    if (SIDE_CONTROL && fabs(getInput(PID_DIST_SENSOR_SIDE)) > MAX_DELTA_SIDE) errSide = 0.0f;

    // Adjust each setpoint velocity to compensate wall distance and allow turning
    SLIDING_SETPOINT_VELO_L = constrainf(idealSetpointLeft - errSide + errTurn + errFront,
                                         -SPEED_LIMIT,
                                          SPEED_LIMIT);
    SLIDING_SETPOINT_VELO_R = constrainf(idealSetpointRight + errSide - errTurn + errFront,
                                         -SPEED_LIMIT,
                                          SPEED_LIMIT);
}

float convDC(float velocity)
{
    return velocity/MAX_SPEED_MS;
}

void motorControl(void)
{
    pidController();

    float controlLeft  = SLIDING_SETPOINT_VELO_L 
                       + (float)MOTOR_CONTROL * pidData[PID_VELO_MOTOR_LEFT].Sum;
    float controlRight = SLIDING_SETPOINT_VELO_R
                       + (float)MOTOR_CONTROL * pidData[PID_VELO_MOTOR_RIGHT].Sum;
    
    driveLeft(convDC(controlLeft));
    driveRight(convDC(controlRight)); 
}