/* 
 * File:   bitops.c
 * Author: oliver
 *
 * Created on 20. November 2020, 16:45
 */

#ifndef BITOPS_H
#define	BITOPS_H

int setBit(int x, unsigned char position);
int clearBit(int x, unsigned char position);
int modifyBit(int x, unsigned char position, bool newState);
int flipBit(int x, unsigned char position);
bool isBitSet(int x, unsigned char position);
int setMask(int x, int y);
int clearMask(int x, int y);
int flipMask(int x, int y);

#endif	/* BITOPS_H */


