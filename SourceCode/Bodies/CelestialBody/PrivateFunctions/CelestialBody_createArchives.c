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

  /* Write header for archive */
  GArchive_writeHeader(&p_celestialBody_state_in->celestialBodyArchive);

  /*-------------------------------------------------------------------------*
   *                       CELESTIAL BODY STATE STRUCT                       *
   *-------------------------------------------------------------------------*/
  /* None */

  return GCONST_TRUE;
}
