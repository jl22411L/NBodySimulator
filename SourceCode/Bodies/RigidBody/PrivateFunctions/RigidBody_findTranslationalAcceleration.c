/*
 *    @File:         RigidBody_findTranslationalAcceleration.c
 *
 *    @ Brief:       Finds the translational acceleration of the rigid body.
 *
 *    @ Date:        24/03/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int RigidBody_findTranslationalAcceleration(
    RigidBody_State *p_rigidBody_state_in)
{
  /* Define local variables */
  uint8_t i;

  /* Find the acceleration for each component of the acceleration vector */
  for (i = 0; i < 3; i++)
  {
    p_rigidBody_state_in->acceleration_ms2_Fix[i] =
        (p_rigidBody_state_in->resultantForce_N_Fixed[i]) /
        (p_rigidBody_state_in->rigidBodyMass_kg);
  }

  return GCONST_TRUE;
}
