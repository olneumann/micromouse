/*
 * File:   actions.h
 * Author: yigit
 *
 * Created on 2. March 2021, 17:00
 */

#ifndef ACTIONS_H
#define	ACTIONS_H

#include "../manager/manager_parameters.h"
#include "../manager/manager_definitions.h"
#include "../control/primitives.h"

#include "shortest_path.h"
#include "map_updater.h"

struct action {
    primitives_e action_primitive_id;
    position resulting_cell;
    position starting_cell;
    direction resulting_direction;
    struct action * next;
    struct action * previous;
};
typedef struct action action;

action *get_chain_of_actions_to_reach_goal_cell(position);
void move_one_cell_towards(direction d);
void turn_towards(direction);

#endif