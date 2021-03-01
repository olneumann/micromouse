/*
 * File:   vl53l0x_i2c_platform.c
 * Author: oliver
 *
 * Created on 12. Februar 2021, 19:16
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../serial_i2c.h"

#include "vl53l0x_def.h"
#include "vl53l0x_i2c_platform.h"

char debug_string[VL53L0X_MAX_STRING_LENGTH_PLT];

uint8_t cached_page = 0;

#define MIN_COMMS_VERSION_MAJOR     1
#define MIN_COMMS_VERSION_MINOR     8
#define MIN_COMMS_VERSION_BUILD     1
#define MIN_COMMS_VERSION_REVISION  0

#define MAX_STR_SIZE            255
#define MAX_MSG_SIZE            100
#define MAX_DEVICES             4
#define STATUS_OK               0x00
#define STATUS_FAIL             0x01

static unsigned char _dataBytes[MAX_MSG_SIZE];

bool_t _check_min_version(void)
{
    return true;
}

int VL53L0X_i2c_init(char *comPortStr, unsigned int baudRate) // mja
{
    unsigned int status = STATUS_FAIL;
    
    return status;
}

int32_t VL53L0X_comms_close(void)
{
    unsigned int status = STATUS_FAIL;

    return status;
}

int32_t VL53L0X_write_multi(uint8_t address, uint8_t reg, uint8_t *pdata, int32_t count)
{
    int32_t status = STATUS_OK;
    
    status = i2cWrite(address, reg, pdata, count);
    
    return status;
}

int32_t VL53L0X_read_multi(uint8_t address, uint8_t index, uint8_t *pdata, int32_t count)
{
    int32_t status = STATUS_OK;

    status = i2cRead(address, index, _dataBytes, count);
    memcpy(pdata, &_dataBytes, count);

    return status;
}

int32_t VL53L0X_write_byte(uint8_t address, uint8_t index, uint8_t data)
{
    int32_t status = STATUS_OK;
    const int32_t cbyte_count = 1;

    status = VL53L0X_write_multi(address, index, &data, cbyte_count);

    return status;
}

int32_t VL53L0X_write_word(uint8_t address, uint8_t index, uint16_t data)
{
    int32_t status = STATUS_OK;
    uint8_t buffer[BYTES_PER_WORD];

    // Split 16-bit word into MS and LS uint8_t
    buffer[0] = (uint8_t)(data >> 8);
    buffer[1] = (uint8_t)(data &  0x00FF);

    if(index%2 == 1)
    {
        status = VL53L0X_write_multi(address, index, &buffer[0], 1);
        status = VL53L0X_write_multi(address, index + 1, &buffer[1], 1);
        // serial comms cannot handle word writes to non 2-byte aligned registers.
    }
    else
    {
        status = VL53L0X_write_multi(address, index, buffer, BYTES_PER_WORD);
    }

    return status;
}

int32_t VL53L0X_write_dword(uint8_t address, uint8_t index, uint32_t data)
{
    int32_t status = STATUS_OK;
    uint8_t  buffer[BYTES_PER_DWORD];

    // Split 32-bit word into MS ... LS bytes
    buffer[0] = (uint8_t) (data >> 24);
    buffer[1] = (uint8_t)((data &  0x00FF0000) >> 16);
    buffer[2] = (uint8_t)((data &  0x0000FF00) >> 8);
    buffer[3] = (uint8_t) (data &  0x000000FF);

    status = VL53L0X_write_multi(address, index, buffer, BYTES_PER_DWORD);

    return status;
}

int32_t VL53L0X_read_byte(uint8_t address, uint8_t index, uint8_t *pdata)
{
    int32_t status = STATUS_OK;
    int32_t cbyte_count = 1;

    status = VL53L0X_read_multi(address, index, pdata, cbyte_count);

    return status;
}

int32_t VL53L0X_read_word(uint8_t address, uint8_t index, uint16_t *pdata)
{
    int32_t  status = STATUS_OK;
	uint8_t  buffer[BYTES_PER_WORD];

    status = VL53L0X_read_multi(address, index, buffer, BYTES_PER_WORD);
	*pdata = ((uint16_t)buffer[0]<<8) + (uint16_t)buffer[1];

    return status;
}

int32_t VL53L0X_read_dword(uint8_t address, uint8_t index, uint32_t *pdata)
{
    int32_t status = STATUS_OK;
	uint8_t  buffer[BYTES_PER_DWORD];

    status = VL53L0X_read_multi(address, index, buffer, BYTES_PER_DWORD);
    *pdata = ((uint32_t)buffer[0]<<24) + ((uint32_t)buffer[1]<<16) + ((uint32_t)buffer[2]<<8) + (uint32_t)buffer[3];

    return status;
}

int32_t VL53L0X_platform_wait_us(int32_t wait_us)
{
    int32_t status = STATUS_OK;
    
    /*
     * perform non-blocking wait.
     */

    return status;
}

int32_t VL53L0X_wait_ms(int32_t wait_ms)
{
    int32_t status = STATUS_OK;

    /*
     * perform non-blocking wait.
     */

    return status;
}

int32_t VL53L0X_set_gpio(uint8_t level)
{
    int32_t status = STATUS_OK;
    return status;
}

int32_t VL53L0X_get_gpio(uint8_t *plevel)
{
    int32_t status = STATUS_OK;
    return status;
}

int32_t VL53L0X_release_gpio(void)
{
    int32_t status = STATUS_OK;
    return status;
}

int32_t VL53L0X_cycle_power(void)
{
    int32_t status = STATUS_OK;
	return status;
}

int32_t VL53L0X_get_timer_frequency(int32_t *ptimer_freq_hz)
{
    *ptimer_freq_hz = 0;
    return STATUS_FAIL;
}

int32_t VL53L0X_get_timer_value(int32_t *ptimer_count)
{
    *ptimer_count = 0;
    return STATUS_FAIL;
}
