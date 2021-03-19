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

#include "primitives.h"

/*
 * Description: Low-Level kinematic primitives; incorp. dynamics of the 
 *              robot (accel, deccel, friction).
 * 
 */

int32_t reqDistanceToSpeed(float speed)
{
    float acceleration;
	float current_speed = getLinearVelocity();

	acceleration = (current_speed > speed) ? -LIN_ACCELERATION
                                           :  LIN_ACCELERATION;

	return 0; //(int32_t)((speed * speed - current_speed * current_speed) /
                 //(2 * acceleration) * 1e6); [ToDo: Calibrate!]
}

void targetStraight(int32_t start_um, float delta_dist_m, float speed_ms)
{
    int32_t target_dist = start_um + (int32_t)(delta_dist_m * 1e6);
    
    if (delta_dist_m > 0.0f)
    {
        setSetpointLinearVelocity(speed_ms);
        while (getDistance() < target_dist - reqDistanceToSpeed(speed_ms));
    }
    else if (delta_dist_m < 0.0f)
    {
        setSetpointLinearVelocity(-speed_ms);
        while (getDistance() > target_dist - reqDistanceToSpeed(speed_ms));
    }
}

void targetTurn(float angle, bool controlled)
{
    if (controlled)
    {
        setSetpointTurnAngle(angle);
        while(getAngle() > 0.0f);
    }
    else
    {
//        if (grad > 0.0f)
//        {
//            setSetpointAngularVelocity(speed_ms);
//            while (getAngle() < grad);
//        }
//        else if (grad < 0.0f)
//        {
//            setSetpointAngularVelocity(-speed_ms);
//            while (getAngle() > grad);
//        }
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
    toggleSideControl(false);
    toggleFrontControl(false);
    toggleTurnControl(false);
    targetStraight(getDistance(), 0.1f, 0.3*MAX_SPEED_MS);
    
    // hard-stop - ToDo
    setSetpointLinearVelocity(0.0f);
}

void moveSide(void)
{
    toggleMotorControl(true);
    toggleSideControl(false);
    toggleFrontControl(false);
    resetAngleTick();
    toggleTurnControl(true);
    targetTurn(180.0f, true);
}
