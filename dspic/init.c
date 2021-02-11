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
#include "../common/logger.h"

void init(void)
{
    //loggerInit();
    
    boardInit();
    //serialInit();
    
    /* TODO: mapping of sensor value streams (qei/i2c) into dma */
    //dmaInit();
    
    /* TODO: (if no dc/dc converter) setup analog pin for sensing battery voltage */
    //adcInit();
    
    //motorInit();
    /* TODO: setup qei (pulses per rev, position/angle measurement, etc.) */
    //qeiInit();
    
    /* TODO: start main timer - setup pid control loop */
    //timerInit(); 
    //enableTimer();

    //qei1_init(0);
}
    
  