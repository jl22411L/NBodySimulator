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
/* None */

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

  /* ------2------------------------------------------------------------------ *
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
