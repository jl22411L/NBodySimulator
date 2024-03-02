/*
 *    @File:         SatelliteBody_step.c
 *
 *    @ Brief:       Step function for the satellite body
 *
 *    @ Date:
 *
 */

/* Function Includes */
#include "BodyTypes/RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "SatelliteBody/StructDefs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int SatelliteBody_step(SatelliteBody_State *p_sat_state)
{
  /* Find the resultant acceleration of the satellite*/
  p_sat_state->rigidBody_state->acceleration =
      p_sat_state->resultanceForce_N_Fixed / p_sat_state->rigidBody_state.mass;

  /* Step the Rigid Body */
  RigidBody_step(&p_sat_state->rigidBody_state);

  return GCONST_TRUE;
}
