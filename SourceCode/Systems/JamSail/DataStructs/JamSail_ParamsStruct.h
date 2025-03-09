/*!
 *    @File:         JamSail_ParamsStruct.h
 *
 *    @Brief:        Header file which contains the params struct for JamSail.
 *
 *    @Date:         28/01/2025
 *
 */

#ifndef H_JAMSAIL_PARAMSSTRUCT_H
#define H_JAMSAIL_PARAMSSTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_ParamsStruct.h"
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"
#include "Sensors/Gyro/DataStructs/Gyro_ParamsStruct.h"
#include "Sensors/Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Sensors/SunSensor/DataStructs/SunSensor_ParamsStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_Const.h"

/* Generic Libraries */
/* None */

typedef struct JamSail_ParamsStruct
{
  /* ------------------------------------------------------------------------ *
   * Satellite Parameters
   * ------------------------------------------------------------------------ */

  /* None */

  /* ------------------------------------------------------------------------ *
   * Attitude Determination Parameters
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Matrix containing the coefficients of the sensor noise
   *            covariance for the EKF.
   *
   * @frame     N/A
   * @unit      N/A
   */
  double estimationEkfSensorNoiseCovariance[JAMSAIL_ESTIMATION_EKF_DEGREE_M]
                                           [JAMSAIL_ESTIMATION_EKF_DEGREE_M];

  double semiMajorAxis_km;
  double eccentricity;
  double inclination_rad;
  double argumentOfPerigee_rad;
  double raans_rad;
  double timeSincePeriapsis_s;

  /*!
   * @brief     Matrix containing the coefficients of the system noise
   *            covariance for the EKF.
   *
   * @frame     N/A
   * @unit      N/A
   */
  double systemNoiseCovariance[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];

  /*!
   * @brief     Params struct for IGRF model.
   *
   * @frame     N/A
   * @units     N/A
   */
  Igrf_Params igrfModel_params;

  /* ------------------------------------------------------------------------ *
   * Sensor Parameters
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Struct which contains the parameters of the Sun Sensor on
   *            JamSail.
   *
   * @frame     N/A
   * @unit      N/A
   */
  SunSensor_Params sunSensor_params;

  /*!
   * @brief     Struct which contains the parameters of the Magnetometer on
   *            JamSail.
   *
   * @frame     N/A
   * @unit      N/A
   */
  Magnetometer_Params magnetometer_params;

  /*!
   * @brief     Struct which contains the parameters of the Gyro on JamSail.
   *
   * @frame     N/A
   * @unit      N/A
   */
  Gyro_Params gyro_params;

  /* ------------------------------------------------------------------------ *
   * Actuator Parameters
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Struct which contains the parameters of the magnetorquer on
   *            JamSail
   *
   * @frame     N/A
   * @units     N/A
   */
  Magnetorquer_Params magnetorquer_params;

} JamSail_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_PARAMSSTRUCT_H */