/*
 *    @File:
 *
 *    @ Brief:
 *
 *    @ Date:
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
#include "Gravity/ConstantDefs/Gravity_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Gravity_findGravityForceBetweenBodies(
    RigidBody_State *p_internalRigidBody_in,
    RigidBody_State *p_externalRigidBody_in,
    double          *p_internalBodyGravityVector_N_fixed_out)
{
  /* defining local variables */
  double relativePositionVector_m_Fixed[3];
  double relativePositionMagnitude_m;
  double internalObjectMass_kg;
  double externalObjectMass_kg;
  double gravityScaler;
  int    i;

  /* Clearing local variables */
  GZero(&relativePositionVector_m_Fixed, double[3]);

  /* Find the relative position vector */
  GMath_matSub(&((p_internalRigidBody_in)->position_Fix_m[0]),
               3,
               1,
               &((p_externalRigidBody_in)->position_Fix_m[0]),
               3,
               1,
               &relativePositionVector_m_Fixed);

  /* Find the magnitude of the position vector */
  GMath_vectorMag(&relativePositionMagnitude_m,
                  &relativePositionVector_m_Fixed,
                  3);

  /* Find the masses of the objects */
  internalObjectMass_kg = (p_internalRigidBody_in->rigidBodyMass_kg);
  externalObjectMass_kg = (p_externalRigidBody_in->rigidBodyMass_kg);

  /* Find the scaler of the gravity vector */
  gravityScaler = -GRAVITY_UNIVERSAL_GRAVITATIONAL_CONSTANT *
                  internalObjectMass_kg * externalObjectMass_kg /
                  relativePositionMagnitude_m / relativePositionMagnitude_m /
                  relativePositionMagnitude_m;

  /* Find the components for the gravity force vector */
  for (i = 0; i < 3; i++)
  {
    *(p_internalBodyGravityVector_N_fixed_out + i) +=
        relativePositionVector_m_Fixed[i] * gravityScaler;
  }

  return GCONST_TRUE;
}
