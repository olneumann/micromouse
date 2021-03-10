//
// Created by root on 3/9/21.
//

#include "shortest_path.h"

uint8_t straight_forward_chain_distance = MAX_DIJKSTRA_DISTANCE;
position previous_cells[MAZE_SIZE][MAZE_SIZE];
uint32_t dijkstra_distances[MAZE_SIZE][MAZE_SIZE];

void init_shortest_path_utils() {
    int i, j;
    state mouse_state = get_mouse_state();
    for (i = 0; i < MAZE_WALL_SIZE; i++) {
        for (j = 0; j < MAZE_WALL_SIZE; j++) {
            previous_cells[i][j] = (position) {-1, -1};
            dijkstra_distances[i][j] = UINT32_MAX;
        }
    }
    dijkstra_distances[mouse_state.p.x][mouse_state.p.y] = MAX_DIJKSTRA_DISTANCE;
}

void shorten_the_path_for_current_cell(state previous_mouse_state) {
    state mouse_state = get_mouse_state();
    position previous_cell = previous_mouse_state.p;
    position current_cell = mouse_state.p;
    uint32_t dijkstra_distance;
    if (previous_mouse_state.d != mouse_state.d) { // this provides dynamics weights for dijkstra algorithm
        dijkstra_distance = dijkstra_distances[previous_cell.x][previous_cell.y] + MAX_DIJKSTRA_DISTANCE;
        straight_forward_chain_distance = MAX_DIJKSTRA_DISTANCE;

    }
    else{
        dijkstra_distance = dijkstra_distances[previous_cell.x][previous_cell.y] + straight_forward_chain_distance;
        straight_forward_chain_distance--;
    }
    if (dijkstra_distances[current_cell.x][current_cell.y] > dijkstra_distance){
        dijkstra_distances[current_cell.x][current_cell.y] = dijkstra_distance;
        previous_cells[current_cell.x][current_cell.y] = previous_cell;
    }
}
void print_dijkstra_distances(void){
    int i, j;
    for (j = MAZE_SIZE-1; j >=0; j--) {
        printf("\n");
        for (i = 0; i < MAZE_SIZE; i++) {
            if (dijkstra_distances[i][j]==UINT32_MAX){
                printf("00 ");
            }
            else{
                printf("%d ",dijkstra_distances[i][j]);
            }
        }
    }
    printf("\n");
}
void print_shortest_path(void){
    position the_found_goal_cell, goal_cell, state_cell= get_start_cell(), proceeding_cell;
    int i;
    uint32_t max_local_dijkstra_distance = UINT32_MAX, dijkstra_distance;
    for(i=0;i<NUMBER_GOAL_CELL;i++){
        goal_cell = goal_cells[i];
        dijkstra_distance = dijkstra_distances[goal_cell.x][goal_cell.y];
        if(dijkstra_distance < max_local_dijkstra_distance){
            the_found_goal_cell = goal_cell;
            max_local_dijkstra_distance = dijkstra_distance;
        }
    }
    proceeding_cell = the_found_goal_cell;
    printf("Found goal : (%d, %d)",the_found_goal_cell.x,the_found_goal_cell.y);

    while(!is_cells_the_same(state_cell,proceeding_cell)){
        proceeding_cell = previous_cells[proceeding_cell.x][proceeding_cell.y];
        printf("<-- (%d, %d) ",proceeding_cell.x,proceeding_cell.y);
    }
    printf("\n");

}