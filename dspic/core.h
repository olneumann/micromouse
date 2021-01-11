/*
 * File:   core.h
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */

#ifndef CORE_H
#define CORE_H

#include "../common/defines.h"

void taskEncoder(void);
void taskPIDLoop(timeUs_t currentTimeUs);

#endif	/* CORE_H */

