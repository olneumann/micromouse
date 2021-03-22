/* 
 * File:   hmi.c
 * Author: oliver
 *
 * Created on 14. March 2021, 10:22
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../dspic/board.h"
#include "../common/defines.h"
#include "../drivers/serial_uart.h"
#include "../dspic/tasks.h"

#include "hmi.h"

void userCommand(char *cmd, int *pval) 
{
    if(strcmp(cmd, "run") && *pval == 42) runFlag = true;
}

