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
   * @frame     sensor
   * @unit      m
   */
  double trueSunVector_Sensor_m[3];

  /*!
   * @brief     Vector which contains the noise reading of the vector.
   *
   * @frame     sensor
   * @unit      m
   */
  double noiseVector_Sensor_m[3];

  /*!
   * @brief     Measured vector of the sensor.
   *
   * @frame     sensor
   * @unit      m
   */
  double measuredSunVector_Sensor_m[3];

  /*!
   * @brief     Archive struct for sensor.
   *
   * @frame     N/A
   * @unit      N/A
   */
  GArchive sunSensorArchive;

} SunSensor_State;

#ifdef __cplusplus
}
#endif

#endif /* H_SUNSENSOR_STATE_H */