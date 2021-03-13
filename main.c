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
#include "manager/manager.h"
void run(void);

int main(void) 
{
    init();
    run();
        
    return 0;
}

void run(void)
{

    start_discovery();
    init_inference();
    start_inference(0);
}

