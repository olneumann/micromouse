/*
 * File:   control.h
 * Author: oliver
 *
 * Created on 12. March 2021, 18:10
 */
 
#ifndef CONTROL_H
#define	CONTROL_H

#include <stdbool.h>

#define CONTROL_DEBUG

void toggleMotorControl(bool state);
void toggleSideControl(bool state);
void toggleFrontControl(bool state);
float getInput(int ctrl);
float getSetpoint(int ctrl);
void setSetpoint(int ctrl, float val);
void motorControl(void);

#ifdef CONTROL_DEBUG
float convDC(float pidsum, int ctrl);
#endif

#endif	/* CONTROL_H */

