//
// Created by root on 2/28/21.
//

#ifndef MM_GENERAL_DEFINITIONS_H
#define MM_GENERAL_DEFINITIONS_H

#include <stdint.h>

#define radians float

#define True 1
#define False 0
#define distance double
#define PI 3.1415
typedef enum {
    West = 0, East = 1, South = 2, North = 3,
    Southwest = 4, Southeast = 5, Northwest = 6, Northeast = 7

} direction;
typedef enum {
    Front = 0, Right = 1, Left = 2,
}ranging_sensor;

#endif //MM_GENERAL_DEFINITIONS_H
