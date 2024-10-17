/*
 *    @File:         UavBody_init.c
 *
 *    @ Brief:       Function which loads the parameters into the uav Body
 *
 *    @ Date:        02/05/2024
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"
#include "UavBody/PrivateFunctions/UavBody_PrivateFunctions.h"
#include "UavBody/PublicFunctions/UavBody_PublicFunctions.h"

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
#include "UavBody/ConstantDefs/UavBody_Const.h"

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int UavBody_init(
    UavBody_State *p_uavBody_state_in,
    const char    *p_paramFilename_in)
{
  /* Declare local variables */
  dictionary   *dic;
  GParser_State GParser_state;

  /* Clearing variables */
  GZero(&GParser_state, GParser_State);
  GZero(&dic, dictionary *);
  GZero(p_uavBody_state_in, UavBody_State);

  /* ------------------------------------------------------------------------ *
   *                             LOAD PARAMETERS                              *
   * ------------------------------------------------------------------------ */

  /* Load parameters of the body */
  dic = GParser_loadParams(&GParser_state, p_paramFilename_in);

  /* CURRENTLY NO PARAMETERS TO LOAD */
  // TODO Add load parameters into UAV struct

  /* Load Rigid Body parameters */
  RigidBody_init(&p_uavBody_state_in->rigidBody_state, p_paramFilename_in);

  /* Close Params */
  GParser_closeParams(&GParser_state, dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  UavBody_createArchives(
      p_uavBody_state_in,
      p_uavBody_state_in->rigidBody_state.bodyName);

  return GCONST_TRUE;
}
