//
// Created by root on 3/13/21.
//

#include "mouse_state.h"
position get_start_cell() {
    return (position) {START_POSITION_X, START_POSITION_Y};
}
direction get_start_direction() {
    return (direction) {START_DIRECTION};
}

void set_mouse_state(position cell,direction d){
    MOUSE_STATE.p.x = cell.x;
    MOUSE_STATE.p.y = cell.y;
    MOUSE_STATE.d = d;
}


state get_mouse_state() {
    return MOUSE_STATE;
}
void set_mouse_direction(direction d) {
    MOUSE_STATE.d = d;
}