/*
 *    @File:         SatelliteBody_step.c
 *
 *    @ Brief:       Step function for the satellite body
 *
 *    @ Date:
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"
#include "SatelliteBody/PrivateFunctions/SatelliteBody_PrivateFunctions.h"

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"

int SatelliteBody_step(SatelliteBody_State *p_satelliteBody_state_in)
{
  /*--------------------------------------------------------------------------*
   *                           PRE STEP CALCULATIONS                          *
   *--------------------------------------------------------------------------*/

  /* Find the resultant force on the body */
  SatelliteBody_findResultantForce(p_satelliteBody_state_in);

  /*--------------------------------------------------------------------------*
   *                         ARCHIVE SATELLITE BODY                           *
   *--------------------------------------------------------------------------*/

  /* Write archive for satellite body */
  SatelliteBody_archiveData(p_satelliteBody_state_in);

  /*--------------------------------------------------------------------------*
   *                                  STEP                                    *
   *--------------------------------------------------------------------------*/

  /* None */

  /*--------------------------------------------------------------------------*
   *                             STEP RIGID BODY                              *
   *--------------------------------------------------------------------------*/

  /* Step the Rigid Body */
  RigidBody_step(&p_satelliteBody_state_in->rigidBody_state);

  return GCONST_TRUE;
}
