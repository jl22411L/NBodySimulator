/*
 *    @File:         Gravity_flatEarthGravityModel.c
 *
 *    @ Brief:       Finds gravity for a flat earth model
 *
 *    @ Date:        29/04/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "Gravity/DataStructs/Gravity_ParamsStruct.h"
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Gravity_flatEarthGravityModel(
    Gravity_Params   *p_gravityPrams_in,
    RigidBody_State **p_rigidBodyArray_in,
    int               nRigidBodies_in)
{
  /* Declare local variables */
  double  gravityForceAbs_N;
  uint8_t i;

  /* Iterate thorugh rigid bodies */
  for (i = 0; i < nRigidBodies_in; i++)
  {
    /* Find the gravity force present on the rigid body */
    /* TODO:  Could add a feature that the changes in the gravitational
     *        acceleration are found with altitude. May have to incorporate an
     *        altitude member in the rigid body struct, but that only applies if
     *        you have terrain maps and need to differentiate between height and
     *        altitude.
     *
     *        In the beginning, height may be enough.
     */
    gravityForceAbs_N =
        ((*(p_rigidBodyArray_in + i))->rigidBodyMass_kg) *
        (p_gravityPrams_in->seaLevelGravitationalAcceleration_ms2);

    /* Apply gravity force to rigid body. Negative, becaused fixed frame
     * is pointing towards the sky and model assumes gravity is pointing
     * towards the ground. */
    ((*(p_rigidBodyArray_in + i))->gravityForce_N_Fixed[2]) =
        -gravityForceAbs_N;

    /* Clear the gravity foce variable in preperation for next iteration */
    GZero(&gravityForceAbs_N, double);
  }

  return GCONST_TRUE;
}
