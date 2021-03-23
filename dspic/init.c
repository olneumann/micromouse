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
#include "../common/logger.h"
#include "../dspic/core.h"
#include "../io/serial.h"
#include "../drivers/timer.h"
#include "../drivers/motor.h"
#include "../drivers/encoder.h"
#include "../drivers/ranging.h"
#include "../control/pid.h"
#include "../manager/manager.h"

#include "init.h"

void init(void)
{
    boardInit();
    serialInit();
    loggerInit();
    
    /* TODO: (if no dc/dc converter) setup analog pin for sensing battery voltage */
    //adcInit();
    
    /*
     * Components Initialization:
     * - motorInit(uint16_t kfpwm)      -> PWM Generation (Freq.)
     * - qeiInit()                      -> Encoder Readings (Pulses, Unit Conversion)
     * - rangingInit(uint16_t kfscl)    -> VL53L0X Ranging Readings (Remapping, Measurement Freq.)
     *      
     */
    
    motorInit(20);
    qeiInit();
    
    pidProfileInit();
    pidInit(CONTROL_LOOP_PERIODE_MS);
    
#ifndef SIMULATOR
    rangingInit(200);
    enableRanging();
#endif
    
    /* 
     * Main loop:
     * Generates task calls for control (pid), sensing (range, encoder). 
     * Finally, the manager is called to do an exploration phase and then infere
     * the final path to the goal position.
     * 
     */
    
    timerInit(); 
    enableTimer();
   
    initManager();
}
    
  