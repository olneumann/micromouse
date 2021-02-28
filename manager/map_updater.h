#ifndef MAP_UPDATER_H
#define	MAP_UPDATER_H

#include "manager.h"
#include "../sensors/ranging.h"

void init_map(void);
void get_grid_location(void);
void get_map(void);
void update_map(void);

typedef struct {

}Map;

#endif
