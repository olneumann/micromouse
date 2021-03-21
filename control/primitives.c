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
#include "../control/control.h"

#ifdef PRIMITIVES_DEBUG
#include "../control/pid.h"
#include "../drivers/ranging.h"
#include "../drivers/serial_uart.h"
#endif

// import from manager/pathplanning?
#define CELL_DIMENSION  0.16f

#include "primitives.h"

/*
 * Description: Low-Level kinematic primitives; incorp. dynamics of the 
 *              robot (accel, deccel, friction).
 * 
 */

void targetStraight(int32_t start_um, float delta_dist_m, float speed_ms)
{
    int32_t target_dist = start_um + (int32_t)(delta_dist_m * 1e6);
    setSetpointDeltaSide(0.0f);
    
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
    
    targetStraight(getDistance(), CELL_DIMENSION, getSpeedLimit());
}

void moveBackward(void)
{
    toggleMotorControl(true);
    toggleSideControl(true);
    toggleFrontControl(false);
    
    targetStraight(getDistance(), -CELL_DIMENSION, getSpeedLimit());
}

void moveSide(float angle)
{
    toggleMotorControl(true);
    toggleSideControl(false);
    toggleFrontControl(false);

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
    else if (primitive == MOVE_BACK)
        moveBackward();
    else if (primitive == MOVE_END)
        moveStop();   
}