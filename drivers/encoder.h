/* 
 * File:   encoder.h
 * Author: oliver
 *
 * Created on 4. Dezember 2020, 18:03
 */

#ifndef ENCODER_H
#define	ENCODER_H
 
#include <stdint.h>

float getAngle(void);
void resetAngleTick(void);

float getLinearVelocityLeft(void);
float getLinearVelocityRight(void);
float getLinearVelocity(void);

int32_t getDistanceLeft(void);
int32_t getDistanceRight(void);
int32_t getDistance(void);

void updateEncoderReadings(uint16_t freq);
void qeiInit(void);

#endif	/* ENCODER_H */

