//
// Created by root on 3/2/21.
//

#include "simulation_main.h"

void init_simulation(){
    srand(time(NULL));

}
int simulation_main() {
    state mouse_state = get_mouse_state();
    printf("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);

    init_walls();
    init_visited_cells();
    init_shortest_path_utils();
    print_visited_cells();
    set_the_map_2();
    init_simulation();
    start_explorer();
    return 0;
}