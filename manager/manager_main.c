//
// Created by root on 3/8/21.
//
#include "../common/general_parameters.h"
#include "../common/general_definitions.h"
#include "manager.h"
#include "discovery.h"
#include "map_updater.h"
#include "shortest_path.h"

#define MANAGER_MAIN
int main() {
    state mouse_state = get_mouse_state();
    printf("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
    init_walls();
    init_shortest_path_utils();
    init_visited_cells();
    print_visited_cells();
    //set_the_map();
    //init_simulation();
    run_algo();
    return 0;
}