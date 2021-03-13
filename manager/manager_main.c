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
int manager_main() {
    init_manager();
    start_discovery();
    return 0;
}