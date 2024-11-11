/*
 *    @File:         RigidBody_init.c
 *
 *    @ Brief:       Function which loads the parameters into the Rigid Body
 *
 *    @ Date:        24/01/2024
 *
 */

/* Function Includes */
#include "RigidBody/PrivateFunctions/RigidBody_PrivateFunctions.h"
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int RigidBody_init(RigidBody_State *p_rigidBody_state_in,
                   const char      *p_paramFilename_in)
{
  /* Declare local variables */
  dictionary   *dic;
  GParser_State GParser_state;

  /* Zeroing Local variables */
  GZero(&GParser_state, GParser_State);
  GZero(&dic, dictionary *);
  GZero(p_rigidBody_state_in, RigidBody_State);

  /* ------------------------------------------------------------------------ *
   *                             LOAD PARAMETERS                              *
   * ------------------------------------------------------------------------ */

  /* Load parameters of the body */
  dic = GParser_loadParams(&GParser_state, p_paramFilename_in);

  /* Load rigidBodyMass_kg into body*/
  GParser_loadDouble(&GParser_state,
                     dic,
                     &(p_rigidBody_state_in->rigidBodyMass_kg),
                     "InertiaProperties:rigidBodyMass_kg");

  /* Load Inertia matrix into body */
  GParser_loadDoubleArray(&GParser_state,
                          dic,
                          &(p_rigidBody_state_in->inertiaMatrix_kgm2_Bod[0][0]),
                          "InertiaProperties:Inertia_kgm2",
                          3,
                          3);

  /* Load initial fixed frame velocity */
  GParser_loadDoubleArray(&GParser_state,
                          dic,
                          &(p_rigidBody_state_in->velocity_ms_Fix[0]),
                          "TranslationalProperties:fixedFrameVelocity_ms",
                          3,
                          1);

  /* Load initial position */
  GParser_loadDoubleArray(&GParser_state,
                          dic,
                          &(p_rigidBody_state_in->position_m_Fix[0]),
                          "TranslationalProperties:fixedFramePosition_m",
                          3,
                          1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(&GParser_state,
                          dic,
                          &(p_rigidBody_state_in->angularVelocity_rads_Bod[0]),
                          "AngularProperties:angularVelocity_rads",
                          3,
                          1);

  /* Load initial angular velocity */
  GParser_loadDoubleArray(&GParser_state,
                          dic,
                          &(p_rigidBody_state_in->quaternion_FixedToBody[0]),
                          "AngularProperties:quaternion",
                          4,
                          1);

  /* Load the bodies name */
  GParser_loadString(&GParser_state,
                     dic,
                     &(p_rigidBody_state_in->bodyName[0]),
                     "BodyProperties:BodyName");

  /* Close parameters */
  GParser_closeParams(&GParser_state, dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  RigidBody_createArchives(p_rigidBody_state_in);

  return GCONST_TRUE;
}
