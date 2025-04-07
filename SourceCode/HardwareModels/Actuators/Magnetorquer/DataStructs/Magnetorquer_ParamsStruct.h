/*!
 *    @File:         Magnetorquer_ParamsStruct.h
 *
 *    @Brief:        Header file containing the struct declaration of
 *                   Magnetorquer Params struct.
 *
 *    @Date:         10/02/2025
 *
 */

#ifndef H_MAGNETORQUER_PARAMSSTRUCT_H
#define H_MAGNETORQUER_PARAMSSTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "Actuators/Magnetorquer/ConstantDefs/Magnetorquer_Constants.h"

/* Generic Libraries */
/* None */

typedef struct Magnetorquer_ParamsStruct
{
  /*!
   * @brief     String containing the name of the actuator. This is to help
   *            distinguish between different actuators within the system.
   *
   * @frame     N/A
   * @units     N/A
   */
  char magnetorquerName[MAGNETORQUER_MAX_SENSOR_NAME_BUFFER];

  /*!
   * @brief     Vector of doubles which contains the position of the actuator
   *            in the body frame. This is fixed to the body frame and hence
   *            moves with the body.
   *
   * @frame     bod
   * @unit      m
   */
  double actuatorPosition_Bod_m[3];

  /*!
   * @brief     Vector of doubles which contains the quaternion of the actuator
   *            in the body frame. This is fixed to the body frame and hence
   *            moves with the body.
   *
   * @frame     Body Frame
   * @units     N/A
   */
  double actuatorQuaternion_BodToSen[4];

  /*!
   * @brief       Member which keeps track of the areas covered by the coils.
   *
   * @frame       Sensor Frame
   * @units       Meters Suared
   */
  double coilArea_Sen_m2[3];

  /*!
   * @brief       Member which keeps track of the number of coil turns in the
   *              actuator.
   *
   * @frame       Sensor Frame
   * @units       Number of Turns (Negated from Unit Tag as not a standard unit)
   */
  double coilTurns_Sen[3];

  /*!
   * @brief       The mean noise in the output of the actuator torque.
   *
   * @frame       Sensor Frame
   * @units       Newton Meters
   */
  double systemNoiseMean_Sen_Nm[3];

  /*!
   * @brief       The standard deviation noise in the output of the actuator
   *              torque.
   *
   * @frame       Sensor Frame
   * @units       Newton Meters
   */
  double systemNoiseStandardDeviation_Sen_Nm[3];

  /*!
   * @brief       The noise amplitude in the output of the actuator torque.
   *
   * @frame       Sensor Frame
   * @units       Newton Meters
   */
  double systemNoiseAmplitude_Sen_Nm[3];

  /*!
   * @brief       Member which contains the max currents for each of the sensor
   *              axis.
   *
   * @frame       Sensor Frame
   * @units       Amperes
   */
  double maxCurrent_Sen_A[3];
} Magnetorquer_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETORQUER_PARAMSSTRUCT_H */