/* 
 * File:   logger.h
 * Author: yigit
 *
 * Created on January 25, 2021, 12:58 AM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "__logger__.h"
#include "../drivers/serial_uart.h"
/**
 * init a logger and return it
 * @return logger struct
 */
void loggerInit();
extern logger_t logger;

#ifdef	__cplusplus
}
#endif

#endif	/* LOGGER_H */

