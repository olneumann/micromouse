/*
 * File:   serial_i2c.c
 * Author: oliver
 *
 * Created on 12. Februar 2021, 19:16
 */

#ifndef SERIAL_I2C_H
#define	SERIAL_I2C_H

#include <stdint.h>

typedef struct
{
    uint32_t fcy; 
    uint32_t fscl;
    uint32_t fdelay;
} i2c_config_t;

/**
 * \brief Initialize the UART peripheral
 * \param[in] config - the UART configuration
 * \return 0 on success, -1 otherwise
 */
int i2cInit(i2c_config_t *config);

/**
 * \brief Write data stream to I2C
 * \param[in] addr      - Addresse of slave device
 * \param[in] idx_addr  - Register address
 * \param[in] *pData    - Data pointer
 * \param[in] count     - Size of data stream
 * \return 0 on sucesss, -1 otherwise
 */
int i2cWrite(uint8_t addr, uint8_t idx_addr, uint8_t *pData, uint8_t count);

/**
 * \brief Read data stream from I2C
 * \param[in] addr      - Addresse of slave device
 * \param[in] idx_addr  - Register address
 * \param[in] *pData    - Data pointer
 * \param[in] count     - Size of data stream
 * \return 0 on sucesss, -1 otherwise
 */
int i2cRead(uint8_t addr, uint8_t idx_addr, uint8_t *pData, uint32_t count);

#endif	/* SERIAL_I2C_H */

