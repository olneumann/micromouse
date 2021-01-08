/*
 * File:   core.h
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */

#ifndef CORE_H
#define CORE_H

#include "../common/defines.h"

void taskGyroSample(timeUs_t currentTimeUs);
bool gyroFilterReady(void);

void taskMainPidLoop(timeUs_t currentTimeUs);
bool pidLoopReady(void);

#endif	/* CORE_H */

