/*
 * File:   primitives.c
 * Author: oliver
 *
 * Created on 2. Januar 2021, 17:00
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "../dspic/board.h"
#include "../drivers/encoder.h"
#include "../drivers/motor.h"
#include "../control/control.h"

#ifdef PRIMITIVES_DEBUG
#include "../control/pid.h"
#include "../drivers/ranging.h"
#include "../drivers/serial_uart.h"
#endif

#include "../manager/manager_parameters.h"

#include "primitives.h"

#define MIN_DIST_FRONT_MM   20.0f                   // in mm
#define CELL_SIZE_M         A_CELL_SIZE / 10.0f     // cm to m

/*
 * Description: Low-Level kinematic primitives; incorp. dynamics of the 
 *              robot (accel, deccel, friction).
 * 
 */

void targetStraight(int32_t start_um, float delta_dist_m, float speed_ms)
{
    int32_t target_dist = start_um + (int32_t)(delta_dist_m * 1e6);
    setSetpointDeltaSide(0.0f);
    setSetpointFrontDistance(MIN_DIST_FRONT_MM);
    
    if (delta_dist_m > 0.0f)
    {
        setSetpointLinearVelocity(speed_ms);
        while (getDistance() < target_dist);
    }
    else if (delta_dist_m < 0.0f)
    {
        setSetpointLinearVelocity(-speed_ms);
        while (getDistance() > target_dist);
    }
}

void targetTurn(float delta_angle_deg, float speed_ms)
{
    setSetpointDeltaSide(0.0f);
    setSetpointFrontDistance(MIN_DIST_FRONT_MM);
            
    if (delta_angle_deg > 0.0f)
    {
        LED_IND1 = LEDON;
        setSetpointTurnAngle(delta_angle_deg, speed_ms);
        toggleTurnControl(true);
        while (getDiffAngle() < delta_angle_deg);
        toggleTurnControl(false);
        LED_IND1 = LEDOFF;
    }
    else if (delta_angle_deg < 0.0f)
    {
        LED_IND2 = LEDON;
        setSetpointTurnAngle(delta_angle_deg, -speed_ms);
        toggleTurnControl(true);
        while (getDiffAngle() > delta_angle_deg);
        toggleTurnControl(false);
        LED_IND2 = LEDOFF;
    }
}

void targetStop(void)
{
    setSetpointLinearVelocity(0.0f);
    resetSlidingSetpointVelocity();
}

/*
 * Description: Cell-wise functions/primitives (forward, side, backwards, turn on spot)
 *              Should then be used in the manager/pathplanner as a concatenation
 *              of primitives to solve the maze.
 * 
 */

void moveForward(void)
{
    toggleMotorControl(true);
    toggleSideControl(true);
    toggleFrontControl(false);
    
    setSpeedLimit(0.5f * MAX_SPEED_MS);
    
    targetStraight(getDistance(), CELL_SIZE_M, getSpeedLimit());
}

void moveBackward(void)
{
    toggleMotorControl(true);
    toggleSideControl(false);   // ToDo!!
    toggleFrontControl(false);
    
    setSpeedLimit(0.4f * MAX_SPEED_MS);
    
    targetStraight(getDistance(), -CELL_SIZE_M, getSpeedLimit());
}

void moveSide(float angle)
{
    toggleMotorControl(true);
    toggleSideControl(false);
    toggleFrontControl(false);

    setSpeedLimit(0.3f * MAX_SPEED_MS);
    
    targetTurn(angle, getSpeedLimit());
}

void moveStop(void)
{
    toggleMotorControl(false);
    toggleSideControl(false);
    toggleFrontControl(false);
    toggleTurnControl(false);
    
    targetStop();
}

void move(primitives_e primitive)
{
    if (primitive == MOVE_FRONT)
        moveForward();
    else if (primitive == MOVE_LEFT)
        moveSide(-90.0f);
    else if (primitive == MOVE_RIGHT)
        moveSide(90.0f);
    else if (primitive == MOVE_TURN)
        moveSide(180.0f);    
    else if (primitive == MOVE_BACK)
        moveBackward();
    else if (primitive == MOVE_END)
        moveStop();   
}