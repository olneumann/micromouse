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

void init_walls(void);

void get_grid_location(void);

void get_map(void);

void update_map(void);

void print_walls(void);

position get_first_seen_wall(direction, distance);

bool is_wall(uint8_t, uint8_t);

void set_a_wall(uint8_t, uint8_t);

void set_walls_along_y(uint8_t y, int wall_count, ...);

void set_walls_along_x(uint8_t x, int wall_count, ...);

#endif
