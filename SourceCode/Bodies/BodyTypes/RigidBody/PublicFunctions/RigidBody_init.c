/*
 *    @File:         RigidBody_init.c
 *
 *    @ Brief:       Function which loads the parameters into the Rigid Body
 *
 *    @ Date:        24/01/2024
 *
 */

/* Function Includes */
#include "BodyTypes/RigidBody/PrivateFunctions/RigidBody_PrivateFunctions.h"
#include "BodyTypes/RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "BodyTypes/RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int RigidBody_init(
    RigidBody_State *p_rigidBody_state_in,
    const char      *p_paramFilename_in)
{
  /* Declare local variables */
  dictionary  **dic;
  GParser_State GParser_state;

  /* Zeroing Local variables */
  GZero(&GParser_state, GParser_State);
  GZero(&dic, dictionary **);

  /*---------------------------- LOAD PARAMETERS ----------------------------*/

  /* Load parameters of the body */
  dic = GParser_loadParams(&GParser_state, p_paramFilename_in);

  /* Load mass into body*/
  GParser_loadDouble(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->mass),
      "InertiaProperties:mass");

  /* Load Inertia matrix into body */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->inertiaMatrix[0][0]),
      "InertiaProperties:Inertia",
      3,
      3);

  /* Load initial fixed frame acceleration */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->acceleration_ms2_Fix[0]),
      "TranslationalProperties:fixedFrameAcceleration",
      3,
      1);

  /* Load initial fixed frame velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->velocity_ms_Fix[0]),
      "TranslationalProperties:fixedFrameVelocity",
      3,
      1);

  /* Load initial position */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->position_m[0]),
      "TranslationalProperties:position",
      3,
      1);

  /* Load initial angular acceleration */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->angularAcceleration_rads2[0]),
      "AngularProperties:angularAcceleration",
      3,
      1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->angularVelocity_rads[0]),
      "AngularProperties:angularVelocity",
      3,
      1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->quaternionRateFixed2Body[0]),
      "AngularProperties:quaternionRate",
      4,
      1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_rigidBody_state_in->quaternionFixed2Body[0]),
      "AngularProperties:quaternion",
      4,
      1);

  GParser_closeParams(&GParser_state, dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  RigidBody_createArchives(p_rigidBody_state_in);

  return GCONST_TRUE;
}
