/*
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
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct JamSail_StateStruct
{
  /* ######################################################################## *
   * SATELLITE MEMBERS
   * ######################################################################## */

  /*!
   * @brief     Vector from JamSail to the sun in the fixed frame. This is the
   *            true value of the vector with no noise or errors added on.
   *
   * @unit      m
   * @frame     Fixed Frame
   */
  double trueSunVector_m_fix[3];

  /*!
   * @brief     Vector from JamSail to the sun in the body frame. This is the
   *            true value of the vector with no noise or errors added on.
   *
   * @unit      m
   * @frame     Body Frame
   */
  double trueSunVector_m_bod[3];

  /*!
   * @brief     Vector from of magneitc field at JamSail in the fixed frame.
   *            This is the true value of the vector with no noise or errors
   *            added on.
   *
   * @unit      m
   * @frame     Fixed Frame
   */
  double trueMagneticFieldVector_m_fix[3];

  /*!
   * @brief     Vector from of magneitc field at JamSail in the body frame.
   *            This is the true value of the vector with no noise or errors
   *            added on.
   *
   * @unit      m
   * @frame     Body Frame
   */
  double trueMagneticFieldVector_m_bod[3];

  /* TODO: The intention here is to have the different models such as IMU and
   *       sun sensors here.
   */

  /* ######################################################################## *
   * SIMULATION MEMBERS
   * ######################################################################## */

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
