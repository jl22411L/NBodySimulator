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
  double sensorNoiseCovariance[JAMSAIL_EKF_DEGREE_M][JAMSAIL_EKF_DEGREE_M];

  /*!
   * @brief     Mass of Sun. Used in keplarian propogation.
   *
   * @frame     N/A
   * @unit      Kilograms
   */
  double sunMass_kg;

  /*!
   * @brief     Mass of earth. Used in keplarian propogation.
   *
   * @frame     N/A
   * @unit      Kilograms
   */
  double earthMass_kg;

  /*!
   * @brief     Quaternion which represents the rotation form the fix frame to
   *            earths inertical centric frame.
   *
   * @frame     N/A
   * @unit      n/A
   */
  double quaternion_FixToInertCen[4];

  /*!
   * @brief     Mass of jamSail. Used in keplarian propogation.
   *
   * @frame     N/A
   * @unit      Kilograms
   */
  double jamSailMass_kg;

  /*!
   * @brief     Side real time of earth.
   *
   * @frame     N/A
   * @unit      Seconds
   */
  double earthSideRealTime_s;

  /*!
   * @brief     Parameter which contains the magnitude of the average rotation
   *            speed of the earth.
   *
   * @frame     N/A
   * @unit      Radians per Seconds
   */
  double averageEarthRotationalSpeedMag_rads;

  /*!
   * @brief     Parameter which contains the equatorial radius of the earth.
   *
   * @frame     N/A
   * @unit      Meters
   */
  double earthEqutorialRadius_m;

  /*!
   * @brief     Semi major axis of JamSail
   *
   * @frame     N/A
   * @unit      Kilometers
   */
  double semiMajorAxis_km;

  /*!
   * @brief     Eccentricity of JamSail
   *
   * @frame     N/A
   * @unit      N/A
   */
  double eccentricity;

  /*!
   * @brief     Inclination of JamSail
   *
   * @frame     N/A
   * @unit      Radians
   */
  double inclination_rad;

  /*!
   * @brief     Argument of Perigee of JamSail
   *
   * @frame     N/A
   * @unit      Radians
   */
  double argumentOfPerigee_rad;

  /*!
   * @brief     Right Acension of Accending Nodes of JamSail
   *
   * @frame     N/A
   * @unit      Radians
   */
  double raans_rad;

  /*!
   * @brief     Matrix containing the coefficients of the sensor noise
   *            covariance for the EKF.
   *
   * @frame     N/A
   * @unit      N/A
   */
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
   * Attitude Control Parameters
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Proportional coefficient for detumbling control.
   *
   * @frame     N/A
   * @units     N/A
   */
  double detumblingProportionalCoefficient[3];

  /*!
   * @brief     Proportional coefficient for nominal control.
   *
   * @frame     N/A
   * @units     N/A
   */
  double nominalProportionalCoefficient[3];

  /*!
   * @brief     Derivitive coefficient for nominal control.
   *
   * @frame     N/A
   * @units     N/A
   */
  double nominalDerivitiveCoefficient[3];

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