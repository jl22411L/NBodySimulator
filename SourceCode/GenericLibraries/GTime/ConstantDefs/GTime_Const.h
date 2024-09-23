/*
 *    @File:         GTime_Const.h
 *
 *    @Brief:        Header file containing the constants for GTime library
 *
 *    @Date:         13/09/2024
 *
 */

#ifndef H_GTIME_CONST_H
#define H_GTIME_CONST_H

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
 * @brief       Year in which UNIX time is starting from.
 *
 * @frame       N/A
 * @unit        year
 */
#define GTIME_UNIX_START_YEAR      (1970)

/*!
 * @brief       Month in which UNIX time is starting from.
 *
 * @frame       N/A
 * @unit        month
 */
#define GTIME_UNIX_START_MONTH     (1)

/*!
 * @brief       Day in which UNIX time is starting from.
 *
 * @frame       N/A
 * @unit        day
 */
#define GTIME_UNIX_START_DAY       (1)

/*!
 * @brief       Hour in which UNIX time is starting from.
 *
 * @frame       N/A
 * @unit        hour
 */
#define GTIME_UNIX_START_HOUR      (0)

/*!
 * @brief       Minute in which UNIX time is starting from.
 *
 * @frame       N/A
 * @unit        minute
 */
#define GTIME_UNIX_START_MIN       (0)

/*!
 * @brief       Second in which UNIX time is starting from.
 *
 * @frame       N/A
 * @unit        second
 */
#define GTIME_UNIX_START_SEC       (0)

/* ------------------------------------------------------------------------ *
 * CONVERSION RATIOS
 * ------------------------------------------------------------------------ */

/*!
 * Conversions are taken from [Ref: https://www.unixtimestamp.com/]
 */

/*!
 * @brief       Constant which converts 1 year into seconds.
 *
 * @frame       N/A
 * @unit        seconds per year
 */
#define GTIME_ONE_YEAR_TO_SECONDS  (31556926)

/*!
 * @brief       Constant which converts 1 month into seconds.
 *
 * @frame       N/A
 * @unit        seconds per month
 */
#define GTIME_ONE_MONTH_TO_SECONDS (2629743)

/*!
 * @brief       Constant which converts 1 day into seconds.
 *
 * @frame       N/A
 * @unit        seconds per day
 */
#define GTIME_ONE_DAY_TO_SECONDS   (86400)

/*!
 * @brief       Constant which converts 1 hour into seconds.
 *
 * @frame       N/A
 * @unit        seconds per hour
 */
#define GTIME_ONE_HOUR_TO_SECONDS  (3600)

/*!
 * @brief       Constant which converts 1 minute into seconds.
 *
 * @frame       N/A
 * @unit        seconds per minute
 */
#define GTIME_ONE_MIN_TO_SECONDS   (60)

#ifdef __cplusplus
}
#endif
#endif /* H_GTIME_CONST_H */
