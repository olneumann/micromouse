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
#include "../drivers/motor.h"
#include "../drivers/encoder.h"
#include "../common/logger.h"

#include "init.h"

void init(void)
{
    boardInit();
    serialInit();
    
    /* TODO: mapping of sensor value stream (qei) into dma */
    //dmaInit();
    
    /* TODO: (if no dc/dc converter) setup analog pin for sensing battery voltage */
    //adcInit();
    
    motorInit();
    /* TODO: setup qei (pulses per rev, position/angle measurement, etc.) */
    qeiInit(0);
    
    /* TODO: start main timer - setup pid control loop */
    timerInit(); 
    enableTimer();
}
    
  