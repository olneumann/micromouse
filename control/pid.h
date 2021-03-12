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
    PID_VELO_MOTOR_LEFT,
    PID_VELO_MOTOR_RIGHT,
    PID_DIST_SENSOR_SIDE,
    PID_DIST_SENSOR_FRONT,
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
    uint16_t dT;
    float pidFreq;
    float iLim;
    float prevPidSetpoint[PID_ITEM_COUNT];
    float prevPidInput[PID_ITEM_COUNT];
    pidCoefficient_t pidCoef[PID_ITEM_COUNT];
} pidRuntime_t;

typedef struct pidData_s {
    float P;
    float I;
    float D;
    float F;
    float Sum;
} pidData_t;

extern pidRuntime_t pidRuntime;
extern pidData_t pidData[PID_ITEM_COUNT];

void pidProfileInit();
void pidInit(uint16_t pidLooptime);
void pidController(void);

#endif	/* PID_H */