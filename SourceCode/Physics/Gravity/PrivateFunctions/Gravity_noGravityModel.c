/*
 *    @File:         Gravity_noGravityModel.c
 *
 *    @ Brief:       Sets gravity force of all rigid bodies to 0
 *
 *    @ Date:        29/04/2024
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

int Gravity_noGravityModel(RigidBody_State **p_rigidBody_array_in,
                           int               nRigidBodies_in)
{
  /* Defining Local variables */
  uint8_t i;
  uint8_t j;

  /* Iterate thorugh rigid bodies setting the gravity force to 0 */
  for (i = 0; i < nRigidBodies_in; i++)
  {
    /* Set each element in the gravity vector to 0 */
    for (j = 0; j < 3; j++)
    {
      (*(p_rigidBody_array_in + i))->gravityForce_N_Fixed[j] = 0;
    }
  }

  return GCONST_TRUE;
}
