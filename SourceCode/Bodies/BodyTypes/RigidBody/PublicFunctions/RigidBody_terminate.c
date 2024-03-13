/*
 *    @File:         RigidBody_terminate.c
 *
 *    @ Brief:       Function which closes the rigid body archive and releases
 *                   any memory.
 *
 *    @ Date:        11/03/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyTypes/RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int RigidBody_terminate(RigidBody_State *p_rigidBody_state_in)
{
  /* Close archive */
  GArchive_close(&p_rigidBody_state_in->rigidBodyArchive);

  return GCONST_TRUE;
}
