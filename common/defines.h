/* 
 * File:   defines.h
 * Author: oliver
 *
 * Created on 9. Dezember 2020, 13:29
 */

#ifndef DEFINES_H
#define	DEFINES_H

#include <stdint.h>
#include <stddef.h>

/* Macro to get the size of an array */
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))
#define DELAY_150uS asm volatile ("REPEAT, #4000"); Nop(); // 150uS delay
#define DELAY_600uS asm volatile ("REPEAT, #16000"); Nop(); // 600uS delay

/* Time setup */
typedef int32_t timeDelta_t;
typedef uint32_t timeUs_t;
#define TIMEUS_MAX UINT32_MAX

static inline timeDelta_t cmpTimeUs(timeUs_t a, timeUs_t b) {return (timeDelta_t)(a - b); }

#endif /* DEFINES_H */