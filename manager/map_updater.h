#ifndef MAP_UPDATER_H
#define MAP_UPDATER_H

#include "../common/general_definitions.h"
#include "../common/general_parameters.h"
#include "../common/logger.h"
#include "mouse_state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#define MAZE_WALL_SIZE ((MAZE_SIZE<<1) + 1)

static volatile walls_around_t walls_around = {False, False, False, False};

extern position goal_cells[];

#if !DISCOVERY_SIMULATION
distance get_front_sensor_range_data(void);
distance get_right_sensor_range_data(void);
distance get_left_sensor_range_data(void);
#else
#include "../simulation/simulation_common.h"
#endif

void init_walls(void);

void get_grid_location(void);

void get_map(void);

void update_map(void);

void print_walls(void);

position get_first_seen_wall(direction, distance);

walls_around_t reset_around_walls();

void print_walls_around();

bool is_cells_the_same(position,position);

position get_the_cell_by_the_wall_related_to_mouse_orientation(position wall);

position what_is_the_position_after_moving_one_step_in_the_direction(position pos, direction d);

direction get_sight_direction_of_sensor(ranging_sensor);

direction get_direction_btw_start_and_end_cell(position start, position end);

uint8_t manhattan_distance_uint16_t(position a, position b);
#endif
