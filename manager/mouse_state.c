//
// Created by root on 3/13/21.
//

#include "mouse_state.h"
position get_start_cell() {
    return (position) {START_POSITION_X, START_POSITION_Y};
}
position what_is_the_position_after_moving_one_step_in_the_direction(position pos, direction d) {
    switch (d) {
        case West:
            pos.x -= 1;
            return pos;
        case East:
            pos.x += 1;
            return pos;
        case North:
            pos.y += 1;
            return pos;
        case South:
            pos.y -= 1;
            return pos;
        default:
            return pos;
    }

}
void move_to_one_cell_in_direction(direction d) {
    position cell = what_is_the_position_after_moving_one_step_in_the_direction(MOUSE_STATE.p, d);
    MOUSE_STATE.p.x = cell.x;
    MOUSE_STATE.p.y = cell.y;
    MOUSE_STATE.d = d;
}
void turn_towards(direction d) {
    MOUSE_STATE.d = d;
    switch (MOUSE_STATE.d) {
        case West:
            switch (d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;
        case East:
            switch (MOUSE_STATE.d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;

        case North:
            switch (MOUSE_STATE.d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;

        case South:
            switch (MOUSE_STATE.d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
state get_mouse_state() {
    return MOUSE_STATE;
}