//
// Created by root on 3/7/21.
//

#include "simulation_maps.h"
static volatile bool walls[MAZE_WALL_SIZE][MAZE_WALL_SIZE];
bool is_wall(uint8_t x,uint8_t y){
    return walls[x][y];

}
void print_walls(void){
    int i, j;
    for (j = MAZE_WALL_SIZE-1; j >=0; j--) {
        printf("\n");
        for (i = 0; i < MAZE_WALL_SIZE; i++) {
            printf("%d ",walls[i][j]);
        }
    }
    printf("\n");

}

void init_walls(void) {
    int i, j;
    for (i = 0; i < MAZE_WALL_SIZE; i++) {
        for (j = 0; j < MAZE_WALL_SIZE; j++) {
            if (i == 0 || i == MAZE_WALL_SIZE - 1 || j == 0 || j == MAZE_WALL_SIZE - 1) {
                walls[i][j] = 1;
            } else {
                walls[i][j] = 0;
            }
        }
    }
}
void set_a_wall(uint8_t x, uint8_t y){
    walls[x][y] = 1;
}
void set_walls_along_x(uint8_t x, int wall_count, ...){
    va_list ap;
    int i, y;
    va_start (ap, wall_count);         /* Initialize the argument list. */

    for (i = 0; i < wall_count; i++){
        y = (uint8_t) va_arg (ap, int);
        set_a_wall(x, y);
    }
    va_end (ap);
}
void set_walls_along_y(uint8_t y, int wall_count, ...){
    va_list ap;
    int i, x;
    va_start (ap, wall_count);         /* Initialize the argument list. */

    for (i = 0; i < wall_count; i++){
        x = (uint8_t) va_arg (ap, int);
        set_a_wall(x, y);
    }
    va_end (ap);
}
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
