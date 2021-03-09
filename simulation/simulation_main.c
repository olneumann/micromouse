//
// Created by root on 3/2/21.
//

#include "simulation_main.h"

void init_simulation(){
    srand(time(NULL));

}
int main() {
    state mouse_state = get_mouse_state();
    printf("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);

    init_walls();
    init_visited_cells();
    print_visited_cells();
    set_the_map();
    init_simulation();
    run_algo();
    return 0;
}