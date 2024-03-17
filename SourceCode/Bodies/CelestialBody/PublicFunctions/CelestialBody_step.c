/*
 *    @File:         CelestialBody_step.c
 *
 *    @ Brief:       Step function for the satellite body
 *
 *    @ Date:        17/03/2024
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"

int CelestialBody_step(CelestialBody_State *p_celestialBody_state_in)
{
  /* Defining Local Variables */
  double invMass;

  /* Finding the inverse of mass */
  invMass = 1 / p_celestialBody_state_in->rigidBody_state.mass;

  /*--------------------------------------------------------------------------*
   *                         CALCULATE ACCELERATIONS                          *
   *--------------------------------------------------------------------------*/

  /* Find the resultant acceleration of the satellite */
  GMath_matMul(
      &p_celestialBody_state_in->resultantForce_N_Fixed[0],
      3,
      1,
      &invMass,
      1,
      1,
      &p_celestialBody_state_in->rigidBody_state.acceleration_ms2_Fix[0]);

  /* Find the angulat acceleration of the satellite */
  RigidBody_findAngularAcceleration(
      &p_celestialBody_state_in->rigidBody_state,
      &p_celestialBody_state_in->resultantMoment_Nm_Bod[0]);

  /*--------------------------------------------------------------------------*
   *                         ARCHIVE SATELLITE BODY                           *
   *--------------------------------------------------------------------------*/

  /* Write archive for satellite body */
  CelestialBody_archiveData(p_celestialBody_state_in);

  /*--------------------------------------------------------------------------*
   *                                  STEP *
   *--------------------------------------------------------------------------*/

  /* None */

  /*--------------------------------------------------------------------------*
   *                             STEP RIGID BODY *
   *--------------------------------------------------------------------------*/

  /* Step the Rigid Body */
  RigidBody_step(&p_celestialBody_state_in->rigidBody_state);

  return GCONST_TRUE;
}
