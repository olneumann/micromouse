/*
 * File:   init.h
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */

#ifndef TASKS_H
#define	TASKS_H

#include <stdint.h>
#include "../dspic/board.h"

void taskTest(void);

void taskEncoder(uint16_t freq);
void taskRanging(uint16_t freq);
void taskControl(uint16_t freq);
void taskDiscovery(void);
void taskInference(void);

#ifdef PRIMITIVES_DEBUG
extern bool runFlag;
#endif

#endif	/* TASKS_H */