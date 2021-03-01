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
#include "../drivers/motor.h"
#include "../control/pid.h"

#include "tasks.h"

void taskTest(void)
{
    char str[30];
    char str2[30];
       
    driveLeft(-1);   
    driveRight(0);
    
    int32_t val = getDistanceLeft();
    float val2 = getVelocityLeft();
    
    sprintf(str, "DIST %d\n", val);    
    sprintf(str2, "VELO %f.4\n", val2);
        
    uartWrite(str,0);
    uartWrite(str2,0);
    
    if (BTN == 1)
    {          
        LED_W = ~LED_W;
    }
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

