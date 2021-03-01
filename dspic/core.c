/* 
 * File:   core.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 12:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../dspic/tasks.h"

#include "core.h"

void debug(void)
{
    taskTest();
}

void control_loop(uint16_t freq)
{
    taskControl(freq);
}

void encoder_loop(uint16_t freq)
{
    taskEncoder(freq);
}

void ranging_loop(uint16_t freq)
{
    taskRanging(freq);
}

void explore(void)
{
    // exploration phase
}

void fast_run(void)
{
    // final fast run
}