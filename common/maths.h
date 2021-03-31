/* 
 * File:   maths.h
 * Author: oliver
 *
 * Created on 4. Januar 2021, 15:11
 */

#ifndef MATHS_H
#define	MATHS_H

#define M_PI (float)3.14159

#define MIN(a,b) \
  __extension__ ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b; })
#define MAX(a,b) \
  __extension__ ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; })
#define ABS(x) \
  __extension__ ({ __typeof__ (x) _x = (x); \
  _x > 0 ? _x : -_x; })

static inline int constrain(int amt, int low, int high)
{
    if (amt < low)
        return low;
    else if (amt > high)
        return high;
    else
        return amt;
}

static inline float constrainf(float amt, float low, float high)
{
    if (amt < low)
        return low;
    else if (amt > high)
        return high;
    else
        return amt;
}

#endif /* MATHS_H */