//
// Created by root on 3/9/21.
//

#ifndef MM_SHORTEST_PATH_H
#define MM_SHORTEST_PATH_H
#include "manager.h"

#define MAX_DIJKSTRA_DISTANCE MAZE_SIZE // will be used in the discovery
extern position previous_cells[MAZE_SIZE][MAZE_SIZE];
extern uint32_t dijkstra_distances[MAZE_SIZE][MAZE_SIZE];

void init_shortest_path_utils();
void shorten_the_path_for_current_cell(state);

void print_shortest_path(void);
void print_dijkstra_distances(void);
#endif //MM_SHORTEST_PATH_H
