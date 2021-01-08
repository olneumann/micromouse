/*
 * File:   init.h
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */

#ifndef TASKS_H
#define	TASKS_H

#include "../scheduler/scheduler.h"

void tasksInit(void);
task_t *getTask(unsigned taskId);

#endif	/* TASKS_H */

