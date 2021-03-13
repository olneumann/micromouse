/*
 * File:   motor.h
 * Author: oliver
 *
 * Created on 5. Dezember 2020, 15:47
 */

#ifndef MOTOR_H
#define	MOTOR_H
 
#define motorLeftDir      1
#define motorRightDir    -1
#define MAX_SPEED_MS      0.626f

/**
 * \brief Initilizes motor pwm signal generation
 */
void motorInit(uint16_t kfpwm);

/**
 * \brief Sets the duty cycle following the h-bridge setup
 * \param[in] percent - float value between -1 and 1 determines the duty cycle
 * \return 0 on success, -1 otherwise
 */
void driveLeft(float percent);

/**
 * \brief Sets the duty cycle following the h-bridge setup
 * \param[in] percent - float value between -1 and 1 determines the duty cycle
 * \return 0 on success, -1 otherwise
 */
void driveRight(float percent);

#endif	/* MOTOR_H */

