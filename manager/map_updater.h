#ifndef MAP_UPDATER_H
#define MAP_UPDATER_H

#include "../manager/manager.h"

#include "../sensors/ranging.h"
#include "../common/general_definitions.h"
#include "../common/general_parameters.h"
#include <stdio.h>
#include <stdarg.h>
#define MAZE_WALL_SIZE ((MAZE_SIZE<<1) + 1)

static volatile bool walls[MAZE_WALL_SIZE][MAZE_WALL_SIZE];
static volatile walls_around_t walls_around = {False, False, False, False};

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

bool is_wall(uint8_t, uint8_t);

void set_a_wall(uint8_t, uint8_t);

void set_walls_along_y(uint8_t y, int wall_count, ...);

void set_walls_along_x(uint8_t x, int wall_count, ...);

void print_walls_around();

bool is_cells_the_same(position,position);


#endif
