//
// Created by root on 2/28/21.
//

#ifndef MM_GENERAL_PARAMETERS_H
#define MM_GENERAL_PARAMETERS_H

typedef enum {
    West = 0, East = 1, South = 2, North = 3,
    Southwest = 4, Southeast = 5, Northwest = 6, Northeast = 7
} direction;

// This file includes general parameters of frobot mouse
#define START_POSITION_X 0
#define START_POSITION_Y 0
#define START_DIRECTION North
#define MAZE_SIZE 7
#define SENSOR_SIDE_LEFT_ID 0
#define SENSOR_SIDE_RIGHT_ID 1
#define SENSOR_FRONT_ID 2
#define NUM_SENSOR 3

#endif //MM_GENERAL_PARAMETERS_H