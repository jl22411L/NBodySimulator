/*
 *    @File:         GTime_PublicFunctions.h
 *
 *    @Brief:        Contains all the public functions for GTime library
 *
 *    @Date:         13/09/2024
 *
 */

#ifndef H_GTIME_PUBLICFUNCTIONS_H
#define H_GTIME_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which converts calender time into UNIX time. The time
 *              is dependent on what the user inputs into the function. Hence,
 *              this function works independent on time zone, but different time
 *              zones will have different results in UNIX time.
 *
 * @param[in]   yearCalenderTime_in
 *              Integer representing the year in calender time to convert to
 *              UNIX time.
 *
 * @param[in]   monthCalenderTime_in
 *              Integer representing the month in calender time to convert to
 *              UNIX time.
 *
 * @param[in]   dayCalenderTime_in
 *              Integer representing the day in calender time to convert to
 *              UNIX time.
 *
 * @param[in]   hourCalenderTime_in
 *              Integer representing the hour in calender time to convert to
 *              UNIX time.
 *
 * @param[in]   minCalenderTime_in
 *              Integer representing the min in calender time to convert to
 *              UNIX time.
 *
 * @param[in]   secondCalenderTime_in
 *              Double representing the min in calender time to convert to
 *              UNIX time.
 *
 * @param[out]  p_unixTime_out
 *              Ponter containing the address of the variable which will contain
 *              the unix time.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GTime_calenderToUnix(
    uint16_t yearCalenderTime_in,
    uint8_t  monthCalenderTime_in,
    uint8_t  dayCalenderTime_in,
    uint8_t  hourCalenderTime_in,
    uint8_t  minCalenderTime_in,
    double   secondCalenderTime_in,
    double  *p_unixTime_out);

#ifdef __cplusplus
}
#endif
#endif /* H_GTIME_PUBLICFUNCTIONS_H */
