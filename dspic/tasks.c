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
#include "../control/control.h"

// for testing
#include "../drivers/ranging.h"
#include "../drivers/serial_uart.h"
#include "../drivers/serial_i2c.h"
#include "../drivers/motor.h"

#include "tasks.h"

void taskTest(void)
{
#ifdef VL53L0X_DEBUG
    char str[30];
    
    //i2c_test();
    doRanging();
    
    uint16_t val = getRange();
    
    sprintf(str, "%d\n", val);   
    uartWrite(str,0);  
#endif
    
#ifdef CONTROL_DEBUG
    //char str[100];
    //sprintf(str, "[I] %d\n",getDiffCnt());
    //uartWrite(str,0);
    
    static float m = 0.0f;
    
    setSetpoint(0, m*MAX_SPEED_MS);
    setSetpoint(1, m*MAX_SPEED_MS);
    
    if (BTN)
    {
        m += 0.1f;
        if (m > 0.95f) m = 0.1f;
    }
#endif
}

void taskEncoder(uint16_t freq)
{
    updateEncoderReadings(freq);
}

void taskControl(uint16_t freq)
{
    motorControl();
}

void taskRanging(uint16_t freq)
{
    // do we need it in the end?
}