/*
 *    @File:         SatelliteBody_archiveData.c
 *
 *    @ Brief:       Archives the bodies state members
 *
 *    @ Date:        05/02/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "BodyTypes/RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int SatelliteBody_archiveData(SatelliteBody_State *p_satelliteBody_state_in)
{
  /* Declaring local variables */
  uint8_t i;
  uint8_t j;

  /* Writing gravity vector to archive to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_satelliteBody_state_in->satelliteBodyArchive,
        p_satelliteBody_state_in->gravityForce_N_Fixed[i]);
  }

  /* Writing resultant foce vector to archive to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_satelliteBody_state_in->satelliteBodyArchive,
        p_satelliteBody_state_in->resultantForce_N_Fixed[i]);
  }

  /* Writing resultant moment vector to archive to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_satelliteBody_state_in->satelliteBodyArchive,
        p_satelliteBody_state_in->resultantMoment_Nm_Bod[i]);
  }

  /* Write values to CSV file */
  GArchive_writeLine(&p_satelliteBody_state_in->satelliteBodyArchive);

  return GCONST_TRUE;
}
