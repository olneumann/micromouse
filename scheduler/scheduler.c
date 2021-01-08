/* 
 * File:   scheduler.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 12:11
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../common/maths.h"
#include "../dspic/tasks.h"
#include "../dspic/core.h"
#include "scheduler.h"

#define TASK_AVERAGE_EXECUTE_FALLBACK_US    30  // Default task average time if USE_TASK_STATISTICS is not defined
#define TASK_AVERAGE_EXECUTE_PADDING_US     5   // Add a little padding to the average execution time
#define SCHEDULER_DELAY_LIMIT               100

static task_t *currentTask = NULL;

static uint32_t totalWaitingTasks;
static uint32_t totalWaitingTasksSamples;

static bool calculateTaskStatistics;
uint16_t averageSystemLoadPercent = 0;

static int taskQueuePos = 0;
int taskQueueSize = 0;

static int periodCalculationBasisOffset = offsetof(task_t, lastExecutedAtUs);
static bool gyroEnabled;

task_t* taskQueueArray[TASK_COUNT + 1]; // extra item for NULL pointer at end of queue

void queueClear(void)
{
    memset(taskQueueArray, 0, sizeof(taskQueueArray));
    taskQueuePos = 0;
    taskQueueSize = 0;
}

bool queueContains(task_t *task)
{
    for (int ii = 0; ii < taskQueueSize; ++ii) {
        if (taskQueueArray[ii] == task) {
            return true;
        }
    }
    return false;
}

bool queueAdd(task_t *task)
{
    if ((taskQueueSize >= TASK_COUNT) || queueContains(task)) {
        return false;
    }
    for (int ii = 0; ii <= taskQueueSize; ++ii) {
        if (taskQueueArray[ii] == NULL || taskQueueArray[ii]->staticPriority < task->staticPriority) {
            memmove(&taskQueueArray[ii+1], &taskQueueArray[ii], sizeof(task) * (taskQueueSize - ii));
            taskQueueArray[ii] = task;
            ++taskQueueSize;
            return true;
        }
    }
    return false;
}

bool queueRemove(task_t *task)
{
    for (int ii = 0; ii < taskQueueSize; ++ii) {
        if (taskQueueArray[ii] == task) {
            memmove(&taskQueueArray[ii], &taskQueueArray[ii+1], sizeof(task) * (taskQueueSize - ii));
            --taskQueueSize;
            return true;
        }
    }
    return false;
}

/*
 * Returns first item queue or NULL if queue empty
 */
task_t *queueFirst(void)
{
    taskQueuePos = 0;
    return taskQueueArray[0]; // guaranteed to be NULL if queue is empty
}

/*
 * Returns next item in queue or NULL if at end of queue
 */
task_t *queueNext(void)
{
    return taskQueueArray[++taskQueuePos]; // guaranteed to be NULL at end of queue
}

void taskSystemLoad(timeUs_t currentTimeUs)
{
    // Calculate system load
    if (totalWaitingTasksSamples > 0) {
        averageSystemLoadPercent = 100 * totalWaitingTasks / totalWaitingTasksSamples;
        totalWaitingTasksSamples = 0;
        totalWaitingTasks = 0;
    }
}

void getTaskInfo(taskId_e taskId, taskInfo_t * taskInfo)
{
    taskInfo->isEnabled = queueContains(getTask(taskId));
    taskInfo->desiredPeriodUs = getTask(taskId)->desiredPeriodUs;
    taskInfo->staticPriority = getTask(taskId)->staticPriority;
}

void rescheduleTask(taskId_e taskId, timeDelta_t newPeriodUs)
{
    if (taskId == TASK_SELF) {
        task_t *task = currentTask;
        task->desiredPeriodUs = MAX(SCHEDULER_DELAY_LIMIT, newPeriodUs);  // Limit delay to 100us (10 kHz) to prevent scheduler clogging
    } else if (taskId < TASK_COUNT) {
        task_t *task = getTask(taskId);
        task->desiredPeriodUs = MAX(SCHEDULER_DELAY_LIMIT, newPeriodUs);  // Limit delay to 100us (10 kHz) to prevent scheduler clogging
    }
}

void setTaskEnabled(taskId_e taskId, bool enabled)
{
    if (taskId == TASK_SELF || taskId < TASK_COUNT) {
        task_t *task = taskId == TASK_SELF ? currentTask : getTask(taskId);
        if (enabled && task->taskFunc) {
            queueAdd(task);
        } else {
            queueRemove(task);
        }
    }
}

timeDelta_t getTaskDeltaTimeUs(taskId_e taskId)
{
    if (taskId == TASK_SELF) {
        return currentTask->taskLatestDeltaTimeUs;
    } else if (taskId < TASK_COUNT) {
        return getTask(taskId)->taskLatestDeltaTimeUs;
    } else {
        return 0;
    }
}

void schedulerSetCalulateTaskStatistics(bool calculateTaskStatisticsToUse)
{
    calculateTaskStatistics = calculateTaskStatisticsToUse;
}


void schedulerInit(void)
{
    calculateTaskStatistics = true;
    queueClear();
    queueAdd(getTask(TASK_SYSTEM));
}

void schedulerOptimizeRate(bool optimizeRate)
{
    periodCalculationBasisOffset = optimizeRate ? offsetof(task_t, lastDesiredAt) : offsetof(task_t, lastExecutedAtUs);
}

inline static timeUs_t getPeriodCalculationBasis(const task_t* task)
{
    if (task->staticPriority == TASK_PRIORITY_REALTIME) {
        return *(timeUs_t*)((uint8_t*)task + periodCalculationBasisOffset);
    } else {
        return task->lastExecutedAtUs;
    }
}

timeUs_t schedulerExecuteTask(task_t *selectedTask, timeUs_t currentTimeUs)
{
    timeUs_t taskExecutionTimeUs = 0;

    if (selectedTask) {
        currentTask = selectedTask;
        selectedTask->taskLatestDeltaTimeUs = cmpTimeUs(currentTimeUs, selectedTask->lastExecutedAtUs);
        selectedTask->lastExecutedAtUs = currentTimeUs;
        selectedTask->lastDesiredAt += (cmpTimeUs(currentTimeUs, selectedTask->lastDesiredAt) / selectedTask->desiredPeriodUs) * selectedTask->desiredPeriodUs;
        selectedTask->dynamicPriority = 0;
        selectedTask->taskFunc(currentTimeUs);
    }

    return taskExecutionTimeUs;
}

void scheduler(void)
{
    // Cache currentTime
    const timeUs_t schedulerStartTimeUs = micros();
    timeUs_t currentTimeUs = schedulerStartTimeUs;
    timeUs_t taskExecutionTimeUs = 0;
    task_t *selectedTask = NULL;
    uint16_t selectedTaskDynamicPriority = 0;
    uint16_t waitingTasks = 0;
    bool realtimeTaskRan = false;
    timeDelta_t gyroTaskDelayUs = 0;

    if (gyroEnabled) {
        // Realtime gyro/filtering/PID tasks get complete priority
        task_t *gyroTask = getTask(TASK_GYRO);
        const timeUs_t gyroExecuteTimeUs = getPeriodCalculationBasis(gyroTask) + gyroTask->desiredPeriodUs;
        gyroTaskDelayUs = cmpTimeUs(gyroExecuteTimeUs, currentTimeUs);  // time until the next expected gyro sample
        if (cmpTimeUs(currentTimeUs, gyroExecuteTimeUs) >= 0) {
            taskExecutionTimeUs = schedulerExecuteTask(gyroTask, currentTimeUs);
            if (gyroFilterReady()) {
                taskExecutionTimeUs += schedulerExecuteTask(getTask(TASK_FILTER), currentTimeUs);
            }
            if (pidLoopReady()) {
                taskExecutionTimeUs += schedulerExecuteTask(getTask(TASK_PID), currentTimeUs);
            }
            currentTimeUs = micros();
            realtimeTaskRan = true;
        }
    }

    if (!gyroEnabled || realtimeTaskRan || (gyroTaskDelayUs > GYRO_TASK_GUARD_INTERVAL_US)) {
        // The task to be invoked

        // Update task dynamic priorities
        for (task_t *task = queueFirst(); task != NULL; task = queueNext()) {
            if (task->staticPriority != TASK_PRIORITY_REALTIME) {
                // Task has checkFunc - event driven
                if (task->checkFunc) {
                    const timeUs_t currentTimeBeforeCheckFuncCallUs = currentTimeUs;
                    // Increase priority for event driven tasks
                    if (task->dynamicPriority > 0) {
                        task->taskAgeCycles = 1 + ((currentTimeUs - task->lastSignaledAtUs) / task->desiredPeriodUs);
                        task->dynamicPriority = 1 + task->staticPriority * task->taskAgeCycles;
                        waitingTasks++;
                    } else if (task->checkFunc(currentTimeBeforeCheckFuncCallUs, cmpTimeUs(currentTimeBeforeCheckFuncCallUs, task->lastExecutedAtUs))) {
                        task->lastSignaledAtUs = currentTimeBeforeCheckFuncCallUs;
                        task->taskAgeCycles = 1;
                        task->dynamicPriority = 1 + task->staticPriority;
                        waitingTasks++;
                    } else {
                        task->taskAgeCycles = 0;
                    }
                } else {
                    // Task is time-driven, dynamicPriority is last execution age (measured in desiredPeriods)
                    // Task age is calculated from last execution
                    task->taskAgeCycles = ((currentTimeUs - getPeriodCalculationBasis(task)) / task->desiredPeriodUs);
                    if (task->taskAgeCycles > 0) {
                        task->dynamicPriority = 1 + task->staticPriority * task->taskAgeCycles;
                        waitingTasks++;
                    }
                }

                if (task->dynamicPriority > selectedTaskDynamicPriority) {
                    selectedTaskDynamicPriority = task->dynamicPriority;
                    selectedTask = task;
                }
            }
        }

        totalWaitingTasksSamples++;
        totalWaitingTasks += waitingTasks;

        if (selectedTask) {
            timeDelta_t taskRequiredTimeUs = TASK_AVERAGE_EXECUTE_FALLBACK_US;  // default average time if task statistics are not available

            // Add in the time spent so far in check functions and the scheduler logic
            taskRequiredTimeUs += cmpTimeUs(micros(), currentTimeUs);
            if (!gyroEnabled || realtimeTaskRan || (taskRequiredTimeUs < gyroTaskDelayUs)) {
                taskExecutionTimeUs += schedulerExecuteTask(selectedTask, currentTimeUs);
            } else {
                selectedTask = NULL;
            }
        }
    }
}

void schedulerEnableGyro(void)
{
    gyroEnabled = true;
}

uint16_t getAverageSystemLoadPercent(void)
{
    return averageSystemLoadPercent;
}