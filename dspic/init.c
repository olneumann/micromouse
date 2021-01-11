/*
 * File:   init.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "board.h"
#include "../io/serial.h"
#include "../drivers/timer.h"
#include "../drivers/dma.h"
#include "../drivers/adc.h"

void init(void)
{
    boardInit();
    serialInit();
    

    dmaInit();
    adcInit();
    
    timerInit();
    enableTimer();
        
    //motor_init();
    //qei1_init(0);
}
    
  