//
// Created by root on 3/4/21.
//

#ifndef MM_DISCOVERY_2_H
#define MM_DISCOVERY_2_H

#endif //MM_DISCOVERY_2_H
//
// Created by root on 3/3/21.
//

#ifndef MM_DISCOVERY_H
#define MM_DISCOVERY_H

#include "../common/general_parameters.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <aio.h>

#if DISCOVERY_SIMULATION
#include "../simulation/simulation_common.h"
#endif

#include "map_updater.h"
#include "manager.h"

void print_visited_cells(void);
void init_visited_cells(void);

struct mission {
    position start;
    uint8_t number_of_fork_missions;
    direction d;
    struct mission * parent;
    struct mission * fork_missions[MAZE_SIZE];
};
typedef struct mission mission;
direction get_opposite_direction(direction);
position get_the_cell_by_the_wall_related_to_mouse_orientation(position wall);
direction get_direction_btw_start_and_end_cells(position start, position end);
mission *create_a_mission(mission*, direction, position);
uint8_t get_visits(position cell);
void run_algo(void);
void set_visited(position);
bool is_cells_the_same(position,position);
void print_missions(mission*);
void process_mission(mission*);
void convert_to_an_undo_mission(mission*);
void process_fork_missions(mission*);
void process_fork_mission(mission* fork_mission);
mission *add_a_mission(mission*,ranging_sensor);


#endif //MM_DISCOVERY_H
