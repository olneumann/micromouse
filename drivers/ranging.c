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
#include "../common/defines.h"
#include "vl53l0x/vl53l0x_api.h"
#include "vl53l0x/vl53l0x_platform.h"

#include "ranging.h"

#define SENSOR_COUNT                (uint8_t)3    
#define VL53L0X_ADDRESS_DEFAULT     (uint8_t)0x29

VL53L0X_Dev_t dev[SENSOR_COUNT];    // dev[0] = L; dev[1] = F; dev[2] = R
VL53L0X_Dev_t *pDev = dev;          

static uint16_t RANGE_L[4];
static uint16_t RANGE_F[4];
static uint16_t RANGE_R[4];

/*
 * Description:
 *              - Testing of I2C interface
 *              - Timer based minimal ranging function
 * 
 */

#ifdef VL53L0X_DEBUG

#include "../drivers/serial_uart.h"

#define SENSOR_COUNT                (uint8_t)1

static volatile uint16_t RANGE;

int rd_write_verification(VL53L0X_DEV Dev, uint8_t addr, uint32_t expected_value)
{
    uint8_t bytes[4],mbytes[4];
    uint16_t words[2];
    uint32_t dword;
    int i=0;

    VL53L0X_ReadMulti(Dev, addr, mbytes, 4);
    for (i=0; i<4; i++){VL53L0X_RdByte(Dev, addr+i, &bytes[i]); }
    for (i=0; i<2; i++){VL53L0X_RdWord(Dev, addr+i*2, &words[i]); }
    VL53L0X_RdDWord(Dev, addr, &dword);

    char str[42];
    sprintf(str,"expected   = %8x,\n",expected_value);
    uartWrite(str,0);
    sprintf(str,"read_multi = %2x, %2x, %2x, %2x\n", mbytes[0],mbytes[1],mbytes[2],mbytes[3]);
    uartWrite(str,0);
    sprintf(str,"read_bytes = %2x, %2x, %2x, %2x\n", bytes[0],bytes[1],bytes[2],bytes[3]);
    uartWrite(str,0);
    sprintf(str,"read words = %4x, %4x\n",words[0],words[1]);
    uartWrite(str,0);
    sprintf(str,"read dword = %8x\n",dword);
    uartWrite(str,0);

    if(((uint32_t)mbytes[0]<<24 | (uint32_t)mbytes[1]<<16 | (uint32_t)mbytes[2]<<8 | (uint32_t)mbytes[3]) != expected_value) return (-1);
    if(((uint32_t)bytes[0]<<24 | (uint32_t)bytes[1]<<16 | (uint32_t)bytes[2]<<8 | (uint32_t)bytes[3]) != expected_value) return (-1);
    if(((uint32_t)words[0]<<16 | (uint32_t)words[1]) != expected_value) return (-1);
    if(dword != expected_value) return(-1);

    return(0);
}

void i2c_test(void)
{
    /*
     * Test I2C primitives for byte, word, dword, and multi read & write
     * access. Importance of ACK/NACK, ordering of packets (MSB/LSB).
     * 
     * [Dev] = &pDev[{0,1,2,...}] select sensor obj. 
     */
    VL53L0X_DEV Dev = &pDev[0];

    int err_count = 0;
    uint32_t expected_value = 0;

    uint8_t buff[4] = {0x11,0x22,0x33,0x44};
    uint8_t ChipID[4];
    int i=0;

    for (i=0; i<4; i++){VL53L0X_RdByte(Dev, 0xC0+i, &ChipID[i]); }
    expected_value = (uint32_t)ChipID[0]<<24 | (uint32_t)ChipID[1]<<16 | (uint32_t)ChipID[2]<<8 | (uint32_t)ChipID[3];    
    if(rd_write_verification(Dev, 0xc0, expected_value) <0) err_count++;	// check the chip ID

    VL53L0X_WriteMulti(Dev, 0x4, buff, 4);				// check WriteMulti
    if(rd_write_verification(Dev, 0x4, 0x11223344) <0) err_count++;

    VL53L0X_WrDWord(Dev, 0x4, 0xffeeddcc);				// check WrDWord
    if(rd_write_verification(Dev, 0x4, 0xffeeddcc) <0) err_count++;

    VL53L0X_WrWord(Dev, 0x4, 0x5566);					// check WrWord
    VL53L0X_WrWord(Dev, 0x6, 0x7788);
    if(rd_write_verification(Dev, 0x4, 0x55667788) <0) err_count++;

    for (i=0; i<4; i++){VL53L0X_WrByte(Dev, 0x04+i, buff[i]);}
    if(rd_write_verification(Dev, 0x4,0x11223344) <0) err_count++;

    if(err_count>0)
    {
        char str[30];
        sprintf(str,"i2c test failed - please check it\n");
        uartWrite(str,0);
    }
}

void print_pal_error(VL53L0X_Error Status){
    char buf[VL53L0X_MAX_STRING_LENGTH];
    char str[100];
    VL53L0X_GetPalErrorString(Status, buf);
    sprintf(str, "API Status: %i : %s\n", Status, buf);
    uartWrite(str,0);
}

void print_range_status(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData){
    char buf[VL53L0X_MAX_STRING_LENGTH];
    char str[100];
    uint8_t RangeStatus;

    /*
     * New Range Status: data is valid when pRangingMeasurementData->RangeStatus = 0
     */

    RangeStatus = pRangingMeasurementData->RangeStatus;

    VL53L0X_GetRangeStatusString(RangeStatus, buf);
    sprintf(str,"Range Status: %i : %s\n", RangeStatus, buf);
    uartWrite(str,0);
}

#endif

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
     * Addresses: L = 0x29; F -> 0x2b; R -> 0x2d;  
     *   
     */
    
    XSHUT_L = 0;
    XSHUT_F = 0;    // all sensors in reset
    XSHUT_R = 0;

    XSHUT_F = 1;
    DELAY_600uS;    // wait till set
    VL53L0X_SetDeviceAddress(&pDev[0], dev[1].I2cDevAddr*2);
    XSHUT_R = 1;
    DELAY_600uS;
    VL53L0X_SetDeviceAddress(&pDev[0], dev[2].I2cDevAddr*2);
    XSHUT_L = 1;
    DELAY_600uS;
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
    
#ifdef VL53L0X_DEBUG
    XSHUT_L = 1;
    XSHUT_F = 0;    // only one sensor
    XSHUT_R = 0;
#else
    remapSensors();
#endif
    
    for (i=0; i<SENSOR_COUNT; i++)
    {       
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_DataInit(&pDev[i]);
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_StaticInit(&pDev[i]);  
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_PerformRefCalibration(&pDev[i],
        		&VhvSettings, &PhaseCal); 
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_PerformRefSpadManagement(&pDev[i],
        		&refSpadCount, &isApertureSpads);        
        if(Status == VL53L0X_ERROR_NONE) Status = VL53L0X_SetDeviceMode(&pDev[i], 
                VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
    }
    
    // interrupt params
    IPC0bits.INT0IP = 5;    // prios
    IPC5bits.INT1IP = 5;
    IPC7bits.INT2IP = 5;
    
    IFS0bits.INT0IF = 0;    // reset both flags
    IFS1bits.INT1IF = 0;
    IFS1bits.INT2IF = 0;
    
#ifdef VL53L0X_DEBUG
    IEC0bits.INT0IE = 0;    // disable interrupts
    IEC1bits.INT1IE = 0;
    IEC1bits.INT2IE = 0;
#else
    IEC0bits.INT0IE = 1;    // enable interrupts
    IEC1bits.INT1IE = 1;
    IEC1bits.INT2IE = 1;
#endif
    
    INTCON2bits.INT0EP = 1; // interrupt on negative edge
    INTCON2bits.INT1EP = 1;
    INTCON2bits.INT2EP = 1;
    
#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
    
    return Status;
}

VL53L0X_Error enableRanging(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    int i;
    for (i=0; i<SENSOR_COUNT; i++)
    {       
        Status = VL53L0X_StartMeasurement(&pDev[i]);
        Status = VL53L0X_ClearInterruptMask(&pDev[i], VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
    }

#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
    
    return Status;
}

VL53L0X_Error disableRanging(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    int i;
    for (i=0; i<SENSOR_COUNT; i++)
    {       
        Status = VL53L0X_StopMeasurement(&pDev[i]);  
    }
    
#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
    
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
    return RANGE_L[0]; //filter(&RANGE_L[0]);
}

float getRangeFront(void)
{
    return RANGE_F[0]; //filter(&RANGE_F[0]);
}

float getRangeRight(void)
{
    return RANGE_R[0]; //filter(&RANGE_R[0]);
}

static inline VL53L0X_Error getRangingSample(VL53L0X_Dev_t *pDev, volatile uint16_t *pData)
{
    VL53L0X_RangingMeasurementData_t RangingData;
    VL53L0X_RangingMeasurementData_t *pRangingData = &RangingData;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
    Status = VL53L0X_GetRangingMeasurementData(pDev, pRangingData);
    *pData = pRangingData->RangeMilliMeter;
    
    VL53L0X_ClearInterruptMask(pDev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
    
#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
    
    return Status;
}

#ifdef VL53L0X_DEBUG

void doRanging(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    Status = getRangingSample(&pDev[0], &RANGE);
    
#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
}

uint16_t getRange(void)
{
    return RANGE;
}

#endif

/*
 * INT0 = INT_L
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT0Interrupt(void)
{
    IFS0bits.INT0IF = 0;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    
    Status = getRangingSample(&dev[0], &RANGE_L[0]);
    
    i++;
    if (i==3) i = 0;
    
#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
}

/*
 * INT1 = INT_F
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
{
    IFS1bits.INT1IF = 0;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;

    Status = getRangingSample(&dev[1], &RANGE_F[0]);
    
    i++;
    if (i==3) i = 0;
    
#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
}

/*
 * INT2 = INT_R
 */
void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
{
    IFS1bits.INT2IF = 0;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    static int i = 0;
    
    Status = getRangingSample(&dev[2], &RANGE_R[0]);
    
    i++;
    if (i==3) i = 0;
    
#ifdef VL53L0X_DEBUG_LOG
    print_pal_error(Status);
#endif
}