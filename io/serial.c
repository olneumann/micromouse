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
#include "../drivers/serial_i2c.h"
#include "../drivers/serial_uart.h"
#include "../drivers/serial_uart_rn4871.h"

#include "serial.h"

void serialInit(void) 
{
    /* UART setup
     * Initialize UART to [BAUD] 115200
     */ 
    uart_config_t uartConf;
    uartConf.fcy = FCY;
    uartConf.baud = 115200;
    
    if (uartInit(&uartConf) != 0) {
        while (1);
    }
    
    /* I2C setup
     * Initialize I2C to [FSCL] 200kHz 
     */ 
    i2c_config_t i2cConf;
    i2cConf.fcy = FCY;
    i2cConf.fscl = 200000;
    i2cConf.fdelay = 8333333;

    if (i2cInit(&i2cConf) != 0) {
        while (1);
    }
    
    /* Bluetooth setup 
     */
    if (bluetoothInit() != 0) {
        while (1);
    }
}

