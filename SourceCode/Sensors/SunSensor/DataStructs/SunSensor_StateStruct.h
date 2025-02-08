/*!
 *    @File:         SunSensor_State.h
 *
 *    @Brief:        Header file which contains the definition of the sun sensor
 *                   state struct.
 *
 *    @Date:         11/11/2024
 *
 */

#ifndef H_SUNSENSOR_STATE_H
#define H_SUNSENSOR_STATE_H

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
#include "GArchive/GArchive.h"

typedef struct SunSensor_StateStruct
{
  /*!
   * @brief     Vector which contains the true value for which the sensor is
   *            reading.
   *
   * @unit      m
   * @frame     Sensor
   */
  double trueSunVector_Sen_m[3];

  /*!
   * @brief     Vector which repressents the bias caused to the measurement from
   *            albedo effects of other celestial bodies.
   *
   * @unit      m
   * @frame     Sensor
   */
  double albedoComponentNoise_Sen_m[3];

  /*!
   * @brief     Vector which contains the noise reading of the vector. This is
   *            just random noise.
   *
   * @unit      m
   * @frame     sensor
   */
  double noiseVector_Sen_m[3];

  /*!
   * @brief     Measured vector of the sensor.
   *
   * @unit      m
   * @frame     Sensor
   */
  double measuredSunVector_Sen_m[3];

  /*!
   * @brief     Flag which indicates if the sun sensor can detect the sun. If
   *            the flag is GCONST_TRUE, then the measured sun vector will only
   *            be noise.
   *
   * @units     N/A
   * @frame     N/A
   */
  uint8_t isSensorReadingInvalid;

  /*!
   * @brief     Archive member for sensor.
   *
   * @unit      N/A
   * @frame     N/A
   */
  GArchive sunSensorArchive;

} SunSensor_State;

#ifdef __cplusplus
}
#endif

#endif /* H_SUNSENSOR_STATE_H */