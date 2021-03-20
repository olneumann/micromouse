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

#ifdef VL53L0X_DEBUG
#include "../drivers/ranging.h"
#include "../drivers/serial_uart.h"
#include "../drivers/serial_i2c.h"
#endif

#ifdef CONTROL_DEBUG
#include "../control/pid.h"
#include "../control/primitives.h"
#include "../drivers/ranging.h"
#include "../drivers/serial_uart.h"
#endif

#ifdef PRIMITIVES_DEBUG
#include "../control/pid.h"
#include "../control/primitives.h"
#include "../drivers/ranging.h"
#include "../drivers/serial_uart.h"

bool runFlag = false;

#endif

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
    static float m = 0.5f;
    setSetpointLinearVelocity(m*MAX_SPEED_MS);    
    setSetpointDeltaSide(0.0f);
    
    if (BTN)
    {
        m += 0.1f;
        if (m > 0.95f) m = 0.1f;
    }
        
    toggleMotorControl(true);
    toggleSideControl(true);
            
    
    char str[100];   
    sprintf(str, "[IN %-.3f][R %-.3f][L %-.3f] [SUM %-.3f] [VL %-.3f] [VR %-.3f]\n", 
            getInput(PID_DIST_SENSOR_SIDE),
            getRangeRight(),
            getRangeLeft(),
            pidData[PID_DIST_SENSOR_SIDE].Sum,
            getLinearVelocityLeft(),
            getLinearVelocityRight());
    uartWrite(str,0);
#endif
#ifdef PRIMITIVES_DEBUG
    setSetpointDeltaSide(0.0f);
    
    if (runFlag)
    {
        moveForward();
        moveSide();
        moveForward();
        moveSide();
        moveForward();
        moveSide();
        moveForward();
        moveSide();

        setSetpointLinearVelocity(0.0f);
        runFlag = false;
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