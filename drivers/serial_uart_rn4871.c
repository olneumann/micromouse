/* 
 * File:   serial_uart_rn4871.c
 * Author: oliver
 *
 * Created on 12. Februar 2021, 13:36
 */

#include <stdio.h>
#include <stdlib.h>

#include "../common/defines.h"
#include "../dspic/board.h"
#include "../drivers/serial_uart.h"

#include "serial_uart_rn4871.h"

int bluetoothInit()
{
    int status = -1;
    /*
     * STATUS INDICATION PINS
     * STATUS1      STATUS2     Description
     * High         High        Power On
     * High         Low         Standby state
     * Low          Low         Connection established
     * Low          High        Data session open (Transparent UART)
     * 
     * [P1_2] STATUS1
     * [P1_3] STATUS2
     */
    
    /*
     * To enter Command mode from Data mode, type the $$$ character sequence after a
     * 100 ms delay before the first $. 
     */
    
    uartWrite("$$$\r",5);

    /*
     * Remapping
     */
    
    uartWrite("SW,0A,07\r",5);
    uartWrite("SW,0B,08\r",5);
    uartWrite("---\r",5);
    
    status = 0;
    return status;
}

void setBTmode(bt_mode_t mode)
{
    if (mode == NORMAL)
    {
        /*
         * If the user intends to provide data or commands via UART in the Low-Power mode, 
         * then the UART_RX_IND pin must be pulled low and the user needs 
         * to wait for at least five milliseconds before sending the data. 
         * Pulling the UART_RX_IND pin low resumes the normal operation mode.
         */
        
        UART_RX_IND = 0;
    }
    else if (mode == LOW_POWER)
    {
        /*
         * ASCII command SO,1 for set module in low-power mode.
         * Default UART settings:
         * [BAUD] 115200
         * [BITS] 8
         * [PARITY] None
         * [SBIT] 1
         * [FC] Disabled
         */
        
        uartWrite("$$$\r",5);
        uartWrite("SO,1\r",5);
        uartWrite("---\r",5);
    }
}