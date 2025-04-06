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
#include "JamSail/ConstantDefs/JamSail_AdcsStateEnum.h"
#include "JamSail/ConstantDefs/JamSail_Const.h"

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
  double kalmanGain[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_DEGREE_M];

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
  double errorCovariance[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];

  /*!
   * @brief     Member which holds the error covariance derivitive matrix of the
   *            EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double errorCovarianceDerivitive[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];

  /*!
   * @brief     Member which holds the measurement jacobian of the EKF.
   *
   * @frame     N/A
   * @units     N/A
   */
  double observationJacobian[JAMSAIL_EKF_DEGREE_M][JAMSAIL_EKF_ORDER_N];

  /*!
   * @brief     Member which holds the state jacobian of the EKS.
   *
   * @frame     N/A
   * @units     N/A
   */
  double stateJacobian[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];

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

  /*!
   * @brief     Member which holds the estimation of the magnetic field in
   *            the inertial centric frame. This vector should be normalised as
   *            the magnitude does not contain any information relating to
   *            attitude.
   *
   * @frame     Inertial Centric
   * @units     N/A (As is a normalised vector)
   */
  double magneticFieldEstimateNorm_InertCen[3];

  /*!
   * @brief     Member which holds the estimation of the magnetic field in
   *            the body frame. This vector should be normalised as
   *            the magnitude does not contain any information relating to
   *            attitude.
   *
   *            This is found using the estimate of the quaternion from the
   *            EKF. This is then compared to the body magnetic field found
   *            from the magnetometer.
   *
   * @frame     Body
   * @units     N/A (As is a normalised vector)
   */
  double magneticFieldEstimateNorm_Bod[3];

  /*!
   * @brief     Member which holds the estimation of the sun vector in
   *            the inertial centric frame. This vector should be normalised as
   *            the magnitude does not contain any information relating to
   *            attitude.
   *
   * @frame     Inertial Centric
   * @units     N/A (As is a normalised vector)
   */
  double sunVectorEstimateNorm_InertCen[3];

  /*!
   * @brief     Member which holds the estimation of the sun vecto in
   *            the body frame. This vector should be normalised as
   *            the magnitude does not contain any information relating to
   *            attitude.
   *
   *            This is found using the estimate of the quaternion from the
   *            EKF. This is then compared to the body magnetic field found
   *            from the magnetometer.
   *
   * @frame     Body
   * @units     N/A (As is a normalised vector)
   */
  double sunVectorEstimateNorm_Bod[3];

  /*!
   * @brief     Member which holds the estimation of the position of JamSail in
   *            the inertial centric frame
   *
   * @frame     Inertial Centric
   * @units     Meters
   */
  double positionEstimate_InertCen_m[3];

  /*!
   * @brief     Flag to indicate if the attitude was measured or estimated by
   *            the attitude determination algorithm.
   *
   *            GCONST_TRUE  = Attitude was Measured
   *            GCONST_FALSE = Attitude was Estimated
   *
   * @frame     N/A
   * @units     N/A
   */
  uint8_t attitudeMeasuredFlag : 1;

  /*!
   * @brief     Archive member for ekf.
   *
   * @unit      N/A
   * @frame     N/A
   */
  GArchive attitudeDeterminationArchive;

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
   * JamSail Generic Members
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Member which contains the state for JamSail's ADCS state
   *            machine.
   *
   * @frame    N/A
   * @units    N/A
   */
  JamSail_AdcsState adcsState;

  /* ------------------------------------------------------------------------ *
   * Simulation Members
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     This member contains the address to the satellite body struct
   *            for JamSail.
   *
   * @frame    N/A
   * @units    N/A
   */
  SatelliteBody_State *p_satelliteBody_state;

} JamSail_State;

#ifdef __cplusplus
}
#endif

#endif /* H_JAMESAIL_STATESTRUCT_H */
