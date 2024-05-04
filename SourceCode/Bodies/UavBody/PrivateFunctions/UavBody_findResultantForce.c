/*
 *    @File:         UavBody_findResultantForce.c
 *
 *    @ Brief:       Will find the resultant force for the UAV body.
 *
 *    @ Date:        04/05/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int UavBody_findResultantForce(UavBody_State *p_uavBody_state_in)
{
  /* Defining local variables */
  int i;

  /* Clear resultance force. (This is to start from a fresh slate) */
  GZero(
      &p_uavBody_state_in->rigidBody_state.resultantForce_N_Fixed[0],
      double[3]);

  /* Add the gravity force to the resultant force */
  for (i = 0; i < 3; i++)
  {
    p_uavBody_state_in->rigidBody_state.resultantForce_N_Fixed[i] +=
        p_uavBody_state_in->rigidBody_state.gravityForce_N_Fixed[i];
  }

  return GCONST_TRUE;
}
