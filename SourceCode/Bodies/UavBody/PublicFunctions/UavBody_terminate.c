/*
 *    @File:         UavBody_terminate.c
 *
 *    @ Brief:       Terminates the satellite body
 *
 *    @ Date:        02/05/2024
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int UavBody_terminate(UavBody_State *p_uavBody_in)
{

  /* Terminate Rigid Body */
  RigidBody_terminate(&p_uavBody_in->rigidBody_state);

  /* Close archive */
  GArchive_close(&p_uavBody_in->uavBodyArchive);

  return GCONST_TRUE;
}
