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

int RigidBody_createArchives(RigidBody_State *p_rigidBody_state_in)
{

  /* Add mass column */
  GArchive_addCol(&p_rigidBody_state_in->rigidBodyArchive, "mass", 1, 1);

  /* Add inertia matrix columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "inertiaMatrix",
      3,
      3);

  /* Add body frame accelerations columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "bodyFrameAcceleration_ms2",
      3,
      1);

  /* Add body frame velocities columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "bodyFrameVeclocity_ms",
      3,
      1);

  /* Add fixed frame accelerations columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "fixedFrameAcceleration_ms2",
      3,
      1);

  /* Add fixed frame velocities columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "fixedFrameVeclocity_ms",
      3,
      1);

  /* Add angular position columns */
  GArchive_addCol(&p_rigidBody_state_in->rigidBodyArchive, "position_m", 3, 1);

  /* Add angular acceleration columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "angularAcceleration_rads2",
      3,
      1);

  /* Add angular velocity columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "angularVelocity_rads",
      3,
      1);

  /* Add quaternion rate columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "quaternionRateFixed2Body",
      4,
      1);

  /* Add quaternion columns */
  GArchive_addCol(
      &p_rigidBody_state_in->rigidBodyArchive,
      "quaternionFixed2Body",
      4,
      1);

  return GCONST_TRUE;
}