/*
 * File:   discovery.c
 * Author: yigit
 *
 * Created on 2. March 2021, 17:00
 */

#include "discovery.h"

static volatile int8_t visited_cells[MAZE_SIZE][MAZE_SIZE];


void init_visited_cells(void) {
    int i, j;
    for (i = 0; i < MAZE_SIZE; i++) {
        for (j = 0; j < MAZE_SIZE; j++) {
            visited_cells[i][j];
        }
    }
}

void print_visited_cells(void) {
    int i, j;
    for (j = MAZE_SIZE - 1; j >= 0; j--) {
        logger.info("\n");
        for (i = 0; i < MAZE_SIZE; i++) {
            logger.info("%d ", visited_cells[i][j]);
        }
    }
    logger.info("\n");

}


position get_the_cell_by_the_wall_related_to_mouse_orientation(position wall) {
    state mouse_state = get_mouse_state();
    uint8_t mouse_x = mouse_state.p.x * 2 + 1, mouse_y = mouse_state.p.y * 2 + 1, wall_x = wall.x, wall_y = wall.y;
    position cell;
    logger.info(" mouse  in maze coordinate space ==> (%d, %d)\n", mouse_x, mouse_y);

    if (mouse_x > wall_x) {
        cell.y = (wall_y - 1) / 2;
        cell.x = (wall_x) / 2;
    } else if (mouse_x < wall_x) {

        cell.x = (wall_x / 2) - 1;
        cell.y = (wall_y - 1) / 2;

    } else if (mouse_y > wall_y) {

        cell.x = (wall_x - 1) / 2;
        cell.y = (wall_y) / 2;
    } else if (mouse_y < wall_y) {

        cell.y = (wall_y / 2) - 1;
        cell.x = (wall_x - 1) / 2;
    } else {
        cell.x = 255;
        cell.y = 255;
    }
    logger.info(" get cell by wall ==> (%d, %d)\n", cell.x, cell.y);

    return cell;
}
direction get_opposite_direction(direction d) {
    switch (d) {
        case East:
            return West;
        case West:
            return East;
        case North:
            return South;
        case South:
            return North;
        default:
            return -1;
    }
}


mission *create_a_mission(mission *parent, direction d, position start) {
    mission *m = malloc(sizeof(mission));
    m->parent = parent;
    m->start = start;
    m->d = d;
    m->number_of_fork_missions = 0;
    return m;
}


uint8_t get_visits(position cell) {
    logger.info("is visited (%d, %d )\n", cell.x, cell.y);

    return visited_cells[cell.x][cell.y];
}

void set_visited(position cell) {
    visited_cells[cell.x][cell.y] += 1;

}


void print_missions(mission *mission_tail) {

    logger.info("missions : ");

    while (mission_tail) {
        logger.info(" to direction %d from (%d, %d) <<=", mission_tail->d, mission_tail->start.x,
               mission_tail->start.y);
        mission_tail = mission_tail->parent;
    }
    logger.info("\n");
}


bool goal_cell_found(){

    bool is_same = 0;
    position p = get_mouse_state().p;
    is_same |= is_cells_the_same(goal_cells[0],p);
    is_same |= is_cells_the_same(goal_cells[1],p);
    is_same |= is_cells_the_same(goal_cells[2],p);
    is_same |= is_cells_the_same(goal_cells[3],p);
    return is_same;

}
void cheers(){
    position pos = get_mouse_state().p;
    visited_cells[pos.x][pos.y] = -1;
}
void process_mission(mission *current_mission) {
    state mouse_state = get_mouse_state(), previous_mouse_state;
    walls_around_t mouse_walls_around;
    mission *found_mission_fork;
    print_missions(current_mission);
    logger.info("\nmission to direction %d from (%d, %d) \n\n",
           current_mission->d,
           current_mission->start.x,
           current_mission->start.y);
    logger.info("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
    turn_towards(current_mission->d);
    mouse_walls_around = reset_around_walls();
    print_walls_around();
    while (!mouse_walls_around.front) {
        logger.info(" -----------------------\n");
        previous_mouse_state = mouse_state;
        move_one_cell_towards(current_mission->d);
        shorten_the_path_for_current_cell(previous_mouse_state);
        mouse_state = get_mouse_state();
        logger.info("move to 1 (%d, %d )\n", mouse_state.p.x, mouse_state.p.y);

        if (get_visits(mouse_state.p)) {
            logger.info("cell  (%d, %d ) is already visited\n", mouse_state.p.x, mouse_state.p.y);
            break;
        }
        else if(goal_cell_found()){
            cheers();
            break;
        }
        set_visited(get_mouse_state().p);

        mouse_walls_around = reset_around_walls();
        print_walls_around();

        if (!mouse_walls_around.right) {
            found_mission_fork = add_a_mission(current_mission, Right_Sensor);
            current_mission->fork_missions[current_mission->number_of_fork_missions] = found_mission_fork;
            current_mission->number_of_fork_missions++;
            logger.info("mission %d to direction %d from (%d,%d)  is added to mission : to direction %d  from (%d,%d) \n",
                   current_mission->number_of_fork_missions + 1,
                   found_mission_fork->d,
                   found_mission_fork->start.x, found_mission_fork->start.y,
                   current_mission->d,
                   current_mission->start.x, current_mission->start.y
            );
        } else {
            logger.info("no mission on right !\n");
        }
        if (!mouse_walls_around.left) {
            found_mission_fork = add_a_mission(current_mission, Left_Sensor);
            current_mission->fork_missions[current_mission->number_of_fork_missions] = found_mission_fork;
            current_mission->number_of_fork_missions++;
            logger.info("mission %d to direction %d from (%d,%d)  is added to mission : to direction %d  from (%d,%d) \n",
                   current_mission->number_of_fork_missions + 1,
                   found_mission_fork->d,
                   found_mission_fork->start.x, found_mission_fork->start.y,
                   current_mission->d,
                   current_mission->start.x, current_mission->start.y
            );
        } else {
            logger.info("no mission on left !\n");

        }


        logger.info(" --------------end of a step -----------------------\n");
        print_visited_cells();
    }

    logger.info(" --------------end of a mission -----------------------\n");
    logger.info(" --------------start of fork missions -----------------------\n");

    process_fork_missions(current_mission);
    logger.info(" --------------end of fork missions -----------------------\n");
    free(current_mission);
}

void convert_to_an_undo_mission(mission *mission_to_undo) {
    state mouse_state = get_mouse_state();
    logger.info("\nundo a mission to direction %d from (%d, %d) \n\n",
           mission_to_undo->d,
           mission_to_undo->start.x, mission_to_undo->start.y);
    mission_to_undo->d = get_opposite_direction(mission_to_undo->d);
    mission_to_undo->start = mouse_state.p;

}

void process_fork_mission(mission *fork_mission) {

    process_mission(fork_mission);

}

void process_fork_missions(mission *mission_to_fork) {
    mission *fork_mission;
    int8_t fork_mission_index;
    int8_t step, number_of_steps;
    state mouse_state;
    walls_around_t mouse_walls_around;
    convert_to_an_undo_mission(mission_to_fork);
    logger.info("%d fork missions \n", mission_to_fork->number_of_fork_missions);

    if (mission_to_fork->number_of_fork_missions) {
        for (fork_mission_index = mission_to_fork->number_of_fork_missions - 1;
             fork_mission_index >= 0; fork_mission_index--) {

            fork_mission = mission_to_fork->fork_missions[fork_mission_index];

            number_of_steps = manhattan_distance_uint16_t(get_mouse_state().p, fork_mission->start);

            logger.info(" -----------preparation of a fork mission------------\n");

            for (step = 0; step < number_of_steps; step++) { // move to the start position of the fork mission
                move_one_cell_towards(mission_to_fork->d);
                mouse_state = get_mouse_state();
                logger.info("move to 2 (%d, %d ) ultimate target is (%d,%d) \n", mouse_state.p.x, mouse_state.p.y,
                       fork_mission->start.x, fork_mission->start.y);
                set_visited(mouse_state.p);
            }

            logger.info(" -----------start of a fork mission------------\n");
            logger.info("\nfork mission to direction %d from (%d, %d)\n", fork_mission->d, fork_mission->start.x,
                   fork_mission->start.y);

            process_fork_mission(fork_mission);

            logger.info(" --------------end of a fork mission -----------------------\n");
        }
    }

    logger.info(" -----------complete the undo mission after %d  fork missions direction %d from (%d, %d) ------------\n",
           number_of_steps, mission_to_fork->d, mission_to_fork->start.x,
           mission_to_fork->start.y);
    turn_towards(mission_to_fork->d);
    mouse_walls_around = reset_around_walls();
    while (!mouse_walls_around.front) { // move to the start position of the fork mission
        move_one_cell_towards(mission_to_fork->d);
        mouse_state = get_mouse_state();
        logger.info("move to 3 (%d, %d )\n", mouse_state.p.x, mouse_state.p.y);
        set_visited(mouse_state.p);
        mouse_walls_around = reset_around_walls();
    }
    logger.info(" -----------completed undo mission------------\n");

}

mission *add_a_mission(mission *parent, ranging_sensor sensor) {//search for undo missions

    mission *mission = NULL;

    state mouse_state = get_mouse_state();

    direction sight_direction = get_sight_direction_of_sensor(sensor);

    mission = create_a_mission(parent, sight_direction, mouse_state.p);
    logger.info(" found possible_next_cell ==> (%d, %d, direction: %d) \n", mouse_state.p.x, mouse_state.p.y,
           sight_direction);

    return mission;
}


void start_explorer(void) {
    mission *first_mission = create_a_mission(NULL, get_mouse_state().d, get_mouse_state().p);
    set_visited(get_mouse_state().p);
    process_mission(first_mission);
    print_visited_cells();
    print_dijkstra_distances();
    print_shortest_path();
}
