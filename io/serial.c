/* 
 * File:   serial.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 10:22
 */

#include <stdio.h>
#include <stdlib.h>

#include "../dspic/board.h"
#include "../common/defines.h"
#include "../drivers/serial_uart.h"
#include "../drivers/serial_uart_rn4871.h"

#include "serial.h"

void serialInit(void) 
{
    /* UART setup
     * Initialize UART to 115200 baud
     */ 
    uart_config_t config;
    config.fcy = FCY;
    config.baud = 115200;
    
    if (uartInit(&config) != 0) {
        while (1);
    }
    
    /* Bluetooth setup 
     */
    if (bluetoothInit() != 0) {
        while (1);
    }
}

