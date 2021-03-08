//
// Created by root on 3/7/21.
//

#include "simulation_maps.h"

void set_the_map(void) { // 5v5

    set_a_wall(2, 1);
    set_a_wall(5, 2);
    set_a_wall(7, 2);
    set_a_wall(2, 3);
    set_a_wall(8, 3);
    set_a_wall(3, 4);
    set_a_wall(7, 4);
    set_a_wall(4, 5);
    set_a_wall(6, 5);
    set_a_wall(8, 5);
    set_a_wall(3, 6);
    set_a_wall(5, 6);
    set_a_wall(2, 7);
    set_a_wall(6, 7);
    set_a_wall(8, 7);
    set_a_wall(3, 8);
    set_a_wall(5, 8);

}

void set_the_map_2(void) { //7v7

    set_walls_along_x(2, 3, 1, 5, 9);
    set_walls_along_x(3, 6, 2, 4, 6, 8, 10, 12);
    //set_a_wall(2, 13);
    set_walls_along_x(4, 1, 7);
    set_walls_along_x(5, 4, 2, 4, 10, 12);
    set_walls_along_x(6, 4, 3, 5, 7, 11);
    set_walls_along_x(7, 3, 4, 8, 12);
    set_walls_along_x(8, 1, 9);
    set_walls_along_x(9, 4, 2, 4, 10, 12);
    set_walls_along_x(10, 4, 3, 5, 7, 11);
    set_walls_along_x(11, 1, 8);
    set_walls_along_x(12, 5, 3, 5, 7, 9, 11);

}
