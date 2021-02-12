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

#include "serial_uart.h"
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
    
    // TODO: Check <cr> == \n?
    
    uartWrite("$$$\n");
    DELAY_600uS;
    uartWrite("SW,0A,07\n");
    DELAY_600uS;
    uartWrite("SW,0B,08\n");
    DELAY_600uS;
    uartWrite("---\n");
    
    // TODO: Response check? ERR/AOK?
    
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
         * Pulling the UART_RX_IND pin low allows the
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
        
        // TODO: Check <cr> == \n?
        
        uartWrite("$$$\n");
        DELAY_600uS;
        uartWrite("SO,1\n");
        DELAY_600uS;
        uartWrite("---\n");
    }
}