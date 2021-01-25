/* 
 * File:   logger.h
 * Author: yigit
 *
 * Created on January 25, 2021, 12:59 AM
 */

#include "__logger__.h"
#include "logger.h"
#include "../drivers/serial_uart.h"
#include <string.h>
#include <stdio.h>

logger_t logger;

/**
 * logger debug function
 * @param str log message
 * @return 1 if success
 */
int debug_func(const char *str){
        
    int l = strlen(str) + 8;
    char log[l];
    sprintf(log, "DEBUG : %s",str);
    
    return uartWrite(log);
    
}
/**
 * logger error function
 * @param str log message
 * @return 1 if success
 */
int error_func(const char *str){
    int l = strlen(str) + 8;
    char log[l];
    sprintf(log, "ERROR : %s", str);
    return uartWrite(log);
}
/**
 * logger info function
 * @param str log message
 * @return 1 if success
 */
int info_func(const char *str){
       
    int l = strlen(str) + 8;
    char log[l];
    sprintf(log, "INFO : %s",str);
    
    return uartWrite(log);
}
/**
 * logger warning function
 * @param str log message
 * @return 1 if success
 */
int warning_func(const char *str){
    int l = strlen(str) + 10;
    char log[l];
    sprintf(log, "WARNING : %s",str);
    return uartWrite(log);
}
void loggerInit(){
    
    logger.debug = debug_func;
    logger.warning = warning_func;
    logger.error = error_func;
    logger.info = info_func;

}