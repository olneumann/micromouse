//
// Created by root on 3/2/21.
//


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
        printf("\n");
        for (i = 0; i < MAZE_SIZE; i++) {
            printf("%d ", visited_cells[i][j]);
        }
    }
    printf("\n");

}

position get_the_cell_by_the_wall_related_to_mouse_orientation(position wall) {
    state mouse_state = get_mouse_state();
    uint8_t mouse_x = mouse_state.p.x * 2 + 1, mouse_y = mouse_state.p.y * 2 + 1, wall_x = wall.x, wall_y = wall.y;
    position cell;
    printf(" mouse  in maze coordinate space ==> (%d, %d)\n", mouse_x, mouse_y);

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
    printf(" get cell by wall ==> (%d, %d)\n", cell.x, cell.y);

    return cell;
}

direction get_direction_btw_start_and_end_cells(position start, position end) {
    printf(" get_direction ==> (%d, %d,) ( %d %d) \n", start.x, start.y, end.x, end.y);

    if (start.x > end.x && start.y == end.y) {
        return West;
    } else if (start.x < end.x && start.y == end.y) {
        return East;
    } else if (start.x == end.x && start.y < end.y) {
        return North;
    } else if (start.x == end.x && start.y > end.y) {
        return South;
    } else if (start.x == end.x && start.y == end.y) {
        return get_mouse_state().d;
    } else return -1;
}

position get_the_most_distant_cell_for_2_walls(position r_wall, position l_wall) {
    u_int8_t ultimate_visits = 255;
    position the_cell, r_cell, l_cell;
    u_int8_t visits;

    r_cell = get_the_cell_by_the_wall_related_to_mouse_orientation(r_wall);
    printf(" l_cell ==> (%d, %d) \n", r_cell.x, r_cell.y);
    visits = get_visits(r_cell);
    if (visits < ultimate_visits) {
        ultimate_visits = visits;
        the_cell = r_cell;
    }

    l_cell = get_the_cell_by_the_wall_related_to_mouse_orientation(l_wall);
    printf(" l_cell ==> (%d, %d) \n", l_cell.x, l_cell.y);
    visits = get_visits(l_cell);
    if (visits < ultimate_visits) {
        ultimate_visits = visits;
        the_cell = l_cell;
    }
    printf(" a cell to go ==> (%d, %d) \n", the_cell.x, the_cell.y);
    return the_cell;
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
    printf("is visited (%d, %d )\n", cell.x, cell.y);

    return visited_cells[cell.x][cell.y];
}

void set_visited(position cell) {
    visited_cells[cell.x][cell.y] += 1;

}


void print_missions(mission *mission_tail) {
    mission *parent;

    printf("missions : ");

    while (mission_tail) {
        printf(" to direction %d from (%d, %d) <<=", mission_tail->d, mission_tail->start.x,
               mission_tail->start.y);
        mission_tail = mission_tail->parent;
    }
    printf("\n");
}


void turn_towards_the_direction(direction d) {
    printf("turn towards %d\n",d);
    turn_towards(d);
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
    u_int8_t step;
    print_missions(current_mission);
    printf("\nmission to direction %d from (%d, %d) \n\n",
           current_mission->d,
           current_mission->start.x,
           current_mission->start.y);
    printf("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
    turn_towards_the_direction(current_mission->d);
    mouse_walls_around = reset_around_walls();

    while (!mouse_walls_around.front) {
        printf(" -----------------------\n");
        previous_mouse_state = mouse_state;
        move_to_one_cell_in_direction(current_mission->d);
        shorten_the_path_for_current_cell(previous_mouse_state);
        mouse_state = get_mouse_state();
        printf("move to 1 (%d, %d )\n", mouse_state.p.x, mouse_state.p.y);

        if (get_visits(mouse_state.p)) {
            printf("cell  (%d, %d ) is already visited\n", mouse_state.p.x, mouse_state.p.y);
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
            printf("mission %d to direction %d from (%d,%d)  is added to mission : to direction %d  from (%d,%d) \n",
                   current_mission->number_of_fork_missions + 1,
                   found_mission_fork->d,
                   found_mission_fork->start.x, found_mission_fork->start.y,
                   current_mission->d,
                   current_mission->start.x, current_mission->start.y
            );
        } else {
            printf("no mission on right !\n");
        }
        if (!mouse_walls_around.left) {
            found_mission_fork = add_a_mission(current_mission, Left_Sensor);
            current_mission->fork_missions[current_mission->number_of_fork_missions] = found_mission_fork;
            current_mission->number_of_fork_missions++;
            printf("mission %d to direction %d from (%d,%d)  is added to mission : to direction %d  from (%d,%d) \n",
                   current_mission->number_of_fork_missions + 1,
                   found_mission_fork->d,
                   found_mission_fork->start.x, found_mission_fork->start.y,
                   current_mission->d,
                   current_mission->start.x, current_mission->start.y
            );
        } else {
            printf("no mission on left !\n");

        }


        printf(" --------------end of a step -----------------------\n");
        print_visited_cells();
        if (step++ == 6)exit(0);
    }

    printf(" --------------end of a mission -----------------------\n");
    printf(" --------------start of fork missions -----------------------\n");

    process_fork_missions(current_mission);
    printf(" --------------end of fork missions -----------------------\n");
    free(current_mission);
}

void convert_to_an_undo_mission(mission *mission_to_undo) {
    state mouse_state = get_mouse_state();
    printf("\nundo a mission to direction %d from (%d, %d) \n\n",
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
    printf("%d fork missions \n", mission_to_fork->number_of_fork_missions);

    if (mission_to_fork->number_of_fork_missions) {
        for (fork_mission_index = mission_to_fork->number_of_fork_missions - 1;
             fork_mission_index >= 0; fork_mission_index--) {

            fork_mission = mission_to_fork->fork_missions[fork_mission_index];

            number_of_steps = manhattan_distance_uint16_t(get_mouse_state().p, fork_mission->start);

            printf(" -----------preparation of a fork mission------------\n");

            for (step = 0; step < number_of_steps; step++) { // move to the start position of the fork mission
                move_to_one_cell_in_direction(mission_to_fork->d);
                mouse_state = get_mouse_state();
                printf("move to 2 (%d, %d ) ultimate target is (%d,%d) \n", mouse_state.p.x, mouse_state.p.y,
                       fork_mission->start.x, fork_mission->start.y);
                set_visited(mouse_state.p);
            }

            printf(" -----------start of a fork mission------------\n");
            printf("\nfork mission to direction %d from (%d, %d)\n", fork_mission->d, fork_mission->start.x,
                   fork_mission->start.y);

            process_fork_mission(fork_mission);

            printf(" --------------end of a fork mission -----------------------\n");
        }
    }

    printf(" -----------complete the undo mission after %d  fork missions direction %d from (%d, %d) ------------\n",
           number_of_steps, mission_to_fork->d, mission_to_fork->start.x,
           mission_to_fork->start.y);
    turn_towards_the_direction(mission_to_fork->d);
    mouse_walls_around = reset_around_walls();
    while (!mouse_walls_around.front) { // move to the start position of the fork mission
        move_to_one_cell_in_direction(mission_to_fork->d);
        mouse_state = get_mouse_state();
        printf("move to 3 (%d, %d )\n", mouse_state.p.x, mouse_state.p.y);
        set_visited(mouse_state.p);
        mouse_walls_around = reset_around_walls();
    }
    printf(" -----------completed undo mission------------\n");

}

mission *add_a_mission(mission *parent, ranging_sensor sensor) {//search for undo missions

    mission *mission = NULL;

    state mouse_state = get_mouse_state();

    direction sight_direction = get_sight_direction_of_sensor(sensor);

    mission = create_a_mission(parent, sight_direction, mouse_state.p);
    printf(" found possible_next_cell ==> (%d, %d, direction: %d) \n", mouse_state.p.x, mouse_state.p.y,
           sight_direction);

    return mission;
}


void run_algo(void) {
    mission *first_mission = create_a_mission(NULL, get_mouse_state().d, get_mouse_state().p);
    set_visited(get_mouse_state().p);
    process_mission(first_mission);
    print_visited_cells();
    print_dijkstra_distances();
    print_shortest_path();
}
