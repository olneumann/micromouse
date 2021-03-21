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

#include "primitives.h"

/*
 * Description: Low-Level kinematic primitives; incorp. dynamics of the 
 *              robot (accel, deccel, friction).
 * 
 */

void targetStraight(int32_t start_um, float delta_dist_m, float speed_ms)
{
    int32_t target_dist = start_um + (int32_t)(delta_dist_m * 1e6);
    
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
        setSetpointTurnAngle(delta_angle_deg, speed_ms);
        toggleTurnControl(true);
        while (getDiffAngle() < delta_angle_deg);
        toggleTurnControl(false);
    }
    else if (delta_angle_deg < 0.0f)
    {
        
    }
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
    
    targetStraight(getDistance(), 0.4f, 0.2f*MAX_SPEED_MS);
    
    toggleSideControl(false);
    
    // ToDo: Transition into next action, blending?
}

void moveSide(void)
{
    toggleMotorControl(true);
    toggleSideControl(false);
    toggleFrontControl(false);

    targetTurn(180.0f, 0.1f*MAX_SPEED_MS);

    
    // ToDo: Transition into next action, blending?
}
