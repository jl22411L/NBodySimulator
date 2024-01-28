/*
 *    @File:         RigidBody_init.c
 *
 *    @ Brief:       Function which loads the parameters into the Rigid Body
 *
 *    @ Date:        24/01/2024
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int RigidBody_init(RigidBody_State *p_Rigidbody_state)
{
  /* Declare local variables */
  dictionary  **dic;
  GParser_State GParser_state;

  /* Zeroing Local variables */
  GZero(&GParser_state, GParser_State);
  GZero(&dic, dictionary **);

  /* Load parameters of the body */
  dic = GParser_loadParams(&GParser_state, "Parameters/RigidBody_params.ini");

  /* Load mass into body*/
  GParser_loadDouble(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_mass),
      "InertiaProperties:mass");

  /* Load Inertia matrix into body */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_inertiaMatrix[0][0]),
      "InertiaProperties:Inertia",
      3,
      3);

  /* Load initial body frame acceleration */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_bodyFrameAcceleration_ms2[0]),
      "TranslationalProperties:bodyFrameAcceleration",
      3,
      1);

  /* Load initial body frame velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_bodyFrameVeclocity_ms[0]),
      "TranslationalProperties:bodyFrameVelocity",
      3,
      1);

  /* Load initial fixed frame acceleration */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_fixedFrameAcceleration_ms2[0]),
      "TranslationalProperties:fixedFrameAcceleration",
      3,
      1);

  /* Load initial fixed frame velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_fixedFrameVeclocity_ms[0]),
      "TranslationalProperties:fixedFrameVelocity",
      3,
      1);

  /* Load initial position */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_position_m[0]),
      "TranslationalProperties:position",
      3,
      1);

  /* Load initial angular acceleration */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_angularAcceleration_rads2[0]),
      "AngularProperties:angularAcceleration",
      3,
      1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_angularVelocity_rads[0]),
      "AngularProperties:angularVelocity",
      3,
      1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_quaternionRateFixed2Body[0]),
      "AngularProperties:quaternionRate",
      4,
      1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(
      &GParser_state,
      dic,
      &(p_Rigidbody_state->RigidBody_quaternionFixed2Body[0]),
      "AngularProperties:quaternion",
      4,
      1);

  GParser_closeParams(&GParser_state, dic);

  return GCONST_TRUE;
}