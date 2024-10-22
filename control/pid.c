/*
 * File:   control.c
 * Author: oliver
 *
 * Created on 2. Januar 2021, 10:39
 */

#include <stdint.h>
#include <stddef.h>

#include "../drivers/motor.h"
#include "../common/defines.h"
#include "../common/maths.h"
#include "../control/control.h"
#include "../control/primitives.h"

#include "pid.h"

pidRuntime_t pidRuntime;
pidProfile_t pidProfile;
pidData_t pidData[PID_ITEM_COUNT];

void pidProfileInit()
{
    pidProfile.pid[PID_VELO_MOTOR_LEFT]     = (pidf_t) { .017, .004, .07, 0 }; 
    pidProfile.pid[PID_VELO_MOTOR_RIGHT]    = (pidf_t) { .017, .004, .07, 0 };
    pidProfile.pid[PID_DIST_SENSOR_SIDE]    = (pidf_t) { .005, .0005, .001, 0 };
    pidProfile.pid[PID_DIST_SENSOR_FRONT]   = (pidf_t) { .02, .001, .01, 0 };
    pidProfile.pid[PID_ROBOT_TURN_ANGLE]    = (pidf_t) { .01, .001, .01, 0 };
}

void pidInit(uint16_t pidLooptime) 
{
    pidRuntime.dT = pidLooptime;
    pidRuntime.pidFreq = 1.0f / pidRuntime.dT;
    pidRuntime.iLim = 0.01f;
   
    for (int ctrl = 0; ctrl < PID_ITEM_COUNT; ctrl++)
    {
        pidRuntime.prevPidSetpoint[ctrl] = 0.0f;
        pidRuntime.pidCoef[ctrl].Kp = pidProfile.pid[ctrl].P;
        pidRuntime.pidCoef[ctrl].Ki = pidProfile.pid[ctrl].I;
        pidRuntime.pidCoef[ctrl].Kd = pidProfile.pid[ctrl].D;
        pidRuntime.pidCoef[ctrl].Kf = pidProfile.pid[ctrl].F;
        pidRuntime.outMin[ctrl] = -MAX_SPEED_MS;
        pidRuntime.outMax[ctrl] =  MAX_SPEED_MS;
    }
}

void pidController(void)
{    
    static float PidSetpoint[PID_ITEM_COUNT];
    static float PidInput[PID_ITEM_COUNT];
    
    for (int ctrl = 0; ctrl < PID_ITEM_COUNT; ctrl++)
    {
        PidSetpoint[ctrl]   = getSetpoint(ctrl); 
        PidInput[ctrl]      = getInput(ctrl);
        
        // Proportional component
        float errRate = PidSetpoint[ctrl] - PidInput[ctrl];
        pidData[ctrl].P = pidRuntime.pidCoef[ctrl].Kp * errRate;
        
        // Integral component (with windup protection & stable integral term)
        const float prevI = 0.0f; //pidData[ctrl].I;
        pidData[ctrl].I = constrainf(prevI + pidRuntime.pidCoef[ctrl].Ki * errRate * pidRuntime.dT,
                                     -pidRuntime.iLim,
                                     pidRuntime.iLim);
        
        // Differential component (avoid derivative kick)
        float deltaPidSetpoint = 0.0f;
        deltaPidSetpoint = PidSetpoint[ctrl] - pidRuntime.prevPidSetpoint[ctrl];
        
        pidData[ctrl].D = pidRuntime.pidCoef[ctrl].Kd * (-deltaPidSetpoint) * pidRuntime.pidFreq; 
        pidRuntime.prevPidInput[ctrl] = PidInput[ctrl];
        
        // Feedforward component (setpoint weighting)
        pidRuntime.prevPidSetpoint[ctrl] = PidSetpoint[ctrl];
        pidData[ctrl].F = pidRuntime.pidCoef[ctrl].Kf * deltaPidSetpoint * pidRuntime.pidFreq;
        
        const float pidSum = pidData[ctrl].P 
                           + pidData[ctrl].I
                           + pidData[ctrl].D
                           + pidData[ctrl].F;
        
        // Output windup protection
        pidData[ctrl].Sum = constrainf(pidSum, pidRuntime.outMin[ctrl], pidRuntime.outMax[ctrl]);   
    }
}