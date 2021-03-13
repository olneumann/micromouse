/* 
 * File:   __logger__.h
 * Author: root
 *
 * Created on January 25, 2021, 1:44 AM
 */

#ifndef __LOGGER___H
#define	__LOGGER___H
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
typedef int (*__debug__)(const char *,...);
typedef int (*__error__)(const char *,...);
typedef int (*__info__)(const char *,...);
typedef int (*__warning__)(const char *,...);

int debug_func(const char *,...);
int error_func(const char *,...);
int info_func(const char *,...);
int warning_func(const char *,...);

/**
 * \brief logger structure with function parameters
 */
typedef struct {
    __debug__ debug;
    __error__ error;
    __info__ info;
    __warning__ warning;
}logger_t;

#endif

