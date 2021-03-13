//
// Created by root on 3/8/21.
//

#include "manager.h"
int manager_main() {
    loggerInit();
    init_manager();
    start_discovery();
    return 0;
}