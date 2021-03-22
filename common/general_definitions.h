//
// Created by root on 2/28/21.
//

#ifndef MM_GENERAL_DEFINITIONS_H
#define MM_GENERAL_DEFINITIONS_H

#include <stdint.h>
#include "stdbool.h"
#define radians float

#define True 1
#define False 0
#define distance double
#define PI 3.1415

typedef enum{
    Front = 0, Right=1, Left=2, Back=3,
} body_direction;

typedef enum {
    West = 0, East = 1, South = 2, North = 3,
    Southwest = 4, Southeast = 5, Northwest = 6, Northeast = 7
} direction;

typedef enum {
    Front_Sensor = 0, Right_Sensor = 1, Left_Sensor = 2,
}ranging_sensor;
typedef struct {
    uint8_t x;
    uint8_t y;
} position;


typedef struct {
    position p;
    direction d;
} state;

typedef struct {
    bool front;
    bool left;
    bool right;
    bool back;
} walls_around_t;


typedef enum {
    Normal = 0, Fast = 1, BlindlyFast = 2
} inference_mode;

#endif //MM_GENERAL_DEFINITIONS_H
