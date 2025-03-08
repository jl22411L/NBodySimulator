/*!
 *    @File:         JamSail_StateStruct.h
 *
 *    @Brief:        Header file containing state struct for JamSail
 *
 *    @Date:         08/07/2024
 *
 */

#ifndef H_JAMESAIL_STATESTRUCT_H
#define H_JAMESAIL_STATESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"
#include "Sensors/Gyro/DataStructs/Gyro_StateStruct.h"
#include "Sensors/Magnetometer/DataStructs/Magnetometer_StateStruct.h"
#include "Sensors/SunSensor/DataStructs/SunSensor_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"

typedef struct JamSail_StateStruct
{
  /* ------------------------------------------------------------------------ *
   * Satellite Members
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Vector from JamSail to the sun in the fixed frame. This is the
   *            true value of the vector with no noise or errors added on.
   *
   * @frame     Fixed Frame
   * @units     m
   */
  double trueSunVector_m_fix[3];

  /*!
   * @brief     Vector from JamSail to the sun in the body frame. This is the
   *            true value of the vector with no noise or errors added on.
   *
   * @frame     Body Frame
   * @units     m
   */
  double trueSunVector_m_bod[3];

  /*!
   * @brief     Vector from of magneitc field at JamSail in the fixed frame.
   *            This is the true value of the vector with no noise or errors
   *            added on.
   *
   * @frame     Fixed Frame
   * @units     m
   */
  double trueMagneticFieldVector_m_fix[3];

  /*!
   * @brief     Vector from of magneitc field at JamSail in the body frame.
   *            This is the true value of the vector with no noise or errors
   *            added on.
   *
   * @frame     Body Frame
   * @units     m
   */
  double trueMagneticFieldVector_m_bod[3];

  /* ------------------------------------------------------------------------ *
   * EKF State Members
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Member which holds the kalman gain of the EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double kalmanGain[7][3];

  /*!
   * @brief     Member which holds the estimate of the measurement of the EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double measurementEstimate[3];

  /*!
   * @brief     Member which holds the sensor measurements of the EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double sensorMeasurement[3];

  /*!
   * @brief     Member which holds the error covariance matrix of the EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double errorCovariance[7][7];

  /*!
   * @brief     Member which holds the error covariance derivitive matrix of the
   *            EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double errorCovarianceDerivitive[7][7];

  /*!
   * @brief     Member which holds the measurement jacobian of the EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double measurementJacobian[3][7];

  /*!
   * @brief     Member which holds the state jacobian of the EKS.
   *
   * @frame     N/A
   * @units     N/A
   */
  double stateJacobian[7][7];

  /*!
   * @brief     Member which holds the state estimation of the quaternion from
   *            the EKf.
   *
   * @frame     Fixed Frame to Body Frame
   * @units     N/A
   */
  double quaternionEstimate_InertCenToBod[4];

  /*!
   * @brief     Member which holds the state estimation of the angular velocity
   *            from the EKf.
   *
   * @frame     Body Frame
   * @units     radians per second
   */
  double angularVelocityEstimate_Bod_rads[3];

  // /*!
  //  * @brief     Member which holds the state estimation of earths magnetic
  //  field
  //  *            from the EKf in the body frame.
  //  *
  //  * @frame     Body Frame
  //  * @units     Nano Teslas
  //  */
  // double magneticFieldEstimate_Bod_nT[3];

  // /*!
  //  * @brief     Member which holds the state estimation of the first order
  //  *            derivitive of earths magnetic field from the EKf in the body
  //  *            frame.
  //  *
  //  * @frame     Body Frame
  //  * @units     Nano Teslas Per Second
  //  */
  // double magneticFieldFirstDerivitiveEstimate_Bod_nT[3];

  // /*!
  //  * @brief     Member which holds the state estimation of the second order
  //  *            derivitive of earths magnetic field from the EKf in the body
  //  *            frame.
  //  *
  //  * @frame     Body Frame
  //  * @units     Nano Teslas Per Second Squared
  //  */
  // double magneticFieldSecondDerivitiveEstimate_Bod_nT[3];

  GArchive ekfArchive;

  /* ------------------------------------------------------------------------ *
   * Sensor State Structs
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Struct which keeps track of the state of the sun sensor on
   *            JamSail.
   *
   * @frame     N/A
   * @units     N/A
   */
  SunSensor_State sunSensor_state;

  /*!
   * @brief     Struct which keeps track of the state of the magnetometer on
   *            JamSail.
   *
   * @frame     N/A
   * @units     N/A
   */
  Magnetometer_State magnetometer_state;

  /*!
   * @brief     Struct which keeps track of the state of the gyro on JamSail.
   *
   * @frame     N/A
   * @units     N/A
   */
  Gyro_State gyro_state;

  /* ------------------------------------------------------------------------ *
   * Actuator State Structs
   * ------------------------------------------------------------------------ */

  /*!
   * @brief    Struct which keeps track of the state of the magnetoruer on
   *           JamSail.
   *
   * @frame    N/A
   * @units    N/A
   */
  Magnetorquer_State magnetorquer_state;

  /* ------------------------------------------------------------------------ *
   * Simulation Members
   * ------------------------------------------------------------------------ */

  /*!
   * @details   This member contains the address to the satellite body struct
   *            for JamSail.
   */
  SatelliteBody_State *p_satelliteBody_state;

} JamSail_State;

#ifdef __cplusplus
}
#endif

#endif /* H_JAMESAIL_STATESTRUCT_H */
