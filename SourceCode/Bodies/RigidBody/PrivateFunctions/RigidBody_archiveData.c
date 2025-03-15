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
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

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
  GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                  p_rigidBody_state_in->rigidBodyMass_kg);

  /* Writing Inertia Matrix to archive */
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                      p_rigidBody_state_in->inertiaMatrix_Bod_kgm2[i][j]);
    }
  }

  /* Writing gravity force to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->gravityForce_N_Fixed[i]);
  }

  /* Writing resultant force to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->resultantForce_N_Fixed[i]);
  }

  /* Writing fixed frame acceleration to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->acceleration_ms2_Fix[i]);
  }

  /* Writing fixed frame velocity to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->velocity_ms_Fix[i]);
  }

  /* Writing fixed frame velocity to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->position_Fix_m[i]);
  }

  /* Writing resultant moment to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->resultantMoment_Nm_Bod[i]);
  }

  /* Writing angular acceleration to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->angularAcceleration_rads2_Bod[i]);
  }

  /* Writing angular velocity to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->angularVelocity_rads_Bod[i]);
  }

  /* Writing quaternion rate to archive */
  for (i = 0; i < 4; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->quaternionRate_FixToBody[i]);
  }

  /* Writing quaternion to archive */
  for (i = 0; i < 4; i++)
  {
    GArchive_addVal(&p_rigidBody_state_in->rigidBodyArchive,
                    p_rigidBody_state_in->quaternion_FixToBody[i]);
  }

  GArchive_writeLine(&p_rigidBody_state_in->rigidBodyArchive);

  return GCONST_TRUE;
}
