#include "map_updater.h"
#include <stdio.h>
#include <stdarg.h>
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
bool is_wall(uint8_t x, uint8_t y){
    return walls[x][y];
}
void set_a_wall(uint8_t x, uint8_t y){
    walls[x][y] = 1;
}
void set_a_wall_along_x(uint8_t x,int wall_count,...){
    va_list ap;
    int i, y;
    va_start (ap, wall_count);         /* Initialize the argument list. */

    for (i = 0; i < wall_count; i++){
        y = (uint8_t) va_arg (ap, int);
        set_a_wall(x, y);
    }
    va_end (ap);
}
void set_a_wall_along_y(uint8_t y, int wall_count,...){
    va_list ap;
    int i, x;
    va_start (ap, wall_count);         /* Initialize the argument list. */

    for (i = 0; i < wall_count; i++){
        x = (uint8_t) va_arg (ap, int);
        set_a_wall(y, x);
    }
    va_end (ap);
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
