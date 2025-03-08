/*!
 *    @File:         Gyro_StateStruct.h
 *
 *    @Brief:        State struct for Gyro Sensor
 *
 *    @Date:         05/02/2025
 *
 */

#ifndef H_GYRO_STATESTRUCT_H
#define H_GYRO_STATESTRUCT_H

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

typedef struct Gyro_StateStruct
{
  /*!
   * @brief       True reading of angular velocity of sensor.
   *
   * @frame       Sensor Frame
   * @units       radians per second
   */
  double trueGyroVector_Sen_rads[3];

  /*!
   * @brief       Noise reading of angular velocity of sensor.
   *
   * @frame       Sensor Frame
   * @units       radians per second
   */
  double noiseGyroVector_Sen_rads[3];

  /*!
   * @brief       Measured reading of angular velocity of sensor.
   *
   * @frame       Sensor Frame
   * @units       radians per second
   */
  double measuredGyroVector_Sen_rads[3];

  /*!
   * @brief     Measured vector of the sensor from previous timestep. (Used for
   *            low pass filtering)
   *
   * @frame     Sensor
   * @units     radians per second
   */
  double previousFilteredGyroVector_Sen_rads[3];

  /*!
   * @brief     Filtered vector reading of magnetic field.
   *
   * @frame     Sensor
   * @units     radians per second
   */
  double filteredGyroVector_Sen_rads[3];

  /*!
   * @brief     Archive member for sensor.
   *
   * @unit      N/A
   * @frame     N/A
   */
  GArchive gyroArchive;

} Gyro_State;

#ifdef __cplusplus
}
#endif
#endif /* H_GYRO_STATESTRUCT_H */