/*
 * File:   primitives.h
 * Author: oliver
 *
 * Created on 2. Januar 2021, 17:00
 */

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

#define MAX_SPEED_MS            0.62f
#define LIN_ACCELERATION        0.1f    // ToDo: Calibrate!

void moveForward(void);
void moveSide(void);

#endif /* PRIMITIVES_H */