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
  /* Write values to CSV file */
  GArchive_writeLine(&p_celestialBody_state_in->celestialBodyArchive);

  return GCONST_TRUE;
}
