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
 * \brief Initilizes the quadrature encoder interface
 * \param[in] init_poscnt - initial offset
 */
void qeiInit(uint16_t init_poscnt);

#endif	/* ENCODER_H */

