/*
 *    @File:         SatelliteBody_findResultantForce.c
 *
 *    @ Brief:       Will find the resultant force for the Satellite body.
 *
 *    @ Date:        06/05/2024
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

int SatelliteBody_findResultantForce(
    SatelliteBody_State *p_satelliteBody_state_in)
{
  /* Defining local variables */
  int i;

  /* Clear resultance force. (This is to start from a fresh slate) */
  GZero(
      &p_satelliteBody_state_in->rigidBody_state.resultantForce_N_Fixed[0],
      double[3]);

  /* Add the gravity force to the resultant force */
  for (i = 0; i < 3; i++)
  {
    p_satelliteBody_state_in->rigidBody_state.resultantForce_N_Fixed[i] +=
        p_satelliteBody_state_in->rigidBody_state.gravityForce_N_Fixed[i];
  }

  return GCONST_TRUE;
}
