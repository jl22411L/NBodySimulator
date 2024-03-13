/*
 *    @File:         SatelliteBody_StateStruct.h
 *
 *    @ Brief:       State struct of the satellite
 *
 *    @ Date:        22/02/2024
 *
 */

#ifndef H_SATELLITEBODY_STATESTRUCT_H
#define H_SATELLITEBODY_STATESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyTypes/RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct SatelliteBody_StateStruct
{
  /*!
   * @brief   Resultant gravity force vector present on the satellite
   *
   * @unit    Newtons
   * @frame   Fixed Frame
   */
  double gravityForce_N_Fixed[3];

  /*!
   * @brief   Vector containing the resultant force of the satellite.
   *
   * @unit    Newtons
   * @frame   Fixed Frame
   */
  double resultantForce_N_Fixed[3];

  /*!
   * @brief   Vector containing the resultant Moment of the satellite.
   *
   * @unit    NewtonMeters
   * @frame   Body Frame
   */
  double resultantMoment_Nm_Bod[3];

  /*!
   * @brief   Rigid Body struct which is used for the dynamic simulations
   *
   * @unit    N/A
   * @frame   N/A
   */
  RigidBody_State rigidBody_state;

  /*!
   * @details   Archive struct for RigidBody.
   *
   * @unit      N/A
   * @frame     N/A
   */
  GArchive satelliteBodyArchive;

} SatelliteBody_State;

#ifdef __cplusplus
}
#endif

#endif /* H_SATELLITEBODY_STATESTRUCT_H */
