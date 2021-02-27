/* 
 * File:   encoder.h
 * Author: oliver
 *
 * Created on 4. Dezember 2020, 18:03
 */

#ifndef ENCODER_H
#define	ENCODER_H
 
#include <stdint.h>

typedef enum {
    POS = 1,
    NEG = -1
} direction;

/**
 * \brief Determine the rotation of the motor 1
 * \param[out] direction - the rotation of the motor 1
 */
direction getDir1(void);

/**
 * \brief Determine the rotation of the motor 2
 * \param[out] direction - the rotation of the motor 2
 */
direction getDir2(void);

/**
 * \brief Determine the angle of the motor 1
 * \param[out] angle - float value [0.0-360.0]
 */
double getAngle1(void);

/**
 * \brief Determine the angle of the motor 2
 * \param[out] angle - float value [0.0-360.0]
 */
double getAngle2(void);

/**
 * \brief Initilizes the quadrature encoder interface
 * \param[in] init_poscnt - initial offset
 */
void qeiInit(uint16_t init_poscnt);

#endif	/* ENCODER_H */

