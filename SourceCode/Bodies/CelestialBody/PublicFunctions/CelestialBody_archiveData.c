/*
 *    @File:         CelestialBody_archiveData.c
 *
 *    @ Brief:       Archives the bodies state members
 *
 *    @ Date:        17/03/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int CelestialBody_archiveData(CelestialBody_State *p_celestialBody_state_in)
{
  /* Declaring local variables */
  uint8_t i;
  uint8_t j;

  /* Writing gravity vector to archive to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_celestialBody_state_in->celestialBodyArchive,
        p_celestialBody_state_in->gravityForce_N_Fixed[i]);
  }

  /* Writing resultant foce vector to archive to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_celestialBody_state_in->celestialBodyArchive,
        p_celestialBody_state_in->resultantForce_N_Fixed[i]);
  }

  /* Writing resultant moment vector to archive to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_celestialBody_state_in->celestialBodyArchive,
        p_celestialBody_state_in->resultantMoment_Nm_Bod[i]);
  }

  /* Write values to CSV file */
  GArchive_writeLine(&p_celestialBody_state_in->celestialBodyArchive);

  return GCONST_TRUE;
}
