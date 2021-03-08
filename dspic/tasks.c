/* 
 * File:   tasks.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 12:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../dspic/board.h"
#include "../common/defines.h"
#include "../drivers/encoder.h"
#include "../drivers/ranging.h"
#include "../drivers/serial_uart.h"
#include "../drivers/serial_i2c.h"
#include "../drivers/motor.h"
#include "../control/pid.h"

#include "tasks.h"

void taskTest(void)
{
#ifdef VL53L0X_DEBUG
    char str[30];
    
    //i2c_test();
    doRanging();
    uint16_t val = getRange();
       
    sprintf(str, "RL %d\n", val);   
    uartWrite(str,0);
#endif
    
    char str[30];
    float val = getRangeLeft();
    sprintf(str, "RL %-.4f\n", val);   
    uartWrite(str,0);  
}

void taskEncoder(uint16_t freq)
{
    updateEncoderReadings(freq);
}

void taskRanging(uint16_t freq)
{
    // do we need it in the end?
}

void taskControl(uint16_t freq)
{
    //timeUs_t currentTimeUs;
    //pidController(currentTimeUs);
    //writeMotors();
}

