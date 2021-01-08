/*
 * File:   adc.c
 * Author: oliver
 *
 * Created on 17. Dezember 2020, 10:31
 */

#include "xc.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "adc.h"

void adcInit(void)
{
    /* DESCRIPTION
    The ADxCON1, ADxCON2 and ADxCON3 registers control the operation of the ADC module.
    The ADxCON4 register sets up the number of conversion results stored in a DMA buffer for each
    analog input in the Scatter/Gather mode for devices with DMA. The ADxCHS123 and ADxCHS0
    registers select the input pins to be connected to the S&H amplifiers. The ADCSSH/L registers
    select inputs to be sequentially scanned. The ADxPCFGH/L registers configure the analog input
    pins as analog inputs or as digital I/O.
     */
    
    AD1CON1bits.ADON = 0;           // Operating Mode bit - OFF
    AD1CON1bits.SIMSAM = 1;         // Simultaneous Sample Select bit (if 1 only 10 bit operation)
    AD1CON1bits.FORM = 0b00;        // Data Output Format bits
                                    // For 12-bit operation:
                                    // 11 = Signed fractional (D OUT = sddd dddd dddd 0000, where s = sign, d = data)
                                    // 10 = Fractional (D OUT = dddd dddd dddd 0000)
                                    // 01 = Signed Integer (D OUT = ssss sddd dddd dddd, where s = sign, d = data)
                                    // 00 = Integer (D OUT = 0000 dddd dddd dddd)
    AD1CON1bits.ADDMABM = 1;        // DMA Buffer Build Mode bit
    AD1CON1bits.AD12B = 0;          // 10-bit or 12-bit Operation Mode bit 
    
    AD1CON1bits.SSRC = 0b111;       // Sample Clock Source Select bits (Internal counter ends sampling and starts conversion (auto-convert))
    AD1CON1bits.SAMP = 1;           // ADC Sample Enable bit
    AD1CON1bits.ASAM = 1;           // ADC Sample Auto-Start bit
        
    AD1CON2bits.CSCNA = 1;          // Input Scan Select bit
    AD1CON2bits.CHPS = 0b11;        // Channel Select bits (CH0)
    AD1CON2bits.SMPI = 0b0000;      // -> [TODO!] Sample and Conversion Operation bits
                                    // 1111 = Increments the DMA address after completion of every 16th sample/conversion operation
                                    // 1110 = Increments the DMA address after completion of every 15th sample/conversion operation
                                    // xxxx
                                    // 0001 = Increments the DMA address after completion of every 2nd sample/conversion operation
                                    // 0000 = Increments the DMA address after completion of every sample/conversion operation
    AD1CON2bits.ALTS = 0;           // Alternate Input Sample Mode Select bit
    AD1CON2bits.BUFM = 0;           // Buffer Fill Mode Select bit
    AD1CON2bits.VCFG = 0b000;       // Converter Voltage Reference Configuration bits (AVDD | AVSS)
    
    AD1CON3bits.ADRC = 0;           // ADC Conversion Clock Source bit (ADC Internal RC Clock)
    AD1CON3bits.ADCS = 0b111111;    // -> [TODO!] ADC Conversion Clock Select bits (64*TCY)
    AD1CON3bits.SAMC = 0b11111;     // -> [TODO!]Auto Sample Time bits (31 TAD)
    
    AD1CHS0bits.CH0NA = 0;          // Channel 0 Negative Input Select for Sample A bit (0: VREFL, 1: AN1)
    AD1CHS0bits.CH0SA = 0b0000;     // Channel 0 Positive Input Select for Sample A bits (pos input: AN0)
    
    //AD1CSSLbits.CSS0 = 1;           // -> [TODO!] ADC Input Scan Selection bits (AN0)
    AD1CSSLbits.CSS5 = 1;           // -> [TODO!] ADC Input Scan Selection bits (AN5)
    
    AD1CHS123bits.CH123NA = 0b00;   // Channel 1, 2, 3 Negative Input Select for Sample A bits (VREFL))
    AD1CHS123bits.CH123SA = 0b1;    // Channel 1, 2, 3 Positive Input Select for Sample A bit
    
    IFS0bits.AD1IF = 0;             // Clear the Analog-to-Digital interrupt flag bit
    IPC3bits.AD1IP = 5;             // AD1 priority bit
    IEC0bits.AD1IE = 0;             // AD1 enable bit
    
    AD1CON1bits.ADON = 1;           // Operating Mode bit - ON
}

void __attribute__((__interrupt__,no_auto_psv)) _ADC1Interrupt(void)
{
    /* Clear the Analog-to-Digital interrupt flag bit */
    IFS0bits.AD1IF = 0;
    
    // AD1CON1bits.ASAM = 0;           // ADC Sample Auto-Start bit [STOP]
    // processing here -> work with dma memory instead
    // AD1CON1bits.ASAM = 1;           // ADC Sample Auto-Start bit [START]
}