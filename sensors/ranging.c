/*
 * File:   ranging.c
 * Author: oliver
 *
 * Created on 2. Januar 2021, 17:00
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "../drivers/ranging/vl53l0x_api.h"
#include "../drivers/ranging/vl53l0x_platform.h"

#include "ranging.h"

#define SENSOR_COUNT 3    
VL53L0X_Dev_t *sensors[SENSOR_COUNT];

uint16_t RANGE_SENSOR_L[4];
uint16_t RANGE_SENSOR_F[4];
uint16_t RANGE_SENSOR_R[4];

/*
 * TODO: Bootstrap - remapping of i2c addresses for multiple sensors
 * 
 * Description: see appl. note
 *              - Set VL53L0x_SINGLE_DEVICE_DRIVER macro to 0 so that API implementation 
 *                will be automatically adapted to a multi-device context. (n.def??)
 *              - Define VL53L0xDev_t type as a structure pointer holding any data 
 *                required for multi-device management.
 *              - define, ?N? the number of VL53L0X (Struct MyVL53L0xDev_t BoardDevs[N])
 *              - Put all devices under reset (XSHUT - active low)
 *              - Enable VL53L0X one after the other and set their I2C address through 
 *                VL53L0X_SetDeviceAddress (&BoardDevs[i], FinalI2cAddr)
 * 
 */

void remapSensors(void)
{
    
}

VL53L0X_Error rangingInit(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    return Status;
}

/*
 * TODO: Continuous Ranging
 * 
 * Description: In continuous ranging mode the sensor is measuring continuously,
 *              if a new sample is on the stack we get an interrupt INT{0,1,2}.
 *              We use the ISR to call for the sample, copy it and put it in the
 *              corresponding array RANGE_SENSOR_{L,F,R} (historian, keep old
 *              values - filtering).
 * 
 */

VL53L0X_Error getRangingSample(VL53L0X_Dev_t *pDev, uint16_t *pData)
{
    VL53L0X_RangingMeasurementData_t RangingData;
    VL53L0X_RangingMeasurementData_t *pRangingData = &RangingData;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    Status = VL53L0X_GetRangingMeasurementData(pDev, pRangingData);
    *pData = pRangingData->RangeMilliMeter;
    
    VL53L0X_ClearInterruptMask(pDev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
    VL53L0X_PollingDelay(pDev);  
    
    return Status;
}

/*
 * INT0 = INT_L
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT0Interrupt(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    
    Status = getRangingSample(sensors[0], &RANGE_SENSOR_L[i]);
    
    i++;
    if (i==3) i = 0;
}

/*
 * INT1 = INT_F
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    
    Status = getRangingSample(sensors[1], &RANGE_SENSOR_F[i]);
    
    i++;
    if (i==3) i = 0;
}

/*
 * INT2 = INT_R
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    
    Status = getRangingSample(sensors[2], &RANGE_SENSOR_R[i]);
    
    i++;
    if (i==3) i = 0;
}