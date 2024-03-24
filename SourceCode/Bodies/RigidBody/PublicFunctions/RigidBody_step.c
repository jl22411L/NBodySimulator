/*
 *    @File:         RigidBody_step.c
 *
 *    @ Brief:       Function which will step the rigid body forward in the
 *                   simulation. Should be called each time the simulation
 *                   steps.
 *
 *    @ Date:        20/02/2024
 *
 */

/* Function Includes */
#include "RigidBody/PrivateFunctions/RigidBody_PrivateFunctions.h"
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GIntegral/GIntegral.h"
#include "GUtilities/GUtilities.h"

int RigidBody_step(RigidBody_State *p_rigidBody_state_in)
{
  /*--------------------------------------------------------------------------*
   *                       FIND RESULTANT ACCELERATIONS                       *
   *--------------------------------------------------------------------------*/

  /* Find the translational acceleration of the rigid body */
  RigidBody_findTranslationalAcceleration(p_rigidBody_state_in);

  /* Find angular acceleration of the rigid body */
  RigidBody_findAngularAcceleration(p_rigidBody_state_in);

  /*--------------------------------------------------------------------------*
   *                                  ARCHIVE                                 *
   *--------------------------------------------------------------------------*/
  RigidBody_archiveData(p_rigidBody_state_in);

  /*--------------------------------------------------------------------------*
   *                                   STEP                                   *
   *--------------------------------------------------------------------------*/

  /* Integrate position vector */
  GIntegral_3x1Double(
      &p_rigidBody_state_in->position_m_Fix[0],
      &p_rigidBody_state_in->velocity_ms_Fix[0],
      Utilities.simTimeStep_s);

  /* Integrate velocity vector */
  GIntegral_3x1Double(
      &p_rigidBody_state_in->velocity_ms_Fix[0],
      &p_rigidBody_state_in->acceleration_ms2_Fix[0],
      Utilities.simTimeStep_s);

  /* Find quaternion rate from angular velocities */
  GMath_quaternionRateCalc(
      &p_rigidBody_state_in->quaternionRate_FixedToBody[0],
      &p_rigidBody_state_in->quaternion_FixedToBody[0],
      &p_rigidBody_state_in->angularVelocity_rads_Bod[0]);

  /* Integrate quaternion vector */
  GIntegral_4x1Double(
      &p_rigidBody_state_in->quaternion_FixedToBody[0],
      &p_rigidBody_state_in->quaternionRate_FixedToBody[0],
      Utilities.simTimeStep_s);

  /* Normalise the quaternion */
  GMath_vectorNorm(
      &p_rigidBody_state_in->quaternion_FixedToBody[0],
      &p_rigidBody_state_in->quaternion_FixedToBody[0],
      4);

  /* Integrate angular velocity vector */
  GIntegral_3x1Double(
      &p_rigidBody_state_in->angularVelocity_rads_Bod[0],
      &p_rigidBody_state_in->angularAcceleration_rads2_Bod[0],
      Utilities.simTimeStep_s);

  return GCONST_TRUE;
}
