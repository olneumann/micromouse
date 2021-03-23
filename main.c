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
#include "dspic/core.h"

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
        //explore();
        
        //if (BTN) inference();
    }
}

