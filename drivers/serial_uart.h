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

/**
 * \brief Initialize the UART peripheral
 * \param[in] config - the UART configuration
 * \return 0 on success, -1 otherwise
 */
int uartInit(uart_config_t *config);

/**
 * \brief Read a character from UART
 * \return the character read on success, -1 if nothing was read
 */
int uartReadC(void);

/**
 * \brief Write a character to UART
 * \param[in] c - the character to write
 * \return 0 on sucess, -1 otherwise
 */
int uartWriteC(int c);

/**
 * \brief Write a string to UART
 * \return 0 on sucesss, -1 otherwise
 */
int uartWrite(const char *str);

/**
 * \brief Parses ring buffer for commands
 * \return 0 on sucesss, -1 otherwise
 * Format of commands: !<val> 
 */
int uartCMD(void);

#endif	/* SERIAL_UART_H */
