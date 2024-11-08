/*
 *    @File:         GTime_utvToUnix.c
 *
 *    @Brief:        Converts time from UTC to Unix time.
 *
 *    @Date:         13/09/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "GTime/ConstantDefs/GTime_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int GTime_calenderToUnix(
    uint16_t yearCalenderTime_in,
    uint8_t  monthCalenderTime_in,
    uint8_t  dayCalenderTime_in,
    uint8_t  hourCalenderTime_in,
    uint8_t  minCalenderTime_in,
    double   secondCalenderTime_in,
    double  *p_unixTime_out)
{
  /* Declare local variables */
  /* None */

  /* Check to make sure month is valid */
  if (monthCalenderTime_in < 1 | monthCalenderTime_in > 12)
  {
    GError(
        "Month is out of range of possible values when converting to UNIX "
        "time, monthCalenderTime_in = %d",
        monthCalenderTime_in);
  }

  /* Check to make sure day is valid. */
  if (!(dayCalenderTime_in > 0 | dayCalenderTime_in < 31))
  {
    GError(
        "Day is out of range of possible values when converting to UNIX time, "
        "dayCalenderTime_in = %d",
        dayCalenderTime_in);
  }

  /* Check to make sure hour is valid. */
  if (!(hourCalenderTime_in < 24))
  {
    GError(
        "Hour is out of range of possible values when converting to UNIX time, "
        "hourCalenderTime_in = %d",
        hourCalenderTime_in);
  }

  /* Check to make sure minute is valid. */
  if (!(minCalenderTime_in < 60))
  {
    GError(
        "Minute is out of range of possible values when converting to UNIX "
        "time, minCalenderTime_in = %d",
        minCalenderTime_in);
  }

  /* Check to make sure second is valid. */
  if (!(secondCalenderTime_in < 60))
  {
    GError(
        "Second is out of range of possible values when converting to UNIX "
        "time, secondCalenderTime_in = %d",
        secondCalenderTime_in);
  }

  /* Find the unix time from the calender time */
  *p_unixTime_out =
      ((double)(yearCalenderTime_in - GTIME_UNIX_START_YEAR) *
           GTIME_ONE_YEAR_TO_SECONDS +
       (double)(monthCalenderTime_in - GTIME_UNIX_START_MONTH) *
           GTIME_ONE_MONTH_TO_SECONDS +
       (double)(dayCalenderTime_in - GTIME_UNIX_START_DAY) *
           GTIME_ONE_DAY_TO_SECONDS +
       (double)(hourCalenderTime_in - GTIME_UNIX_START_HOUR) *
           GTIME_ONE_HOUR_TO_SECONDS +
       (double)(minCalenderTime_in - GTIME_UNIX_START_MIN) *
           GTIME_ONE_MIN_TO_SECONDS +
       (secondCalenderTime_in - GTIME_UNIX_START_SEC));

  return GCONST_TRUE;
}
