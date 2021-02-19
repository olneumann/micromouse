#ifndef MANAGER_H
#define	MANAGER_H

#include "map_updater.h"
#include "solver.h"
#include "actions.h"
#include "../control/pid.h"


void init_manager(void);
void do_inference(void);
void do_discovery(void);
void start_discovery(void);
void decide_action(void);
void process_action(void);
