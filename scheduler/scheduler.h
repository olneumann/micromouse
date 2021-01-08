/* 
 * File:   scheduler.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 12:11
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include <stdbool.h>
#include "../common/defines.h"

#define TASK_PERIOD_HZ(hz) (1000000 / (hz))
#define TASK_PERIOD_MS(ms) ((ms) * 1000)
#define TASK_PERIOD_US(us) (us)

typedef enum {
    TASK_PRIORITY_REALTIME = -1, // Task will be run outside the scheduler logic
    TASK_PRIORITY_IDLE = 0,      // Disables dynamic scheduling, task is executed only if no other task is active this cycle
    TASK_PRIORITY_LOW = 1,
    TASK_PRIORITY_MEDIUM = 3,
    TASK_PRIORITY_MEDIUM_HIGH = 4,
    TASK_PRIORITY_HIGH = 5,
    TASK_PRIORITY_MAX = 255
} taskPriority_e;

typedef struct {
    timeUs_t     maxExecutionTimeUs;
    timeUs_t     totalExecutionTimeUs;
    timeUs_t     averageExecutionTimeUs;
    timeUs_t     averageDeltaTimeUs;
} cfCheckFuncInfo_t;

typedef struct {
    const char * taskName;
    const char * subTaskName;
    bool         isEnabled;
    int8_t       staticPriority;
    timeDelta_t  desiredPeriodUs;
    timeDelta_t  latestDeltaTimeUs;
    timeUs_t     maxExecutionTimeUs;
    timeUs_t     totalExecutionTimeUs;
    timeUs_t     averageExecutionTimeUs;
    timeUs_t     averageDeltaTimeUs;
    float        movingAverageCycleTimeUs;
} taskInfo_t;

typedef enum {
    /* Actual tasks */
    TASK_SYSTEM = 0,
    TASK_MAIN,
    TASK_ENCODER,
    TASK_PID,
    TASK_FILTER,
    TASK_SERIAL,
    /* Count of real tasks */
    TASK_COUNT,
    /* Service task IDs */
    TASK_NONE = TASK_COUNT,
    TASK_SELF
} taskId_e;

typedef struct {
    bool (*checkFunc)(timeUs_t currentTimeUs, timeDelta_t currentDeltaTimeUs);
    void (*taskFunc)(timeUs_t currentTimeUs);
    timeDelta_t desiredPeriodUs;        // target period of execution
    const int8_t staticPriority;        // dynamicPriority grows in steps of this size

    // Scheduling
    uint16_t dynamicPriority;           // measurement of how old task was last executed, used to avoid task starvation
    uint16_t taskAgeCycles;
    timeDelta_t taskLatestDeltaTimeUs;
    timeUs_t lastExecutedAtUs;          // last time of invocation
    timeUs_t lastSignaledAtUs;          // time of invocation event for event-driven tasks
    timeUs_t lastDesiredAt;             // time of last desired execution
} task_t;

void getCheckFuncInfo(cfCheckFuncInfo_t *checkFuncInfo);
void getTaskInfo(taskId_e taskId, taskInfo_t *taskInfo);
void rescheduleTask(taskId_e taskId, timeDelta_t newPeriodUs);
void setTaskEnabled(taskId_e taskId, bool newEnabledState);
timeDelta_t getTaskDeltaTimeUs(taskId_e taskId);
void schedulerSetCalulateTaskStatistics(bool calculateTaskStatistics);
void schedulerResetTaskStatistics(taskId_e taskId);
void schedulerResetTaskMaxExecutionTime(taskId_e taskId);
void schedulerResetCheckFunctionMaxExecutionTime(void);

void schedulerInit(void);
void scheduler(void);
timeUs_t schedulerExecuteTask(task_t *selectedTask, timeUs_t currentTimeUs);
void taskSystemLoad(timeUs_t currentTimeUs);
void schedulerOptimizeRate(bool optimizeRate);
void schedulerEnableGyro(void);
uint16_t getAverageSystemLoadPercent(void);

#endif	/* SCHEDULER_H */

