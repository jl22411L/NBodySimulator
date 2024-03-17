/*
 *    @File:         CelestialBody_terminate.c
 *
 *    @ Brief:       Terminates the satellite body
 *
 *    @ Date:        17/03/2024
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int CelestialBody_terminate(CelestialBody_State *p_celestialBody_in)
{

  /* Terminate Rigid Body */
  RigidBody_terminate(&p_celestialBody_in->rigidBody_state);

  /* Close archive */
  GArchive_close(&p_celestialBody_in->celestialBodyArchive);

  return GCONST_TRUE;
}
