/*
 *    @File:         UavBody_step.c
 *
 *    @ Brief:       Step function for the uav body
 *
 *    @ Date:
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"

int UavBody_step(UavBody_State *p_uavBody_state_in)
{
  /*--------------------------------------------------------------------------*
   *                         ARCHIVE SATELLITE BODY                           *
   *--------------------------------------------------------------------------*/

  /* Write archive for satellite body */
  UavBody_archiveData(p_uavBody_state_in);

  /*--------------------------------------------------------------------------*
   *                                  STEP                                    *
   *--------------------------------------------------------------------------*/

  /* None */

  /*--------------------------------------------------------------------------*
   *                             STEP RIGID BODY                              *
   *--------------------------------------------------------------------------*/

  /* Step the Rigid Body */
  RigidBody_step(&p_uavBody_state_in->rigidBody_state);

  return GCONST_TRUE;
}
