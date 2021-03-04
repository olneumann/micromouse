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

#include "../dspic/board.h"
#include "vl53l0x/vl53l0x_api.h"
#include "vl53l0x/vl53l0x_platform.h"

#include "ranging.h"

#define SENSOR_COUNT                1    
#define VL53L0X_ADDRESS_DEFAULT     0x29

VL53L0X_Dev_t dev[SENSOR_COUNT];    // dev[0] = L; dev[1] = F; dev[2] = R
VL53L0X_Dev_t *pDev = dev;          // &dev ?

static volatile uint16_t RANGE_L[4];
static volatile uint16_t RANGE_F[4];
static volatile uint16_t RANGE_R[4];

/*
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
    /*
     * Remapping: Set all sensors in reset, incrementally reprogram (n-1) sensors 
     *            to desired i2c address.     
     */
    
    XSHUT_L = 0;
    XSHUT_F = 0;    // all sensors in reset
    XSHUT_R = 0;
    
    // L = 0x52; F -> 0x54; R -> 0x56;
    XSHUT_F = 1;
    VL53L0X_SetDeviceAddress(&pDev[1], dev[1].I2cDevAddr);
    XSHUT_R = 1;
    VL53L0X_SetDeviceAddress(&pDev[2], dev[2].I2cDevAddr);
    XSHUT_L = 1;
}

VL53L0X_Error rangingInit(uint16_t kfscl)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
    
    int i;
    for (i=0; i<SENSOR_COUNT; i++)
    {
        pDev[i].I2cDevAddr = VL53L0X_ADDRESS_DEFAULT + i*2;
        pDev[i].comms_speed_khz = kfscl;
    }
    
    //remapSensors();
    
    for (i=0; i<SENSOR_COUNT; i++)
    {       
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_StaticInit(&pDev[i]);  
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_PerformRefCalibration(&pDev[i],
        		&VhvSettings, &PhaseCal); 
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_PerformRefSpadManagement(&pDev[i],
        		&refSpadCount, &isApertureSpads); 
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_SetDeviceMode(&pDev[i], 
                VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
    }
    
    return Status;
}

VL53L0X_Error enableRanging(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    int i;
    for (i=0; i<SENSOR_COUNT; i++)
    {       
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_StartMeasurement(&pDev[i]); 
    }
    return Status;
}

VL53L0X_Error disableRanging(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    int i;
    for (i=0; i<SENSOR_COUNT; i++)
    {       
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_StopMeasurement(&pDev[i]);  
    }
    return Status;
}

/*
 * Description: In continuous ranging mode the sensor is measuring continuously,
 *              if a new sample is on the stack we get an interrupt INT{0,1,2}.
 *              We use the ISR to call for the sample, copy it and put it in the
 *              corresponding array RANGE_SENSOR_{L,F,R} (historian, keep old
 *              values - filtering).
 * 
 */

float filter(volatile uint16_t *Data)
{
    // TODO: more sophisticated approach maybe?
    float mean = 0;
    mean = Data[0] + Data[1] + Data[2] + Data[3];
    mean /= 4;
    return mean;
}

float getRangeLeft(void)
{
    return filter(&RANGE_L[0]);
}

float getRangeFront(void)
{
    return filter(&RANGE_F[0]);
}

float getRangeRight(void)
{
    return filter(&RANGE_R[0]);
}

VL53L0X_Error getRangingSample(VL53L0X_Dev_t *pDev, volatile uint16_t *pData)
{
    VL53L0X_RangingMeasurementData_t RangingData;
    VL53L0X_RangingMeasurementData_t *pRangingData = &RangingData;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    Status = VL53L0X_GetRangingMeasurementData(pDev, pRangingData);
    *pData = pRangingData->RangeMilliMeter;
    
    VL53L0X_ClearInterruptMask(pDev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
    
    return Status;
}

/*
 * INT0 = INT_L
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT0Interrupt(void)
{
    IFS0bits.INT0IF = 0;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    VL53L0X_Dev_t *pDev = &dev[0];
    
    Status = getRangingSample(pDev, &RANGE_L[i]);
    
    i++;
    if (i==3) i = 0;
}

/*
 * INT1 = INT_F
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
{
    IFS1bits.INT1IF = 0;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    VL53L0X_Dev_t *pDev = &dev[1];
    
    Status = getRangingSample(pDev, &RANGE_F[i]);
    
    i++;
    if (i==3) i = 0;
}

/*
 * INT2 = INT_R
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
{
    IFS1bits.INT2IF = 0;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    VL53L0X_Dev_t *pDev = &dev[2];
    
    Status = getRangingSample(pDev, &RANGE_R[i]);
    
    i++;
    if (i==3) i = 0;
}