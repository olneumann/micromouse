/*
 * File:   init.h
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */

#ifndef TASKS_H
#define	TASKS_H

#include <stdint.h>

void taskTest(void);

void taskEncoder(uint16_t freq);
void taskRanging(uint16_t freq);
void taskControl(uint16_t freq);

#endif	/* TASKS_H */