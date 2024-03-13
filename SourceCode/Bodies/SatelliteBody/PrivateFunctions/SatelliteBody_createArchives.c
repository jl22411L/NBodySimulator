/*
 *    @File:         SatelliteBody_createArchives.c
 *
 *    @ Brief:       Creates archives for SatelliteBody
 *
 *    @ Date:        09/03/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int SatelliteBody_createArchives(
    SatelliteBody_State *p_satelliteBody_state_in,
    const char          *p_bodyName_in)
{
  /* Defining local variables */
  char buffer[GCONST_BUFFER_1024];

  /* Clearing buffer */
  GZero(&buffer[0], char[GCONST_BUFFER_1024]);

  /* Create directory to body archive */
  sprintf(buffer, "Bodies/%s/OutputData/SatelliteBody", p_bodyName_in);

  /* Create archive */
  GArchive_init(&p_satelliteBody_state_in->satelliteBodyArchive, buffer);

  /*-------------------------------------------------------------------------*
   *                       SATELLITE BODY STATE STRUCT
   *-------------------------------------------------------------------------*/
  /* Add gravity force vector columns */
  GArchive_addCol(
      &p_satelliteBody_state_in->satelliteBodyArchive,
      "gravityForce_N_Fixed",
      3,
      1);

  /* Add resultant force vector columns */
  GArchive_addCol(
      &p_satelliteBody_state_in->satelliteBodyArchive,
      "resultantForce_N_Fixed",
      3,
      1);

  /* Add resultant moment vector columns */
  GArchive_addCol(
      &p_satelliteBody_state_in->satelliteBodyArchive,
      "resultantMoment_Nm_Bod",
      3,
      1);

  return GCONST_TRUE;
}
