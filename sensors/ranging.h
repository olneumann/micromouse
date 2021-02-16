/*
 * File:   ranging.h
 * Author: oliver
 *
 * Created on 2. Januar 2021, 17:00
 */

#ifndef RANGING_H
#define	RANGING_H

#include "../drivers/ranging/vl53l0x_api.h"

extern uint16_t RANGE_SENSOR_L[4];
extern uint16_t RANGE_SENSOR_F[4];
extern uint16_t RANGE_SENSOR_R[4];

VL53L0X_Error rangingInit(void);

#endif /* RANGING_H */