/*
 * File:   motor.h
 * Author: oliver
 *
 * Created on 5. Dezember 2020, 15:47
 */

#ifndef MOTOR_H
#define	MOTOR_H
 
#define M1_dir -1
#define M2_dir  1

/**
 * \brief Initilizes motor pwm signal generation
 */
void motorInit(void); 

/**
 * \brief Sets the duty cycle following the h-bridge setup
 * \param[in] percent - double value between -1 and 1 determines the duty cycle
 * \return 0 on success, -1 otherwise
 */
void driveM1(double percent);

/**
 * \brief Sets the duty cycle following the h-bridge setup
 * \param[in] percent - double value between -1 and 1 determines the duty cycle
 * \return 0 on success, -1 otherwise
 */
void driveM2(double percent);

#endif	/* MOTOR_H */

