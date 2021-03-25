/*
 * File:   shortest_path.h
 * Author: yigit
 *
 * Created on 2. March 2021, 17:00
 */

#ifndef MM_SHORTEST_PATH_H
#define MM_SHORTEST_PATH_H

#include "../manager/manager_parameters.h"
#include "../manager/manager_definitions.h"
#include "../common/logger.h"
#include "mouse_state.h"
#include "map_updater.h"

#define MAX_DIJKSTRA_DISTANCE MAZE_SIZE // will be used in the discovery

struct path {
    position cell;
    struct path * next;
    struct path * previous;
};
typedef struct path path;

extern position previous_cells[MAZE_SIZE][MAZE_SIZE];
extern uint32_t dijkstra_distances[MAZE_SIZE][MAZE_SIZE];

void init_shortest_path_utils();
path *get_shortest_path();
void shorten_the_path_for_current_cell(state);
position get_the_goal_cell_with_the_shortest_path();
void print_shortest_path(void);
void print_dijkstra_distances(void);

#endif //MM_SHORTEST_PATH_H
