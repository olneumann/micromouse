/* 
 * File:   main.c
 * Author: oliver
 *
 * Created on 20. November 2020, 16:21
 */

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"
#include "dspic/init.h"
#include "scheduler/scheduler.h"

void run(void);

int main(void) 
{
    init();
    run();
        
    return 0;
}

void run(void)
{
    while (true) {
        // scheduler();
        // processLoopback();)
    }
}


