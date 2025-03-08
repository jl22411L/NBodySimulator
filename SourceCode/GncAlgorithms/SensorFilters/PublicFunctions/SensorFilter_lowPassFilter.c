/*!
 *    @File:         SensorFilter_lowPassFilter.c
 *
 *    @Brief:        Function definition of a low pass filter.
 *
 *    @Date:         07/03/2025
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int SensorFilter_lowPassFilter(double  cutoffFrequency_Hz_in,
                               double  samplingPeriod_s_in,
                               double  currentUnfilteredReading_in,
                               double  previousSensorReading_in,
                               double *p_filteredReading_out)
{
  /* Declare local variables */
  double smoothingFactor;

  /* Find smooething factor */
  smoothingFactor =
      2 * GCONST_PI * cutoffFrequency_Hz_in * samplingPeriod_s_in /
      (1 + 2 * GCONST_PI * samplingPeriod_s_in * cutoffFrequency_Hz_in);

  /* Find the filtered output */
  *(p_filteredReading_out) =
      smoothingFactor * previousSensorReading_in +
      (1 - smoothingFactor) * currentUnfilteredReading_in;

  return GCONST_TRUE;
}