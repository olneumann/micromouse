/* 
 * File:   __logger__.h
 * Author: root
 *
 * Created on January 25, 2021, 1:44 AM
 */

#ifndef __LOGGER___H
#define	__LOGGER___H

typedef int (*__debug__)(const char * str);
typedef int (*__error__)(const char * str);
typedef int (*__info__)(const char * str);
typedef int (*__warning__)(const char * str);

int debug_func(const char* str);
int error_func(const char* str);
int info_func(const char* str);
int warning_func(const char* str);

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

