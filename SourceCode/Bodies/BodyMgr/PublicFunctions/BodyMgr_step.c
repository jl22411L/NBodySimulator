/*
 *    @File:         BodyMgr_step.c
 *
 *    @Brief:        Steps all the bodies within the simulation.
 *
 *    @Date:         09/06/2024
 *
 */

/* Function Includes */
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"
#include "UavBody/PublicFunctions/UavBody_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int BodyMgr_step(BodyMgr_State *p_bodyMgr_state_in)
{
  /* Declare Local Variables */
  int i;

  /* Step Celestial Bodies */
  for (i = 0; i < p_bodyMgr_state_in->nCelestialBodies; i++)
  {
    CelestialBody_step(*(p_bodyMgr_state_in->p_celestialBodyList + i));
  }

  /* Step Satellite Bodies */
  for (i = 0; i < p_bodyMgr_state_in->nSatelliteBodies; i++)
  {
    SatelliteBody_step(*(p_bodyMgr_state_in->p_satelliteBodyList + i));
  }

  /* Step UAV Bodies */
  for (i = 0; i < p_bodyMgr_state_in->nUavBodies; i++)
  {
    UavBody_step(*(p_bodyMgr_state_in->p_uavBodyList + i));
  }
  return GCONST_TRUE;
}
