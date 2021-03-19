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
#include "../control/primitives.h"
#include "../drivers/serial_uart.h"
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
    static float m = 0.0f;
    
    setSetpointLinearVelocity(m*MAX_SPEED_MS);    
    setSetpoint(3, 20.0f);
    
    if (BTN)
    {
        m += 0.1f;
        if (m > 0.95f) m = 0.1f;
    }
    
    float controlLeft;
    
    toggleMotorControl(true);
    toggleFrontControl(true);
    
    controlLeft = 1.0f * pidData[PID_VELO_MOTOR_LEFT].Sum
                + 0.0f  * pidData[PID_DIST_SENSOR_SIDE].Sum
                + 1.0f * (pidRuntime.prevPidSetpoint[PID_VELO_MOTOR_LEFT] + pidData[PID_DIST_SENSOR_FRONT].Sum);
    
        
    char str[100];   
    sprintf(str, "DC[%-.3f] IN[%-.4f] ST[%-.4f] P[%-.3f] I[%-.3f] D[%-.3f] F[%-.3f]\n", 
            convDC(controlLeft, 0),
            pidRuntime.prevPidInput[PID_VELO_MOTOR_LEFT],
            pidRuntime.prevPidSetpoint[PID_VELO_MOTOR_LEFT],
            pidData[PID_VELO_MOTOR_LEFT].P,
            pidData[PID_VELO_MOTOR_LEFT].I,
            pidData[PID_VELO_MOTOR_LEFT].D,
            getRangeFront());
    uartWrite(str,0);
#endif
    
#ifdef PRIMITIVES_DEBUG
    char str[42];     
    toggleMotorControl(true);
    //setSetpointAngularVelocity(0.05f * MAX_SPEED_MS);
    //sprintf(str, "% -.3f\n", getAngle()); 
    //uartWrite(str,0);
    
    if (BTN)
    {
        LED_IND1 = ~LED_IND1;
        //moveForward();
        moveSide();
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