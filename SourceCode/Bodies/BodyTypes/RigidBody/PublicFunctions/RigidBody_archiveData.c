/*
 *    @File:         RigidBody_archiveState.c
 *
 *    @ Brief:       Archives the bodies state members
 *
 *    @ Date:        05/02/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyTypes/RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int RigidBody_archiveData(RigidBody_State *p_rigidBody_state_in)
{
  /* Declaring local variables */
  uint8_t i;
  uint8_t j;

  /* Writing mass to archive */
  GArchive_addVal(
      &p_rigidBody_state_in->rigidBodyArchive,
      p_rigidBody_state_in->mass);

  /* Writing Inertia Matrix to archive */
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      GArchive_addVal(
          &p_rigidBody_state_in->rigidBodyArchive,
          p_rigidBody_state_in->inertiaMatrix[i][j]);
    }
  }

  /* Writing fixed frame acceleration to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_rigidBody_state_in->rigidBodyArchive,
        p_rigidBody_state_in->fixedFrameAcceleration_ms2[i]);
  }

  /* Writing fixed frame velocity to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_rigidBody_state_in->rigidBodyArchive,
        p_rigidBody_state_in->fixedFrameVeclocity_ms[i]);
  }

  /* Writing fixed frame velocity to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_rigidBody_state_in->rigidBodyArchive,
        p_rigidBody_state_in->position_m[i]);
  }

  /* Writing angular acceleration to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_rigidBody_state_in->rigidBodyArchive,
        p_rigidBody_state_in->angularAcceleration_rads2[i]);
  }

  /* Writing angular velocity to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &p_rigidBody_state_in->rigidBodyArchive,
        p_rigidBody_state_in->angularVelocity_rads[i]);
  }

  /* Writing quaternion rate to archive */
  for (i = 0; i < 4; i++)
  {
    GArchive_addVal(
        &p_rigidBody_state_in->rigidBodyArchive,
        p_rigidBody_state_in->quaternionRateFixed2Body[i]);
  }

  /* Writing quaternion to archive */
  for (i = 0; i < 4; i++)
  {
    GArchive_addVal(
        &p_rigidBody_state_in->rigidBodyArchive,
        p_rigidBody_state_in->quaternionFixed2Body[i]);
  }

  GArchive_writeLine(&p_rigidBody_state_in->rigidBodyArchive);

  return GCONST_TRUE;
}
