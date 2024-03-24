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
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int SatelliteBody_archiveData(SatelliteBody_State *p_satelliteBody_state_in)
{
  /* None */

  return GCONST_TRUE;
}
