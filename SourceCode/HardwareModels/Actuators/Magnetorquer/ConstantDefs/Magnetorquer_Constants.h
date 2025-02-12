/*!
 *    @File:         Magnetorquer_Constants.h
 *
 *    @Brief:        Header file containing constants for magnetorquer
 *
 *    @Date:         10/02/2025
 *
 */

#ifndef H_MAGNETORQUER_CONSTANTS_H
#define H_MAGNETORQUER_CONSTANTS_H

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
 * @brief       Constant used to define the max length of string which will
 *              contain the name of the magnetorquer.
 *
 * @frame       N/A
 * @units       N/A
 */
#define MAGNETORQUER_MAX_SENSOR_NAME_BUFFER  (64)

/*!
 * @brief       Constant used to determint the minimum current required for
 *              there to be system noise in the magnetorquer.
 *
 * @frame       N/A
 * @units       Amperes
 */
#define MAGNETORQUER_MIN_CURRENT_THRESHOLD_A (0.0001)

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETORQUER_CONSTANTS_H */