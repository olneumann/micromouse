/* 
 * File:   serial_uart.h
 * Author: oliver
 *
 * Created on 9. Dezember 2020, 13:29
 */

#ifndef SERIAL_UART_H
#define	SERIAL_UART_H

#include <stdint.h>

typedef struct
{
    uint32_t fcy; 
    uint32_t baud;
} uart_config_t;

int uartInit(uart_config_t *config);
int uartReadC(void);
int uartWriteC(int c);
int uartWrite(const char *str, int delay_ms);

#endif	/* SERIAL_UART_H */
