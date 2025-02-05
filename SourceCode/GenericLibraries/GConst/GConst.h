/*
 *   @File:         GConst.h
 *
 *   @ Brief:       Contains General Constants
 *
 *   @ Description: Contains Constants to be used within the simulator
 *
 */

#ifndef H_GCONST_H
#define H_GCONST_H

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

/* ---------------------------- Global Constants ---------------------------- */

/* ------------------------------------------------------------------------ *
 * EXECUTION PROCESS CONSTANTS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Constant which is used to represent a true state.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GCONST_TRUE                        (1)

/*!
 * @brief       Constant which is used to represent a false state.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GCONST_FALSE                       (0)

/*!
 * @brief       Constant which is used to represent when an executable has
 *              executed successfully.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GCONST_EXIT_SUCCESS                (0)

/*!
 * @brief       Constant which is used to represent when an executable has not
 *              executed successfully.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GCONST_EXIT_FAILURE                (1)

/* ------------------------------------------------------------------------ *
 * TOLLERANCE CONSTANTS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Constant which represents a milimeter in standard units.
 *
 * @frame       N/A
 * @unit        m
 */
#define GCONST_MM_TOLERANCE                (0.001)

/*!
 * @brief       Constant which represents a micrometer in standard units.
 *
 * @frame       N/A
 * @unit        m
 */
#define GCONST_UM_TOLERANCE                (0.000001)

/*!
 * @brief       Constant which represents a nanometer in standard units.
 *
 * @frame       N/A
 * @unit        m
 */
#define GCONST_NM_TOLERANCE                (0.000000001)

/*!
 * @brief       Constant which represents a picometer in standard units.
 *
 * @frame       N/A
 * @unit        m
 */
#define GCONST_PM_TOLERANC                 (0.000000000001)

/* ------------------------------------------------------------------------ *
 * ROTATION CONSTANTS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Constant used to define Pi.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GCONST_PI                          (3.14159265358979323846264338327950288419716939)

/*!
 * @brief       Constant which represents the converstion from degrees to
 *              radians.
 *
 * @frame       N/A
 * @unit        deg / rad
 */
#define GCONST_DEG_TO_RAD                  (GCONST_PI / 180)

/*!
 * @brief       Constant which represents the converstion from radians to
 *              degrees.
 *
 * @frame       N/A
 * @unit        rad / deg
 */
#define GCONST_RAD_TO_DEG                  (180 / GCONST_PI)

/* ------------------------------------------------------------------------ *
 * CONVERSION CONSTANTS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Constant used to convert a year into seconds.
 *
 * @frame       N/A
 * @unit        Seconds per Year
 */
#define GCONST_YEARS_TO_SECONDS_CONVERSION (31536000)

/* ------------------------------------------------------------------------ *
 * TIME CONSTANTS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Constant used to define Janurary 2020 1st 12:00 in unix time in
 *              seconds.
 *
 * @frame       N/A
 * @unit        Seconds
 */
#define GCONST_J2000_UNIX_TIME_S           (946728000)

#ifdef __cplusplus
}
#endif

#endif /* H_GCONST_H */
