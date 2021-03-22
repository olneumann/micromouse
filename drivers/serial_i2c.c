/*
 * File:   serial_i2c.c
 * Author: oliver
 *
 * Created on 12. Februar 2021, 19:16
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "../dspic/board.h"

#include "serial_i2c.h"

int i2cInit(i2c_config_t *config)
{
    int status = -1;

    I2C1CONbits.I2CEN = 0;
    I2C1BRG = (config->fcy/config->fscl - config->fcy/config->fdelay)/2 - 2;
    I2C1CONbits.I2CEN = 1;                  // Enables the I2Cx module
    status = 0;
    
    return status;
}

static inline int waitACK(void)
{
    while(I2C1STATbits.TBF);                // Transmit in progress, I2CxTRN is full
    while(I2C1STATbits.TRSTAT);             // Wait for and verify ACK from the slave
    if (I2C1STATbits.ACKSTAT)               // 1 = NACK
    {
        I2C1CONbits.PEN = 1;
        while(I2C1CONbits.PEN);
        return -1;
    }
    return 0;
}

static inline void sendACK(void)
{
    I2C1CONbits.ACKEN = 1;                  // Send master ACK
    while(I2C1CONbits.ACKEN);               // Wait for complete
}

int i2cWrite(uint8_t addr, uint8_t idx_addr, uint8_t *pData, uint8_t count)
{
    int status = -1;
    int i = 0;
    uint8_t w_addr = addr << 1;             // 7bit addr + low lsb bit (write cond.)

    I2C1CONbits.SEN = 1;                    // Assert start condition
    while(I2C1CONbits.SEN == 1);
    
    I2C1TRN = w_addr;                       // Send w_addr with write indication
    if(waitACK() == -1) return status;
    I2C1TRN = idx_addr;                     // Send idx_addr
    if(waitACK() == -1) return status;

    for(i=0; i<count; i++)                  // Send data (sequential)
    {
        I2C1TRN = pData[i];                 // Order of data packages
        if(waitACK() == -1) return status;
    }
    
    I2C1CONbits.PEN = 1;                    // Send stop condition
    while(I2C1CONbits.PEN);
    status = 0;
        
    return status;
}

int i2cRead(uint8_t addr, uint8_t idx_addr, uint8_t *pData, uint32_t count)
{
    int status = -1;
    int i = 0;
    uint8_t w_addr = addr << 1;             // 7bit addr + low lsb bit (write cond.)
    uint8_t r_addr = (addr << 1) | 0x01;    // 7bit addr + high lsb bit (read cond.)
    
    I2C1CONbits.SEN = 1;                    // Assert start condition
    while(I2C1CONbits.SEN == 1);
    
    I2C1TRN = w_addr;                       // Send w_addr with write indication
    if(waitACK() == -1) return status;
    I2C1TRN = idx_addr;                     // Send idx_addr
    if(waitACK() == -1) return status;
       
    I2C1CONbits.RSEN = 1;                   // Assert repeated start condition
    while(I2C1CONbits.RSEN == 1);            
    
    I2C1TRN = r_addr;                       // Send r_addr with read indication
    if(waitACK() == -1) return status;
    
    for(i=0; i<count; i++)
    {
        I2C1CONbits.RCEN = 1;               // Enable master reception
        while(!I2C1STATbits.RBF);
        
        pData[i] = I2C1RCV;                 // Receive slave data
        
        if (i != count-1) sendACK();                          
    }

    I2C1CONbits.PEN = 1;                    // Send stop condition
    while(I2C1CONbits.PEN);
    status = 0;
        
    return status;
}