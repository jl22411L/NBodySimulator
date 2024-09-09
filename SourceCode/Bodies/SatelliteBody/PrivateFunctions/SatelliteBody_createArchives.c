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

  /* Write header for archive */
  GArchive_writeHeader(&p_satelliteBody_state_in->satelliteBodyArchive);

  /*-------------------------------------------------------------------------*
   *                       SATELLITE BODY STATE STRUCT
   *-------------------------------------------------------------------------*/
  /* None */

  return GCONST_TRUE;
}
