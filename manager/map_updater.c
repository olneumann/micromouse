#include "map_updater.h"


void init_walls(void) {
    int i,j;
    for (i = 0; i < MAZE_SIZE; i++) {
        for (j = 0; j < MAZE_SIZE; j++) {
            if (i % 2 == 0 && j == MAZE_SIZE-1) {
                walls[i][j] =-1;
            } else {
                walls[i][j] = 0;
            }
        }
    }
}
