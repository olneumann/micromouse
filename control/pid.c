/*
 * File:   control.c
 * Author: oliver
 *
 * Created on 2. Januar 2021, 10:39
 */

#include <stdint.h>
#include <stddef.h>

#include "../common/defines.h"
#include "../common/maths.h"
#include "../control/primitives.h"

#include "pid.h"

pidRuntime_t pidRuntime;
pidProfile_t pidProfile;
pidMotorData_t pidData[PID_ITEM_COUNT];

void pidProfileInit()
{
    pidProfile.pid[PID_L_MOTOR] = (pidf_t) { 42, 42, 42, 42 };
    pidProfile.pid[PID_R_MOTOR] = (pidf_t) { 42, 42, 42, 42 };
}

void pidInit(uint32_t pidLooptime) 
{
    pidRuntime.dT = pidLooptime;
    pidRuntime.pidFreq = 1.0f / pidRuntime.dT;
    pidRuntime.iLim = 42;
    pidRuntime.prevPidSetpoint[PID_ITEM_COUNT] = 0.0f;
    
    for (int ctrl = 0; ctrl < PID_ITEM_COUNT; ctrl++)
    {
        pidRuntime.pidCoef[ctrl].Kp = pidProfile.pid[ctrl].P;
        pidRuntime.pidCoef[ctrl].Ki = 1.0f * pidProfile.pid[ctrl].I;
        pidRuntime.pidCoef[ctrl].Kd = 1.0f * pidProfile.pid[ctrl].D;
        pidRuntime.pidCoef[ctrl].Kf = 1.0f * pidProfile.pid[ctrl].F;
    }
}

void pidController(timeUs_t currentTimeUs)
{    
    static float PidSetpoint[PID_ITEM_COUNT];
    static float PidInput[PID_ITEM_COUNT];
    
    for (int ctrl = 0; ctrl < PID_ITEM_COUNT; ctrl++)
    {
        PidSetpoint[ctrl] = get_desired_val(ctrl);
        PidInput[ctrl] = get_input_val(ctrl);
        
        // Proportional component
        float errRate = PidSetpoint[ctrl] - PidInput[ctrl];
        pidData[ctrl].P = pidRuntime.pidCoef[ctrl].Kp * errRate;
        
        // Integral component (with windup protection)
        pidData[ctrl].I = constrainf(pidRuntime.pidCoef[ctrl].Ki * errRate * pidRuntime.dT,
                                     -pidRuntime.iLim,
                                     pidRuntime.iLim);
        
        // Differential component (avoid derivative kick)
        float deltaPidSetpoint = 0.0f;
        deltaPidSetpoint = PidSetpoint[ctrl] - pidRuntime.prevPidSetpoint[ctrl];
        
        pidData[ctrl].D = pidRuntime.pidCoef[ctrl].Kd * (-deltaPidSetpoint) * pidRuntime.pidFreq; 
        pidRuntime.prevPidInput[ctrl] = PidInput[ctrl];
        
        // Feedforward component
        pidRuntime.prevPidSetpoint[ctrl] = PidSetpoint[ctrl];
        pidData[ctrl].F = pidRuntime.pidCoef[ctrl].Kf * deltaPidSetpoint * pidRuntime.pidFreq;
        
        const float pidSum = pidData[ctrl].P 
                           + pidData[ctrl].I
                           + pidData[ctrl].D
                           + pidData[ctrl].F;
        pidData[ctrl].Sum = pidSum;
    }
}