/*
 *    @File:         SatelliteBody_createArchives.c
 *
 *    @ Brief:       Creates archives for SatelliteBody
 *
 *    @ Date:        17/03/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int CelestialBody_createArchives(
    CelestialBody_State *p_celestialBody_state_in,
    const char          *p_bodyName_in)
{
  /* Defining local variables */
  char buffer[GCONST_BUFFER_1024];

  /* Clearing buffer */
  GZero(&buffer[0], char[GCONST_BUFFER_1024]);

  /* Create directory to body archive */
  sprintf(buffer, "Bodies/%s/OutputData/CelestialBody", p_bodyName_in);

  /* Create archive */
  GArchive_init(&p_celestialBody_state_in->celestialBodyArchive, buffer);

  /*-------------------------------------------------------------------------*
   *                       SATELLITE BODY STATE STRUCT
   *-------------------------------------------------------------------------*/
  /* Add gravity force vector columns */
  GArchive_addCol(
      &p_celestialBody_state_in->celestialBodyArchive,
      "gravityForce_N_Fixed",
      3,
      1);

  /* Add resultant force vector columns */
  GArchive_addCol(
      &p_celestialBody_state_in->celestialBodyArchive,
      "resultantForce_N_Fixed",
      3,
      1);

  /* Add resultant moment vector columns */
  GArchive_addCol(
      &p_celestialBody_state_in->celestialBodyArchive,
      "resultantMoment_Nm_Bod",
      3,
      1);

  return GCONST_TRUE;
}
