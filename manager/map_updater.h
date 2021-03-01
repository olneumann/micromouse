#ifndef MAP_UPDATER_H
#define	MAP_UPDATER_H

#include "manager.h"
#include "../sensors/ranging.h"
#include "general_parameters.h"

void init_walls(void);
void get_grid_location(void);
void get_map(void);
void update_map(void);

extern uint8_t walls[MAZE_SIZE][MAZE_SIZE];

#endif
