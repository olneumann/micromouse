/*
 * File:   primitives.c
 * Author: lucia
 *
 * Created on 19. März 2021, 18:51
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "../drivers/encoder.h"
#include "../drivers/ranging.h"
#include "pid.h"

#include "primitives.h"

// appropriate velocities for forward/backward motion and turning
#define VEL_FW 0.5f
#define VEL_TURN 0.5f
#define VEL_BW 0.5f
// if full turn around, which direction to turn
#define TURN_DIR_RIGHT true
// cell side in um
#define CELL_SIZE 18000
// distance at which stop before frontal wall should be initiated
#define DIST_FRONT 18000

static float motor_left = 0.0f;
static float motor_right = 0.0f;


float get_desired_val(int ctrl)
{
    if (ctrl == PID_L_MOTOR)
    {
        return motor_left;
    }
    else if (ctrl == PID_R_MOTOR)
    {
        return motor_right;
    }
    else
    {
        printf("PID Index desired value not implemented yet");
    }
    return 0.0f;
}

float get_input_val(int ctrl)
{
    if (ctrl == PID_L_MOTOR)
    {
        return getVelocityLeft(); // get velocity from encoder
    }
    else if (ctrl == PID_R_MOTOR)
    {
        return getVelocityRight(); // get velocity from encoder
    }
    else
    {
        printf("PID Index input value not implemented yet");  
    }
    return 0.0f;
}

void stop(void)
{
    // stop movement
    motor_left = 0.0f;
    motor_right = 0.0f;
}

void move_straight(bool forward, int distance)
{
    motor_left = forward ? VEL_FW : VEL_BW;
    motor_right = forward ? VEL_FW : VEL_BW;
    
    // 1st scenario: Mouse should travel given distance (distance is given
    //               if != -1) without checking environment
    if (distance != -1)
    {
        int tmp_distance = (int) 0.5f * (getDistanceLeft()+getDistanceRight());
        // continue on straight
        while (tmp_distance + distance >
                (int) 0.5f * (getDistanceLeft()+getDistanceRight()));
    }
    // 2nd scenario: Mouse currently not enclosed by both sides and should move 
    //               to the next/previous cell
    else if (getRangeLeft() + getRangeRight() > 160)
    {
        int tmp_distance = (int) 0.5f * (getDistanceLeft()+getDistanceRight());
        // continue on straight
        while (tmp_distance + (forward ? 1 : -1) * CELL_SIZE > // next cell not reached
                (int) 0.5f * (getDistanceLeft()+getDistanceRight())
                && (!forward || getRangeFront() > DIST_FRONT)); // not the end
        while (getRangeLeft() + getRangeRight() < 160 && // enclosed on either side
                (!forward || getRangeFront() > DIST_FRONT)); // not the end
        if (getRangeFront() > DIST_FRONT) // at the end emergency stop
            stop();
    }
    // 3rd scenario: Mouse currently enclosed by both sides and should move forward
    //               until not longer enclosed
    else
    {
        // continue on straight
        while (getRangeLeft() + getRangeRight() < 160 && // still enclosed
                (!forward || getRangeFront() > DIST_FRONT)); // not the end
        if (getRangeFront() > DIST_FRONT) // at the end emergency stop
            stop();
    }
}

void turn(int degrees)
{
    motor_left = degrees > 0 ? VEL_TURN : - VEL_TURN;
    motor_right = degrees > 0 ? - VEL_TURN : VEL_TURN;
    
    float tmp_angle_left = getAngleLeft();
    float tmp_angle_right = getAngleRight();
    
    while(getAngleLeft()-getAngleRight()-tmp_angle_left+tmp_angle_right
            < degrees * (degrees>0 ? 1 : -1));
}

void turn_left(void)
{
    turn(-90);
}

void turn_right(void)
{
    turn(90);
}

void turn_around(void)
{
    TURN_DIR_RIGHT ? turn(180) : turn(-180);
}

void move_forward(void)
{
    move_straight(true, -1);
}

void move_backward(void)
{
    move_straight(false, -1);
}

void move_distance(int distance) // distance in um
{
    move_straight(distance>0 ? true : false, distance);
}