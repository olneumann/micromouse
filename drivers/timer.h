/* 
 * File:   timer.h
 * Author: oliver
 *
 * Created on 20. November 2020, 16:45
 */

#ifndef TIMER_H
#define	TIMER_H

#include <stdint.h>
#include <stddef.h>

#include "../common/defines.h"

void enableTimer(void);
void disableTimer(void);
void timerInit(void);      

#endif	/* TIMER_H */

