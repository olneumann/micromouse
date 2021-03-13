/* 
 * File:   serial_uart_rn4871.h
 * Author: oliver
 *
 * Created on 12. Februar 2021, 13:36
 */
  
#ifndef SERIAL_UART_RN4871_H
#define	SERIAL_UART_RN4871_H

typedef enum {
    LOW_POWER = 0,
    NORMAL = 1
} bt_mode_t;

/**
 * \brief Initialize the Bluetooth Module
 * \return 0 on success, -1 otherwise
 */
int bluetoothInit();

/**
 * \brief Sets the operation mode of the bluetooth module
 * \param[in] LOW_POWER, NORMAL
 */
void setBTmode(bt_mode_t mode);

#endif	/* SERIAL_UART_RN4871_H */

