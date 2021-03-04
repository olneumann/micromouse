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
    char str[30];
    char str2[30];
       
    driveLeft(0);   
    driveRight(0);
   
    uint8_t data = 42;
    uint8_t* pData = &data;
    
    //i2cWrite(0x29,0x42,pData, 1);
    
    float val = getRangeLeft();
    //float val = getVelocityRight();
    //float val2 = getVelocityLeft();
   
    sprintf(str, "RL %-.4f\n", val);
    //sprintf(str2, "VL %-.4f\n", val2);
        
    uartWrite(str,0);
    //uartWrite(str2,0);
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

