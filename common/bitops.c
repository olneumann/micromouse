/* 
 * File:   bitops.c
 * Author: oliver
 *
 * Created on 2. Dezember 2020, 18:10
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int setBit(int x, unsigned char position)
{
  int mask = 1 << position;
  return x | mask;
}

int clearBit(int x, unsigned char position)
{
  int mask = 1 << position;
  return x & ~mask;
}

int modifyBit(int x, unsigned char position, bool newState)
{
  int mask = 1 << position;
  int state = (int)newState; // relies on true = 1 and false = 0
  return (x & ~mask) | (-state & mask);
}

int flipBit(int x, unsigned char position)
{
  int mask = 1 << position;
  return x ^ mask;
}

bool isBitSet(int x, unsigned char position)
{
  x >>= position;
  return (x & 1) != 0;
}

int setMask(int x, int y)
{
    return ((x) |= (y));
}

int clearMask(int x, int y)
{
    return ((x) &= (~(y)));
}

int flipMask(int x, int y)
{
    return ((x) ^= (y));
}
