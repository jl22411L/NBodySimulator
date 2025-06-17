/*
 *    @File:         CelestialBody_init.c
 *
 *    @ Brief:       Function which loads the parameters into the Celestial Body
 *
 *    @ Date:        17/03/2024
 *
 */

/* Function Includes */
#include "CelestialBody/PrivateFunctions/CelestialBody_PrivateFunctions.h"
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
#include "CelestialBody/ConstantDefs/CelestialBody_Const.h"

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int CelestialBody_init(CelestialBody_State *p_celestialBody_state_in,
                       const char          *p_paramFilename_in)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;

  /* Zeroing Local variables */
  GZero(&GParser_state, GParser_State);
  GZero(&p_dic, dictionary *);
  GZero(p_celestialBody_state_in, CelestialBody_State);

  /* ------------------------------------------------------------------------ *
   *                             LOAD PARAMETERS                              *
   * ------------------------------------------------------------------------ */

  /* Load parameters of the body */
  p_dic = GParser_loadParams(&GParser_state, p_paramFilename_in);

  /* Load equitorial Radius of celestial body */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_celestialBody_state_in->equitorialRadius_m),
                     "GeometryProperties:equtorialRadius_m");

  /* Load quaternion rotating from fix frame to body inertical centric frame */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_celestialBody_state_in->quaternion_FixToInertCen[0]),
      "AngularProperties:quaternion_FixToInertCen",
      4,
      1);

  /* Load equitorial Radius of celestial body */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_celestialBody_state_in->sideRealTime_s),
                     "BodyProperties:sideRealTime_s");

  /* Load Rigid Body parameters */
  RigidBody_init(&p_celestialBody_state_in->rigidBody_state,
                 p_paramFilename_in);

  /* Close Params */
  GParser_closeParams(&GParser_state, p_dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  CelestialBody_createArchives(
      p_celestialBody_state_in,
      p_celestialBody_state_in->rigidBody_state.bodyName);

  return GCONST_TRUE;
}
