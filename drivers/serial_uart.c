/* 
 * File:   serial_uart.c
 * Author: oliver
 *
 * Created on 9. Dezember 2020, 13:29
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "../common/defines.h"
#include "../common/ring_buffer.h"
#include "../dspic/board.h"
#include "../io/hmi.h"

#define _XTAL_FREQ FOSC
#include <libpic30.h>

#include "serial_uart.h"

#define HMI 1   // read commands via uart

static char rbmem[16];
static rbd_t rbd;
static rb_attr_t attr = {sizeof(rbmem[0]), ARRAY_SIZE(rbmem), rbmem};

int uartInit(uart_config_t *config)
{
    int status = -1;
    
    U1MODEbits.UARTEN = 0;              // Disable for config
    U1MODEbits.STSEL = 0;               // 1-stop bit
    U1MODEbits.ABAUD = 0;               // Auto-Baud disabled
    U1MODEbits.BRGH = 0;                // Standard-Speed mode
            
    U1BRG = (config->fcy/config->baud)/16 - 1; // Baud Rate setting
    
    U1STAbits.URXISEL = 0;              // Interrupt after one RX character is received

    IFS0bits.U1RXIF = 0;                // RX reset flag
    IPC2bits.U1RXIP = 4;                // RX interrupt priority
    IEC0bits.U1RXIE = 1;                // RX interrupt enabled
    
    IFS0bits.U1TXIF = 0;                // TX reset flag
    IPC3bits.U1TXIP = 4;                // TX interrupt priority
    IEC0bits.U1TXIE = 0;                // TX interrupt (not) enabled
    
    if (ring_buffer_init(&rbd, &attr) == 0) { 
        U1MODEbits.UARTEN = 1;              // Enable UART
        U1STAbits.UTXEN = 1;                // UART1 TX is enabled (after UARTEN set)
        status = 0;
    }
    
    return status;
}

int uartReadC(void)
{
    int retval = -1;
    char c = -1;
    
    if (ring_buffer_get(rbd, &c) == 0) {
        retval = (int) c;
    }

    return retval;
}

int uartWriteC(int c)
{
    /* Wait for the transmit buffer to be ready */
    while (!U1STAbits.TRMT);
    /* Transmit data */
    U1TXREG = (char) c; 
    
    return 0;
}

int uartWrite(const char *str, int delay_ms)
{
    int status = -1;

    if (str != NULL) {
        status = 0;

        while (*str != '\0') {
            /* Wait for the transmit buffer to be ready */
            while (!U1STAbits.TRMT);
            /* Transmit data */
            U1TXREG = *str; 
            __delay_ms(delay_ms);
            str++;
        }
    }

    return status;
}

int uartCMD(void)
{
    int status = -1;

    int val = -1;
    sscanf(rbmem, "<%d>", &val);
    
    if (val >= 0 && val <= 100)
    {
        char str[30];
        sprintf(str, "OK: pulseWidth = <%d>\n", val);
        uartWrite(str,0);
    }
    else
    {
        uartWrite("ERROR!\n",0);
    }
    
    status = 0;
    return status;
}

void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt(void)
{
     /* Clear the interrupt flag */
    IFS0bits.U1RXIF = 0;
    
    if(U1STAbits.URXDA == 1)            // data in buffer available
    {
        const char c = U1RXREG;
        ring_buffer_put(rbd, &c);  
                
        // Format of commands: ![CMD]<val> 
        if (HMI && c == '!') 
        {
            ring_buffer_flush(0, &rbd);
        }
        else if (HMI && c == '>')       // wait till '>' end of key-value
        {
            char cmd[3];
            int val;
            sscanf(rbmem, "%3s,<%d>", cmd, &val);
            
            userCommand(cmd, &val);
        }
    }
    
    /* Must clear the overrun error to keep UART receiving */
    if(U1STAbits.OERR == 1)
    {
        U1STAbits.OERR = 0;
    }
}

void __attribute__((__interrupt__,no_auto_psv)) _U1TXInterrupt(void)
{
    // usually not needed..
}