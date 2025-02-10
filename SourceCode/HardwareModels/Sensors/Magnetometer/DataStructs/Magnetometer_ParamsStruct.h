/*!
 *    @File:         Magnetometer_ParamsStruct.h
 *
 *    @Brief:        Header file which contains the params struct for
 *                   magnetometer.
 *
 *    @Date:         30/01/2025
 *
 */

#ifndef H_MAGNETOMETER_PARAMSSTRUCT_H
#define H_MAGNETOMETER_PARAMSSTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "Sensors/Magnetometer/ConstantDefs/Magnetometer_Constants.h"

/* Generic Libraries */
/* None */

typedef struct Magnetometer_ParamsStruct
{
  /*!
   * @brief     String containing the name of the sensor. This is to help
   *            distinguish between different sensors within the system.
   *
   * @frame     N/A
   * @units     N/A
   */
  char magnetometerName[MAGNETOMETER_MAX_SENSOR_NAME_BUFFER];

  /*!
   * @brief     Vector of doubles which contains the position of the sensor
   *            in the body frame. This is fixed to the body frame and hence
   *            moves with the body.
   *
   * @frame     bod
   * @unit      m
   */
  double sensorPosition_Bod_m[3];

  /*!
   * @brief     Vector of doubles which contains the quaternion of the sensor
   *            in the body frame. This is fixed to the body frame and hence
   *            moves with the body.
   *
   * @frame     bod
   * @unit      N/A
   */
  double sensorQuaternion_BodToSen[4];

  /*!
   * @brief     Vector which keeps track of the mean gaussian noise in the
   *            sensor for all components of the vector.
   *
   * @frame     Sensosr Frame
   * @units     Nano Teslas
   */
  double noiseMean_Sen_nT[3];

  /*!
   * @brief     Vector which keeps track of the standard deviation of the
   *            gaussian noise in the sensor for all components of the vector.
   *
   * @frame     Sensosr Frame
   * @units     Nano Teslas
   */
  double noiseStandardDeviation_Sen_nT[3];

  /*!
   * @brief     Vector which keeps track of the amplitude of the gaussian noise
   *            in the sensor for all components of the vector.
   *
   * @frame     Sensosr Frame
   * @units     Nano Teslas
   */
  double noiseAmplitude_Sen_nT[3];

} Magnetometer_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETOMETER_PARAMSSTRUCT_H */