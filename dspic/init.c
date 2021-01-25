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
    
    boardInit();
    serialInit();
    loggerInit();
    logger.info("Board, SerialUart, Logger initialized\n");
    dmaInit();
    logger.info("DMA initialized\n");
    adcInit();
    logger.info("ADC initialized\n");
    timerInit(); 
    logger.info("Timer initialized\n");
    enableTimer();
    logger.info("Timer enabled\n");

    //motor_init();
    //qei1_init(0);
}
    
  