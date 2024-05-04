/*
 *    @File:         Gravity_dualBodyGravityModule.c
 *
 *    @ Brief:       Finds the gravity force between two bodies
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
#include "Gravity/ConstantDefs/Gravity_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int Gravity_dualBodyGravityModel(RigidBody_State **p_rigidBodyArray_in)
{
  /* Declaring local variables */
  RigidBody_State *p_rigidBody1;
  RigidBody_State *p_rigidBody2;
  double           gravityVectorBody1[3];
  uint8_t          i;

  /* Clear local variables */
  GZero(&gravityVectorBody1[0], double[3]);

  /*
   * Unload the rigid bodies. It is assumed that there are only 2 bodies in the
   * rigid body array.
   */
  p_rigidBody1 = *(p_rigidBodyArray_in + 0);
  p_rigidBody2 = *(p_rigidBodyArray_in + 1);

  /* Clear the previous gravity force values */
  GZero(&(p_rigidBody1->gravityForce_N_Fixed[0]), double[3]);
  GZero(&(p_rigidBody2->gravityForce_N_Fixed[0]), double[3]);

  Gravity_findGravityForceBetweenBodies(
      p_rigidBody1,
      p_rigidBody2,
      &gravityVectorBody1[0]);

  /* Assign the gravity force to the bodies */
  for (i = 0; i < 3; i++)
  {
    /* Assign the gravity vector to body 1 */
    p_rigidBody1->gravityForce_N_Fixed[i] = gravityVectorBody1[i];

    /* Assign the gravity vector to body 2 */
    p_rigidBody2->gravityForce_N_Fixed[i] = -gravityVectorBody1[i];
  }

  return GCONST_TRUE;
}
