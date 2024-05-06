/*
 *    @File:         CelestialBody_step.c
 *
 *    @ Brief:       Step function for the satellite body
 *
 *    @ Date:        17/03/2024
 *
 */

/* Function Includes */
#include "CelestialBody/PrivateFunctions/CelestialBody_PrivateFunctions.h"
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
  /*--------------------------------------------------------------------------*
   *                           PRE STEP CALCULATIONS                          *
   *--------------------------------------------------------------------------*/

  /* Find the resultant force on the body */
  CelestialBody_findResultantForce(p_celestialBody_state_in);

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
