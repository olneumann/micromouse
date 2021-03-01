#ifndef MANAGER_H
#define MANAGER_H

#include "map_updater.h"
#include "solver.h"
#include "actions.h"
#include "pid.h"
#include "logger.h"

#include "general_parameters.h"
#include "general_definitions.h"

typedef enum {
    West = 0, East = 1, South = 2, North = 3,
    Southwest = 4, Southeast = 5, Northwest = 6, Northeast = 7
} orientation;
typedef struct {
    uint8_t x;
    uint8_t y;
    orientation o;
} position;

typedef struct {
    bool front;
    bool left;
    bool right;
    bool back;
} walls_around_t;

typedef enum {
    Normal = 0, Fast = 1, BlindlyFast = 2
} inference_mode;

void init_manager(void);

void start_inference(void);

void do_inference(inference_mode);

void do_discovery(void);

void start_discovery(void);

Action *decide_next_action(void);

void start_action(Action *);

#endif //MANAGER_H
