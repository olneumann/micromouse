//
// Created by root on 3/3/21.
//

#ifndef MM_DISCOVERY_H
#define MM_DISCOVERY_H

#include "manager.h"
#include "map_updater.h"
#include "../common/general_parameters.h"
#include "../simulation/simulation_common.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <aio.h>


struct mission {
    position start;
    position target;
    uint8_t number_of_steps;
    direction d;
    struct mission *parent;
    position last_seen_to_visit_cell;
    uint8_t distance_to_last_seen_cell_to_visit;
    position the_start_cell_for_the_last_seen_cell_to_visit;
};
typedef struct mission mission;
void init_visited_cells(void);
void print_visited_cells(void);
void set_the_map(void);
uint8_t manhattan_distance(position a, position b);
position get_the_cell_by_the_wall_related_to_mouse_orientation(position wall);
direction get_direction_btw_start_and_end_cells(position start, position end);
position what_is_the_position_after_moving_one_step_in_the_direction(position pos, direction d);
position get_the_most_distant_cell_for_2_walls(position r_wall, position l_wall);
position get_the_most_distant_cell_for_3_walls(position f_wall, position r_wall, position l_wall);
direction get_opposite_direction(direction d);
mission *init_mission(mission *parent, position target, position start);
uint8_t get_visits(position cell);
void run_algo(void);
void set_visited(position);
bool is_cells_the_same(position,position);
void print_missions(mission*);

#endif //MM_DISCOVERY_H
