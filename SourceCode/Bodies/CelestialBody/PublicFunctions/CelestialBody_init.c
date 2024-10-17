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

int CelestialBody_init(
    CelestialBody_State *p_celestialBody_state_in,
    const char          *p_paramFilename_in)
{
  /* Declare local variables */
  dictionary   *dic;
  GParser_State GParser_state;

  /* Zeroing Local variables */
  GZero(&GParser_state, GParser_State);
  GZero(&dic, dictionary *);
  GZero(p_celestialBody_state_in, CelestialBody_State);

  /* ------------------------------------------------------------------------ *
   *                             LOAD PARAMETERS                              *
   * ------------------------------------------------------------------------ */

  /* Load parameters of the body */
  dic = GParser_loadParams(&GParser_state, p_paramFilename_in);

  /* CURRENTLY NO PARAMETERS TO LOAD */
  // TODO Add load parameters into celestial body struct

  /* Load Rigid Body parameters */
  RigidBody_init(
      &p_celestialBody_state_in->rigidBody_state,
      p_paramFilename_in);

  /* Close Params */
  GParser_closeParams(&GParser_state, dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  CelestialBody_createArchives(
      p_celestialBody_state_in,
      p_celestialBody_state_in->rigidBody_state.bodyName);

  return GCONST_TRUE;
}
