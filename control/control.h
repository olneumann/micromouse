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

float getInput(int ctrl);
float getSetpoint(int ctrl);

void setSetpointLinearVelocity(float speed_ms);
void setSetpointAngularVelocity(float speed_ms);
void motorControl(void);

#ifdef CONTROL_DEBUG
void setSetpoint(int ctrl, float val);
float convDC(float pidsum, int ctrl);
#endif

#endif	/* CONTROL_H */

