/*
 *    @File:         BodyMgr_terminate.c
 *
 *    @Brief:        This removes all the pointers containing the addresses of
 *                   the different bodies along with freeing there memory from
 *                   the heap.
 *
 *    @Date:         03/06/2024
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Function Includes */
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"
#include "UavBody/PublicFunctions/UavBody_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int BodyMgr_terminate(BodyMgr_State *p_bodyMgr_state_in)
{
  /* Declare local variables */
  int i;

  /* -------------------------- RIGID BODIES --------------------------- */

  /* Iterate through all the rigid bodies */
  for (i = 0; i < p_bodyMgr_state_in->nRigidBodies; i++)
  {
    /* Terminate Body */
    RigidBody_terminate(*(p_bodyMgr_state_in->p_pureRigidBodyList + i));

    /* Free memory from Heap */
    free(*(p_bodyMgr_state_in->p_pureRigidBodyList + i));

    /* Assign pointer value of NULL */
    *(p_bodyMgr_state_in->p_pureRigidBodyList + i) = NULL;
  }

  /* Free memory of rigid body list from heap */
  free(p_bodyMgr_state_in->p_pureRigidBodyList);

  /* Set pointer to array of rigid bodies to NULL */
  p_bodyMgr_state_in->p_pureRigidBodyList = NULL;

  /* -------------------------- CELESTIAL BODIES --------------------------- */

  /* Iterate through all the celestial bodies */
  for (i = 0; i < p_bodyMgr_state_in->nCelestialBodies; i++)
  {
    /* Terminate Body */
    CelestialBody_terminate(*(p_bodyMgr_state_in->p_celestialBodyList + i));

    /* Free memory from Heap */
    free(*(p_bodyMgr_state_in->p_celestialBodyList + i));

    /* Assign pointer value of NULL */
    *(p_bodyMgr_state_in->p_celestialBodyList + i) = NULL;
  }

  /* Free memory of celestial body list from heap */
  free(p_bodyMgr_state_in->p_celestialBodyList);

  /* Set pointer to array of rigid bodies to NULL */
  p_bodyMgr_state_in->p_celestialBodyList = NULL;

  /* -------------------------- SATELLITE BODIES --------------------------- */

  /* Iterate through all the satellite bodies */
  for (i = 0; i < p_bodyMgr_state_in->nSatelliteBodies; i++)
  {
    /* Terminate Satellite Body */
    SatelliteBody_terminate(*(p_bodyMgr_state_in->p_satelliteBodyList + i));

    /* Free memory from Heap */
    free(*(p_bodyMgr_state_in->p_satelliteBodyList + i));

    /* Assign pointer value of NULL */
    *(p_bodyMgr_state_in->p_satelliteBodyList + i) = NULL;
  }

  /* Free memory of satellite body list from heap */
  free(p_bodyMgr_state_in->p_satelliteBodyList);

  /* Set pointer to array of rigid bodies to NULL */
  p_bodyMgr_state_in->p_satelliteBodyList = NULL;

  /* ----------------------------- UAV BODIES ------------------------------ */

  /* Iterate through all the UAV bodies */
  for (i = 0; i < p_bodyMgr_state_in->nUavBodies; i++)
  {
    /* Terminate UAV Body */
    UavBody_terminate(*(p_bodyMgr_state_in->p_uavBodyList + i));

    /* Free memory from Heap */
    free(*(p_bodyMgr_state_in->p_uavBodyList + i));

    /* Assign pointer value of NULL */
    *(p_bodyMgr_state_in->p_uavBodyList + i) = NULL;
  }

  /* Free memory of uav body list from heap */
  free(p_bodyMgr_state_in->p_uavBodyList);

  /* Set pointer to array of rigid bodies to NULL */
  p_bodyMgr_state_in->p_uavBodyList = NULL;

  /* ----------------------------- RIGID BODIES ---------------------------- */

  /* Free memory of rigid body list from heap */
  free(p_bodyMgr_state_in->p_rigidBodyPointerList);

  /* Set pointer to array of rigid bodies to NULL */
  p_bodyMgr_state_in->p_rigidBodyPointerList = NULL;

  return GCONST_TRUE;
}
