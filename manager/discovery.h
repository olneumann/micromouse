//
// Created by root on 3/4/21.
//
#ifndef MM_DISCOVERY_H
#define MM_DISCOVERY_H

#include "../common/general_parameters.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#if (DISCOVERY_SIMULATION==1)
#include "../simulation/simulation_common.h"
#endif

#include "../common/logger.h"
#include "mouse_state.h"
#include "map_updater.h"
#include "shortest_path.h"
#include "actions.h"

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
mission *create_a_mission(mission*, direction, position);
uint8_t get_visits(position cell);
void start_explorer(void);
void set_visited(position);
void print_missions(mission*);
void process_mission(mission*);
void convert_to_an_undo_mission(mission*);
void process_fork_missions(mission*);
void process_fork_mission(mission* fork_mission);
mission *add_a_mission(mission*,ranging_sensor);
void start_explorer();

#endif //MM_DISCOVERY_H
