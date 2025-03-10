/*
 * File:   manager.c
 * Author: yigit
 *
 * Created on 2. March 2021, 17:00
 */

#include "discovery.h"
#include "manager.h"

void initManager() 
{
    state mouse_state = get_mouse_state();
    logger.info("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
}

void start_discovery() {
    init_shortest_path_utils();
    
#if (DISCOVERY_SIMULATION==1)
    simulation_main();
#else
    start_explorer();
#endif
}

void start_inference() {
    init_finisher();
    start_finisher();
}