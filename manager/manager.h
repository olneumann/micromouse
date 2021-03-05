#ifndef MANAGER_H
#define MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include "map_updater.h"
//#include "solver.h"
#include "actions.h"
//#include "../common/logger.h"

#include "../common/general_parameters.h"
#include "../common/general_definitions.h"


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
} walls_around;

typedef enum {
    Normal = 0, Fast = 1, BlindlyFast = 2
} inference_mode;

void init_manager(void);

void start_inference(void);

void do_inference(inference_mode);

void do_discovery(void);

void start_discovery(void);

Action *decide_next_action(void);

void start_action(Action*);

state get_mouse_state(void);

position get_start_cell();

position what_is_the_position_after_moving_one_step_in_the_direction(position , direction );

void move_to_one_cell_in_direction(direction);

#endif //MANAGER_H