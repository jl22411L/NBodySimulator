/*
 *    @File:         SatelliteBody_terminate.c
 *
 *    @ Brief:       Terminates the satellite body
 *
 *    @ Date:        11/03/2024
 *
 */

/* Function Includes */
#include "BodyTypes/RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int SatelliteBody_terminate(SatelliteBody_State *p_satelliteBody_in)
{

  /* Terminate Rigid Body */
  RigidBody_terminate(&p_satelliteBody_in->rigidBody_state);

  /* Close archive */
  GArchive_close(&p_satelliteBody_in->satelliteBodyArchive);

  return GCONST_TRUE;
}
