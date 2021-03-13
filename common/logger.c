/* 
 * File:   logger.h
 * Author: yigit
 *
 * Created on January 25, 2021, 12:59 AM
 */

#include "logger.h"


logger_t logger;

/**
 * logger debug function
 * @param str log message
 * @return 1 if success
 */
int debug_func(const char *format, ...) {
    char buffer[256];
    int l = (int) strlen(format) + 8;
    char log_format[l];
    sprintf(log_format, "DEBUG : %s", format);
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 255, log_format, args);
    va_end(args);
#if (RUNNING_ON_MICROPROCESSOR)
    return uartWrite(buffer,0);
#else
    return printf("%s", buffer);
#endif

}

/**
 * logger error function
 * @param str log message
 * @return 1 if success
 */
int error_func(const char *format, ...) {
    char buffer[256];
    int l = (int) strlen(format) + 8;
    char log_format[l];
    sprintf(log_format, "ERROR : %s", format);
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 255, log_format, args);
    va_end(args);
#if (RUNNING_ON_MICROPROCESSOR)
    return uartWrite(buffer,0);
#else
    return printf("%s", buffer);
#endif
}

/**
 * logger info function
 * @param str log message
 * @return 1 if success
 */
int info_func(const char *format, ...) {

    char buffer[256];
    //int l = (int) strlen(format) + 8;
    //char log_format[l];
    //sprintf(log_format, "INFO : %s", format);
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 255, format, args);
    va_end(args);
#if (RUNNING_ON_MICROPROCESSOR)
    return uartWrite(buffer,0);
#else
    return printf("%s", buffer);
#endif
}

/**
 * logger warning function
 * @param str log message
 * @return 1 if success
 */
int warning_func(const char *format, ...) {
    char buffer[256];
    int l = (int) strlen(format) + 8;
    char log_format[l];
    sprintf(log_format, "WARNING : %s", format);
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 255, log_format, args);
    va_end(args);
#if (RUNNING_ON_MICROPROCESSOR)
    return uartWrite(buffer,0);
#else
    return printf("%s", buffer);
#endif
}

void loggerInit() {

    logger.debug = debug_func;
    logger.warning = warning_func;
    logger.error = error_func;
    logger.info = info_func;

}