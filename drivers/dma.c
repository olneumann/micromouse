/* 
 * File:   dma.c
 * Author: oliver
 *
 * Created on 18. Dezember 2020, 20:03
 */

#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "dma.h"


unsigned int dma_bufA[32]__attribute__((space(dma)));

void dmaInit(void)
{
    DMA0CONbits.CHEN = 0;           // Channel Enable bit - OFF
    DMA0CONbits.SIZE = 0;           // Data Transfer Size bit
    DMA0CONbits.DIR = 0;            // Transfer Direction bit (source/destination bus select)
    DMA0CONbits.HALF = 0;           // Block Transfer Interrupt Select bit
    DMA0CONbits.NULLW = 1;          // Null Data Peripheral Write Mode Select bit
    DMA0CONbits.AMODE = 0b10;       // DMA Channel Addressing Mode Select bits 
                                    // 11 = Reserved
                                    // 10 = Peripheral Indirect Addressing mode
                                    // 01 = Register Indirect without Post-Increment mode
                                    // 00 = Register Indirect with Post-Increment mode
    DMA0CONbits.MODE = 0b00;        // DMA Channel Operating Mode Select bits
                                    // 11 = One-Shot, Ping-Pong modes enabled (one block transfer from/to each DMA RAM buffer)
                                    // 10 = Continuous, Ping-Pong modes enabled
                                    // 01 = One-Shot, Ping-Pong modes disabled
                                    // 00 = Continuous, Ping-Pong modes disabled
    
    DMA0REQbits.FORCE = 0;          // Force DMA Transfer bit
    DMA0REQbits.IRQSEL = 0b0001101; // DMA Peripheral IRQ Number Select bits (ADC1))
            
    DMA0STA = (__builtin_dmaoffset(&dma_bufA[0]));      // Primary DPSRAM Start Address Offset bits (source or destination)
    DMA0PAD = (volatile unsigned int) &ADC1BUF0;        // Peripheral Address Register bits
    DMA0CNT = 0;                    // -> [TODO!] DMA Transfer Count Register bits 

    IFS0bits.DMA0IF = 0;            // Reset interrupt flag
    IEC0bits.DMA0IE = 0;            // Disable interrupt
    IPC1bits.DMA0IP = 5;            // Priority of interrupt
    
    DMA0CONbits.CHEN = 1;           // Channel Enable bit - ON
}

void __attribute__((__interrupt__,no_auto_psv)) _DMA0Interrupt(void)
{
    /* Clear DMA0 interrupt flag */
    IFS0bits.DMA0IF = 0;
}