/*!
 *    @File:         SunSensor_Params.h
 *
 *    @Brief:        Header file which contains the parameters of a SunSensor
 *                   model.
 *
 *    @Date:         11/11/2024
 *
 */

#ifndef H_SUNSENSOR_PARAMS_H
#define H_SUNSENSOR_PARAMS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "SunSensor/ConstantDefs/SunSensor_ConstDefs.h"

/* Generic Libraries */
/* None */

typedef struct SunSensor_ParamsStruct
{
  /*!
   * @brief     String containing the name of the sensor. This is to help
   *            distinguish between different sensors within the system.
   *
   * @frame     N/A
   * @units     N/A
   */
  char sunSensorName[SUNSENSOR_MAX_SENSOR_NAME_BUFFER];

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
   * @brief     Double which contains the fov of the sun sensor.
   *
   * @frame     N/A
   * @unit      N/A
   */
  double sensorFov_rad;

} SunSensor_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_SUNSENSOR_PARAMS_H */