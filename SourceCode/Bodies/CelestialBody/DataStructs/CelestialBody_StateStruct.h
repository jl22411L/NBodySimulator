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
  GArchive celestialBodyArchive;

} CelestialBody_State;

#ifdef __cplusplus
}
#endif

#endif /* H_CELESTIALBODY_STATESTRUCT_H */
