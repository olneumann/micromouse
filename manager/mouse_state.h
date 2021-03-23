//
// Created by root on 3/13/21.
//

#ifndef MM_MOUSE_STATE_H
#define MM_MOUSE_STATE_H
#include "../manager/manager_parameters.h"
#include "../manager/manager_definitions.h"

static volatile state MOUSE_STATE = {{START_POSITION_X, START_POSITION_Y}, START_DIRECTION};

state get_mouse_state(void);
direction get_start_direction();
void set_mouse_state(position,direction);
void set_mouse_direction(direction);
position get_start_cell();

#endif //MM_MOUSE_STATE_H
