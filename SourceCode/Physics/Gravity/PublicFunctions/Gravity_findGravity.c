/*
 *    @File:         Gravity_findSatelliteGravity.c
 *
 *    @ Brief:       Finds gravity force on satellites
 *
 *    @ Date:        20/03/2024
 *
 */

#include <math.h>

/* Function Includes */
#include "Gravity/PrivateFunctions/Gravity_PrivateFunctions.h"

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
#include "Gravity/ConstantDefs/Gravity_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int Gravity_findGravity(
    RigidBody_State *p_rigidBodyArray_in,
    int              nRigidBoies_in)
{
  /* Defining Local Variables */
  int i;
  int j;
  int k;

  /* Iterate through each body and find resultant gravity force */
  for (i = 0; i < nRigidBoies_in; i++)
  {
    /* Clear gravity vector for internal body */
    GZero((p_rigidBodyArray_in + i), double[3]);

    /* Find a gravity force for the internal body by iterating through all
     * the external bodies and acumilating the gravity forces caused by them.
     */
    for (j = 0; j < nRigidBoies_in; j++)
    {
      /* For all bodies except the current one, find the effect of gravity */
      if (j != i)
      {
        Gravity_findGravityForceBetweenBodies(
            (p_rigidBodyArray_in + i),
            (p_rigidBodyArray_in + j),
            &p_rigidBodyArray_in->gravityForce_N_Fixed[0]);
      }
    }
  }

  return GCONST_TRUE;
}
