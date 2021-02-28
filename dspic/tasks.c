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
    //char str[30];
    //char str2[30];
       
    driveLeft(1);   
    driveRight(0.05);
            
    //float test = getRangeLeft();
    
    //sprintf(str, "BTN %d\n", BTN);    
    //sprintf(str2, "P2 %d\n", POS2CNT);
        
    //uartWrite(str);
    //uartWrite(str2);
    
    if (BTN == 1)
    {          
        LED_W = LEDON;

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
