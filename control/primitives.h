/*
 * File:   primitives.h
 * Author: oliver
 *
 * Created on 2. Januar 2021, 17:00
 */

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

typedef enum {
	MOVE_END,
	MOVE_FRONT,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_BACK,
	MOVE_ITEM_COUNT,
} primitives_e;

void move(primitives_e primitive);

#endif /* PRIMITIVES_H */