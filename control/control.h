/*
 * File:   control.h
 * Author: oliver
 *
 * Created on 12. March 2021, 18:10
 */
 
#ifndef CONTROL_H
#define	CONTROL_H

#include <stdbool.h>

void toggleMotorControl(bool state);
void toggleSideControl(bool state);
void toggleFrontControl(bool state);
void toggleTurnControl(bool state);

float getInput(int ctrl);
float getSetpoint(int ctrl);

void setSpeedLimit(float speed_ms);
float getSpeedLimit(void);

void setSetpointLinearVelocity(float speed_ms);
void setSetpointAngularVelocity(float speed_ms);
void setSetpointTurnAngle(float angle, float speed_ms);
void setSetpointDeltaSide(float delta);
void setSetpointFrontDistance(float distance);

void updateSlidingSetpointVelocity(void);
void resetSlidingSetpointVelocity(void);
void motorControl(void);

#ifdef CONTROL_DEBUG
float getInput(int ctrl);
void setSetpoint(int ctrl, float val);
static inline float convDC(float pidsum, int ctrl);
#endif

#endif	/* CONTROL_H */

