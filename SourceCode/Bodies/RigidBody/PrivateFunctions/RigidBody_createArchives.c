/*
 *    @File:         RigidBody_createArchives.c
 *
 *    @ Brief:       Creates archives for Rigidbody
 *
 *    @ Date:        07/02/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int RigidBody_createArchives(
    RigidBody_State *p_rigidBody_state_in,
    const char      *p_bodyName_in)
{
  /* Defining local variables */
  char buffer[GCONST_BUFFER_1024];

  /* Clearing buffer */
  GZero(&buffer[0], char[GCONST_BUFFER_1024]);

  /* Create directory to body archive */
  sprintf(buffer, "Bodies/%s/OutputData/RigidBody", p_bodyName_in);

  /* Create archive */
  GArchive_init(&p_rigidBody_state_in->rigidBodyArchive, buffer);

  /* Add mass column */
  GArchive_addCol(&p_rigidBody_state_in->rigidBodyArchive, "mass", 1, 1);

  /* Add inertia matrix columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "inertiaMatrix",
      3,
      3);

  /* Add fixed frame accelerations columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "fixedFrameAcceleration_ms2",
      3,
      1);

  /* Add fixed frame velocities columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "fixedFrameVelocity_ms",
      3,
      1);

  /* Add angular position columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "position_m_Fix",
      3,
      1);

  /* Add angular acceleration columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "angularAcceleration_rads2_Bod",
      3,
      1);

  /* Add angular velocity columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "angularVelocity_rads_Bod",
      3,
      1);

  /* Add quaternion rate columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "quaternionRate_FixedToBody",
      4,
      1);

  /* Add quaternion columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "quaternion_FixedToBody",
      4,
      1);

  return GCONST_TRUE;
}
