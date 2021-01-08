/*
 * File:   control.h
 * Author: oliver
 *
 * Created on 2. Januar 2021, 10:39
 */

#ifndef PID_H
#define PID_H

#include <stdint.h>
#include <stddef.h>

#include "../common/defines.h"

typedef enum {
    PID_L_MOTOR,
    PID_R_MOTOR,
    PID_ITEM_COUNT
} pidIndex_e;

typedef struct pidf_s {
    uint8_t P;
    uint8_t I;
    uint8_t D;
    uint16_t F;
} pidf_t;

typedef struct pidCoefficient_s {
    float Kp;
    float Ki;
    float Kd;
    float Kf;
} pidCoefficient_t;

typedef struct pidProfile_s {
    pidf_t pid[PID_ITEM_COUNT];
} pidProfile_t;

typedef struct pidRuntime_s {
    float dT;
    float pidFreq;
    float iLim;
    float prevPidSetpoint[PID_ITEM_COUNT];
    float prevPidInput[PID_ITEM_COUNT];
    pidCoefficient_t pidCoef[PID_ITEM_COUNT];
} pidRuntime_t;

typedef struct pidMotorData_s {
    float P;
    float I;
    float D;
    float F;
    float Sum;
} pidMotorData_t;

extern pidRuntime_t pidRuntime;
extern pidMotorData_t pidData[PID_ITEM_COUNT];

void pidProfileInit();
void pidInit(uint32_t pidLooptime);
void pidController(timeUs_t currentTimeUs);

#endif	/* PID_H */