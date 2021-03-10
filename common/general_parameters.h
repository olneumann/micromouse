//
// Created by root on 2/28/21.
//

#ifndef MM_GENERAL_PARAMETERS_H
#define MM_GENERAL_PARAMETERS_H

// This file includes general parameters of robot mouse

#define DISCOVERY_SIMULATION 1

#define MAZE_SIZE 7

#define NUMBER_GOAL_CELL 4
#define GOAL_CELL_1_X 2
#define GOAL_CELL_1_Y 2

#define GOAL_CELL_3_X 4
#define GOAL_CELL_2_Y 2
#define GOAL_CELL_3_Y 2
#define GOAL_CELL_4_X 4
#define GOAL_CELL_2_X 3
#define GOAL_CELL_4_Y 3

#define START_POSITION_X 0
#define START_POSITION_Y 0
#define START_DIRECTION North


#define ROBOT_SIZE_X 14.5 // cm ---->x     ^
#define ROBOT_SIZE_Y 9 // cm          | y
#define ROBOT_SIZE_Z 10000000

#define A_WALL_THICKNESS 1.2 // cm
#define A_CELL_SIZE 18. //cm
#define A_WALL_PLUS_A_CELL_SIZE (A_WALL_THICKNESS + A_CELL_SIZE)
#define IS_THAT_A_WALL_THRESHOLD A_CELL_SIZE

#define FRONT_MARGIN_BTW_MOUSE_AND_WALL (A_CELL_SIZE-ROBOT_SIZE_X)
#define SIDE_MARGIN_BTW_MOUSE_AND_WALL (A_CELL_SIZE-ROBOT_SIZE_Y)
#define SENSOR_SIDE_LEFT_ID 0
#define SENSOR_SIDE_RIGHT_ID 1
#define SENSOR_FRONT_ID 2
#define NUM_SENSOR 3


#endif //MM_GENERAL_PARAMETERS_H