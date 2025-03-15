/*!
 *    @File:         SensorFilter_PublicFunctions.h
 *
 *    @Brief:        Header file containing the public functions for Sensor
 *                   Filters.
 *
 *    @Date:         07/03/2025
 *
 */

#ifndef H_SENSORFILTER_PUBLICFUNCTIONS_H
#define H_SENSORFILTER_PUBLICFUNCTIONS_H

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
 * @brief         Function which will apply a low pass filter to a sensor
 *                reading.
 *
 * @param[in]     cutoffFrequency_Hz_in
 *                Cutoff frequency which will be used on the sensor readings.
 *
 * @param[in]     samplingPeriod_s_in
 *                Period which sensor data is sampled in seconds.
 *
 * @param[in]     currentUnfilteredReading_in
 *                Current reading from sensor, which is not filtered.
 *
 * @param[in]     previousFilteredReading_in
 *                Previous filtered sensor output.
 *
 * @param[out]    p_filteredReading_out
 *                Pointer containing the address of double where the result of
 *                the filtered reading will be stored.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int SensorFilter_lowPassFilter(double  cutoffFrequency_Hz_in,
                                      double  samplingPeriod_s_in,
                                      double  currentUnfilteredReading_in,
                                      double  previousFilteredReading_in,
                                      double *p_filteredReading_out);

#ifdef __cplusplus
}
#endif
#endif /* H_SENSORFILTER_PUBLICFUNCTIONS_H */