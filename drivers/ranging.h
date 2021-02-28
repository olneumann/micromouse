/*
 * File:   ranging.h
 * Author: oliver
 *
 * Created on 2. Januar 2021, 17:00
 */

#ifndef RANGING_H
#define	RANGING_H

#include "vl53l0x/vl53l0x_api.h"

float getRangeLeft(void);
float getRangeFront(void);
float getRangeRight(void);

VL53L0X_Error rangingInit(uint16_t kfscl);
VL53L0X_Error enableRanging(void);
VL53L0X_Error disableRanging(void);

#endif /* RANGING_H */