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
      
    /* TODO: (if no dc/dc converter) setup analog pin for sensing battery voltage */
    //adcInit();
    
    /*
     * Components Initialization:
     * - motorInit()   -> PWM Generation (Freq.)
     * - qeiInit()     -> Encoder Readings (Pulses, Unit Conversion)
     * - rangingInit() -> VL53L0X Ranging Readings (Remapping, Measurement Freq.)
     *      
     */
    
    motorInit();
    qeiInit();
    //rangingInit();
    
    /* 
     * Main loop:
     * Generates task calls for control (pid), sensing (range, encoder)
     * 
     */
    
    timerInit(); 
    enableTimer();
}
    
  