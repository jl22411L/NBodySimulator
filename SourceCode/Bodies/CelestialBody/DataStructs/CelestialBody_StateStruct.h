/*
 *    @File:         CelestialBody_StateStruct.h
 *
 *    @ Brief:       State struct of the satellite
 *
 *    @ Date:        17/03/2024
 *
 */

#ifndef H_CELESTIALBODY_STATESTRUCT_H
#define H_CELESTIALBODY_STATESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct CelestialBody_StateStruct
{
  /*!
   * @brief     Rigid Body struct which is used for the dynamic simulations
   *
   * @frame     N/A
   * @unit      N/A
   */
  RigidBody_State rigidBody_state;

  /*!
   * @brief     Double which holds the equatorial radius of the body.
   *
   * @frame     N/A
   * @unit      m
   */
  double equitorialRadius_m;

  /*!
   * @brief     Quaternion which represents the rotation from the fix frame to
   *            the inertial frame of the celestial body. In principle this
   *            quaternion should be a constant but their may be unique cases
   *            where it changes, hence it is in the state struct.
   *
   * @frame     FixToCenInert
   * @unit      N/A
   */
  double quaternion_FixToCenInert[4];

  /*!
   * @brief     Double which represents the sidereal time of the body.
   *
   * @unit      Seconds
   * @frame     N/A
   */
  double sideRealTime_s;

  /*!
   * @details   Archive struct for RigidBody.
   *
   * @frame     N/A
   * @unit      N/A
   */
  GArchive celestialBodyArchive;

} CelestialBody_State;

#ifdef __cplusplus
}
#endif

#endif /* H_CELESTIALBODY_STATESTRUCT_H */
