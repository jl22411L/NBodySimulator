/*
 *    @File:         BodyMgr_StateStruct.h
 *
 *    @Brief:        Struct used to manage the bodies of the simulation.
 *
 *    @Date:         23/05/2024
 *
 */

#ifndef H_BOGY_MGR_STATE_STRUCT_H
#define H_BOGY_MGR_STATE_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct BodyMgr_StateStruct
{
  /*!
   * @details   Integer holding the number of bodies that are within the
   *            Simulation
   *
   * @unit      N/A
   * @frame     N/A
   */
  int nBodies;

  /*!
   * @details   Integer containing the number of standlone rigid bodies within
   *            the simulation. (This is not the total number of rigid bodies
   *            but bodies which are only rigid bodies. The total number of
   *            rigid bodies should equate to nBodies)
   *
   * @unit      N/A
   * @frame     N/A
   */
  int nRigidBodies;

  /*!
   * @details   Integer containing the number of Satellite Bodies within the
   *            Simulation.
   *
   * @unit      N/A
   * @frame     N/A
   */
  int nSatelliteBodies;

  /*!
   * @details   Integer containing the number of UAV Bodies within the
   *            Simulation.
   *
   * @unit      N/A
   * @frame     N/A
   */
  int nUavBodies;

  /*!
   * @details   Integer containing the number of Celestial Bodies within the
   *            Simulation.
   *
   * @unit      N/A
   * @frame     N/A
   */
  int nCelestialBodies;

  /*!
   * @details   Pointer to pointers of rigid bodies. This will contain an array
   *            of pointer that point to the rigid bodies within the simulation.
   *
   * @note      Reason it needs to be pointer of pointers is so that it is
   *            not a copy that is made but rather points to the place in
   *            memory where the rigid bodies are stored.
   *
   * @unit      N/A
   * @frame     N/A
   */
  RigidBody_State **p_rigidBodyList;

  /*!
   * @details   Pointer to pointers of Satellite bodies. This will contain an
   *            array of pointer that point to the rigid bodies within the
   *            simulation.
   *
   * @note      Reason it needs to be pointer of pointers is so that it is
   *            not a copy that is made but rather points to the place in
   *            memory where the Satellite bodies are stored.
   *
   * @unit      N/A
   * @frame     N/A
   */
  SatelliteBody_State **p_satelliteBodyList;

  /*!
   * @details   Pointer to pointers of UAV bodies. This will contain an array
   *            of pointer that point to the rigid bodies within the simulation.
   *
   * @note      Reason it needs to be pointer of pointers is so that it is
   *            not a copy that is made but rather points to the place in
   *            memory where the UAV bodies are stored.
   *
   * @unit      N/A
   * @frame     N/A
   */
  UavBody_State **p_uavBodyList;

  /*!
   * @details   Pointer to pointers of Celestial bodies. This will contain an
   *            array of pointer that point to the rigid bodies within the
   *            simulation.
   *
   * @note      Reason it needs to be pointer of pointers is so that it is
   *            not a copy that is made but rather points to the place in
   *            memory where the Celestial bodies are stored.
   *
   * @unit      N/A
   * @frame     N/A
   */
  CelestialBody_State **p_celestialBodyList;

} BodyMgr_State;

#ifdef __cplusplus
}
#endif

#endif /* H_BOGY_MGR_STATE_STRUCT_H */
