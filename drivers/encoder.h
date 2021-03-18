/* 
 * File:   encoder.h
 * Author: oliver
 *
 * Created on 4. Dezember 2020, 18:03
 */

#ifndef ENCODER_H
#define	ENCODER_H
 
#include <stdint.h>

/**
 * \brief Determine the angle of the motor left motor
 * \param[out] angle - float value [0.0-2*PI]
 */
float getAngleLeft(void);

/**
 * \brief Determine the angle of the motor right motor
 * \param[out] angle - float value [0.0-2*PI]
 */
float getAngleRight(void);

/**
 * \brief Determine the average angle driven by the target
 * \param[out] angle - float value [0.0-2*PI]
 */
float getAngle(void);

/**
 * \brief Determine the velocity in m/s of the left motor
 * \param[out] velocity - float value
 */
float getLinearVelocityLeft(void);

/**
 * \brief Determine the velocity in m/s of the right motor
 * \param[out] velocity - float value
 */
float getLinearVelocityRight(void);

/**
 * \brief Determine the average velocity in m/s
 * \param[out] average velocity - float value
 */
float getLinearVelocity(void);

/**
 * \brief Determine the distance in µm of the left motor
 * \param[out] distance - int32_t value
 */
int32_t getDistanceLeft(void);

/**
 * \brief Determine the distance in µm of the right motor
 * \param[out] distance - int32_t value
 */
int32_t getDistanceRight(void);

/**
 * \brief Determine the average (of both encoders) distance in µm
 * \param[out] average distance - int32_t value
 */
int32_t getDistance(void);

/**
 * \brief Update the encoder readings (counter, velocity)
 */
void updateEncoderReadings(uint16_t freq);

/**
 * \brief Initilizes the quadrature encoder interface
 * \param[in] init_poscnt - initial offset
 */
void qeiInit(void);

#endif	/* ENCODER_H */

