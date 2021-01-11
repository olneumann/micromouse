/* 
 * File:   core.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 12:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../control/pid.h"
#include "core.h"

void taskEncoder(void)
{
    // getEncoderData();
}

void taskPIDLoop(timeUs_t currentTimeUs)
{
    pidController(currentTimeUs);
    // writeMotors();
}