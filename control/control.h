/*
 * File:   control.h
 * Author: oliver
 *
 * Created on 12. March 2021, 18:10
 */
 
#ifndef CONTROL_H
#define	CONTROL_H

#define CONTROL_DEBUG

void setSetpoint(int ctrl, float val);
float getSetpoint(int ctrl);
float getInput(int ctrl);
void motorControl(void);

#ifdef CONTROL_DEBUG
float convSpeedtoDC(float pidsum, int ctrl);
#endif

#endif	/* CONTROL_H */

