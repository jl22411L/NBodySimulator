/*
 *    @File:         GMath_Const.h
 *
 *    @ Brief:       Header file containing the constants for GMath module
 *
 *    @ Date:        02/03/2024
 *
 */

#ifndef H_GMATH_CONSTANTS_H
#define H_GMATH_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Integer which is used within matrix inversion buffers.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GMATH_MATRIX_INV_BUFFER                               (2048)

/*!
 * @brief       Integer used in inverting the column in GMath_invCol()
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GMATH_COLUMN_INV_BUFFER                               (2048)

/*!
 * @brief       Integer used in inverting the column in GMath_invColOptimised()
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GMATH_OPTIMISED_INV_MATRIX_INTERMEDIATE_COLUMN_BUFFER (32)

/*!
 * @brief       Decimal used to filter values and consider them to be zero. THis
 *              is used to overcome floating point errors.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GMATH_QUATERNION_ZERO_TOLERANCE                       (1E-8)

/*!
 * @brief       Tolerance used to indicate which set of equations should be used
 *              when converting a DCM to a quaternion. Value was taken from
 *              reference below.
 *
 *              [Ref: https://motoq.github.io/doc/tnotes/dcmq.pdf]
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GMATH_DCM2QUAT_CONVERSION_TOLERANCE                   (0.25)

#ifdef __cplusplus
}
#endif

#endif /* H_GMATH_CONSTANTS_H */
