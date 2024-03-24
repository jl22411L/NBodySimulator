/*
 *    @File:         Gravity_findSatelliteGravity.c
 *
 *    @ Brief:       Finds gravity force on satellites
 *
 *    @ Date:        20/03/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Gravity_findSatelliteGravity(
    SatelliteBody_State *p_satelliteBodyArray_in,
    int                  nSatelliteBodies,
    CelestialBody_State *p_celestialBodyArray_in,
    int                  nCelestialBodies)
{
  /* Defining local variables */
  double gravityForceSum[3];
  int    i;
  int    j;

  /* Iterate through each satellite to find the total gravity vector */
  for (i = 0; i < nSatelliteBodies; i++)
  {}

  return GCONST_TRUE;
}
