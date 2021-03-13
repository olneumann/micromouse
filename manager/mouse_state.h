//
// Created by root on 3/13/21.
//

#ifndef MM_MOUSE_STATE_H
#define MM_MOUSE_STATE_H
#include "../common/general_definitions.h"
#include "../common/general_parameters.h"

static volatile state MOUSE_STATE = {{START_POSITION_X, START_POSITION_Y}, START_DIRECTION};

void turn_towards(direction);

position what_is_the_position_after_moving_one_step_in_the_direction(position , direction );

void move_to_one_cell_in_direction(direction);

state get_mouse_state(void);

position get_start_cell();
#endif //MM_MOUSE_STATE_H
