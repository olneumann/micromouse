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
#include "../dspic/core.h"
#include "../common/defines.h"
#include "../drivers/encoder.h"
#include "../control/control.h"
#include "../manager/manager.h"

#if defined VL53L0X_DEBUG || defined VL53L0X_HIGH_SPEED_DEBUG
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
#ifdef VL53L0X_HIGH_SPEED_DEBUG
    char str[30];
    sprintf(str, "[L %-.3f][F %-.3f][R %-.3f]\n",
            getRangeLeft(),
            getRangeFront(),
            getRangeRight());
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
    if (runFlag)
    {
        move(MOVE_FRONT);
        move(MOVE_TURN);
        move(MOVE_FRONT);
        move(MOVE_END);

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
    int update_rate = SETPOINT_UPDATE_RATE;    
    static int i = 0;
    if (i == 0) updateSlidingSetpointVelocity();
    motorControl();
    
    i++;
    if (i == update_rate) i = 0;
}

void taskDiscovery(void)
{
    start_discovery();
}

void taskInference(void)
{
    start_inference();
}