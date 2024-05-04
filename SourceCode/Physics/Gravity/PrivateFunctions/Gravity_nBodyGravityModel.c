/*
 *    @File:         Gravity_nBodyGravityModel.c
 *
 *    @ Brief:       Finds the gravity force on N rigid bodies.
 *
 *    @ Date:        29/04/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "Gravity/PrivateFunctions/Gravity_PrivateFunctions.h"

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Gravity_nBodyGravityModel(
    RigidBody_State **p_rigidBodyArray_in,
    int               nRigidBoies_in)
{
  /* Defining Local Variables */
  uint8_t i;
  uint8_t j;
  uint8_t k;

  /* Iterate through each body and find resultant gravity force */
  for (i = 0; i < nRigidBoies_in; i++)
  {
    /* Clear gravity vector for internal body */
    GZero(&((*(p_rigidBodyArray_in + i))->gravityForce_N_Fixed[0]), double[3]);

    /* Find a gravity force for the internal body by iterating through all
     * the external bodies and acumilating the gravity forces caused by them.
     */
    for (j = 0; j < nRigidBoies_in; j++)
    {
      /* For all bodies except the current one, find the effect of
      gravity */
      if (j != i)
      {
        Gravity_findGravityForceBetweenBodies(
            (*(p_rigidBodyArray_in + i)),
            (*(p_rigidBodyArray_in + j)),
            &((*(p_rigidBodyArray_in + i))->gravityForce_N_Fixed[0]));
      }
    }
  }

  return GCONST_TRUE;
}
