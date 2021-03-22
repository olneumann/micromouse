#include "actions.h"

void move_one_cell_towards(direction d) {
    state mouse_state = get_mouse_state();
    turn_towards(d);
    position cell = what_is_the_position_after_moving_one_step_in_the_direction(mouse_state.p, d);
#ifndef DISCOVERY_SIMULATION
    move(MOVE_FRONT); //TODO move
#endif
    set_mouse_state(cell, d);
}

void turn_left_inplace_90(direction towards) {
    logger.info("turn left 90 %d\n");

#ifndef DISCOVERY_SIMULATION
    move(MOVE_LEFT); //TODO turn_left_inplace_90
#endif

    set_mouse_direction(towards);

}

void turn_right_inplace_90(direction towards) {
    logger.info("turn right 90 %d\n");

#ifndef DISCOVERY_SIMULATION
    move(MOVE_RIGHT); //TODO turn_right_inplace_90
#endif

    set_mouse_direction(towards);
}

void turn_inplace_180(direction towards) {
    logger.info("turn back 180 %d\n");

#ifndef DISCOVERY_SIMULATION
    move(MOVE_TURN); //TODO turn_inplace_180
#endif

    set_mouse_direction(towards);
}

void turn_towards(direction d) {
    state mouse_state = get_mouse_state();
    switch (mouse_state.d) {
        case West:
            switch (d) {
                case East:
                    turn_inplace_180(d);
                    break;
                case North:
                    turn_right_inplace_90(d);
                    break;
                case South:
                    turn_left_inplace_90(d);
                    break;
                default:
                    break;
            }
            break;
        case East:
            switch (d) {
                case West:
                    turn_inplace_180(d);
                    break;
                case North:
                    turn_left_inplace_90(d);
                    break;
                case South:
                    turn_right_inplace_90(d);
                    break;
                default:
                    break;
            }
            break;

        case North:
            switch (d) {
                case West:
                    turn_left_inplace_90(d);
                    break;
                case East:
                    turn_right_inplace_90(d);
                    break;
                case South:
                    turn_inplace_180(d);
                    break;
                default:
                    break;
            }
            break;

        case South:
            switch (d) {
                case West:
                    turn_right_inplace_90(d);
                    break;
                case East:
                    turn_left_inplace_90(d);
                    break;
                case North:
                    turn_inplace_180(d);
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }

}

primitives_e get_turn_action_id(direction current_direction, direction desired_direction) {
    switch (current_direction) {
        case West:
            switch (desired_direction) {
                case East:
                    return MOVE_TURN;
                case North:
                    return MOVE_RIGHT;
                case South:
                    return MOVE_LEFT;
                default:
                    break;
            }
            break;
        case East:
            switch (desired_direction) {
                case West:
                    return MOVE_TURN;
                case North:
                    return MOVE_LEFT;
                case South:
                    return MOVE_RIGHT;
                default:
                    break;
            }
            break;

        case North:
            switch (desired_direction) {
                case West:
                    return MOVE_LEFT;
                case East:
                    return MOVE_RIGHT;
                case South:
                    return MOVE_TURN;
                default:
                    break;
            }
            break;

        case South:
            switch (desired_direction) {
                case West:
                    return MOVE_RIGHT;
                case East:
                    return MOVE_LEFT;
                case North:
                    return MOVE_TURN;
                default:
                    break;
            }
            break;

        default:
            break;
    }

}

action * create_a_move_action(position current_cell, position next_cell,
                          direction resulting_orientation){
    action *move = (action *) malloc(sizeof(action));
    move->resulting_cell = next_cell;
    move->starting_cell = current_cell;
    move->resulting_direction = resulting_orientation;
    move->action_primitive_id = MOVE_FRONT;
    move->previous = NULL;
    move->next = NULL;
    return move;
}

action * create_a_turn_action(position current_cell, direction current_orientation,
                              direction resulting_orientation){
    action *turn = (action *) malloc(sizeof(action));
    turn->starting_cell = current_cell;
    turn->resulting_cell = current_cell;
    turn->resulting_direction = resulting_orientation;
    turn->action_primitive_id = get_turn_action_id(current_orientation, resulting_orientation);
    turn->previous=NULL;
    turn->next=NULL;
    return turn;
}

action *add_actions_according_to(action *tail_chain_actions, position current_cell, position next_cell,
                                 direction current_orientation) {
    direction resulting_orientation = get_direction_btw_start_and_end_cell(current_cell, next_cell);

    action *move = create_a_move_action(current_cell,next_cell,resulting_orientation);


    if (resulting_orientation == current_orientation) {        //move action

        if (tail_chain_actions) {
            move->previous = tail_chain_actions;
            tail_chain_actions->next = move;
        }
        tail_chain_actions = move;
    } else {        //turn + move action

        action *turn = create_a_turn_action(current_cell,current_orientation,resulting_orientation);

        if (tail_chain_actions) {
            turn->previous = tail_chain_actions;
            tail_chain_actions->next = turn;
        }
        tail_chain_actions = turn;

        tail_chain_actions->next = move;
        move->previous = tail_chain_actions;
        tail_chain_actions = move;
    }
    return tail_chain_actions;
}

action *get_head_action(action *actions_stack_tail) {
    while (actions_stack_tail->previous) {

        actions_stack_tail = actions_stack_tail->previous;
    }
    return actions_stack_tail;
}

action *get_chain_of_actions_to_reach_goal_cell(position goal_cell) {
    position proceeding_cell = goal_cell, current_cell, next_cell;
    direction current_direction = get_start_direction();;
    action *actions_stack_tail = NULL;
    path *shortest_path = get_shortest_path();
    logger.debug("a\n");

    while (shortest_path->next) {
        current_cell = shortest_path->cell;
        next_cell = shortest_path->next->cell;
        actions_stack_tail = add_actions_according_to(actions_stack_tail, current_cell, next_cell, current_direction);
        current_direction = actions_stack_tail->resulting_direction;
        logger.info("<-- (%d, %d) \n", next_cell.x, next_cell.y);
        shortest_path = shortest_path->next;
    }
    return get_head_action(actions_stack_tail);
}
