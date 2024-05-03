/*
 *    @File:         SatelliteBody_init.c
 *
 *    @ Brief:       Function which loads the parameters into the Satellite Body
 *
 *    @ Date:        24/01/2024
 *
 */

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"
#include "SatelliteBody/PrivateFunctions/SatelliteBody_PrivateFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int SatelliteBody_init(
    SatelliteBody_State *p_satelliteBody_state_in,
    const char          *p_paramFilename_in)
{
  /* Declare local variables */
  dictionary   *dic;
  GParser_State GParser_state;
  char          archiveNameBuffer[GCONST_BUFFER_1024];

  /* Zeroing Local variables */
  GZero(&GParser_state, GParser_State);
  GZero(&dic, dictionary *);
  GZero(&archiveNameBuffer[0], char[GCONST_BUFFER_1024]);
  GZero(p_satelliteBody_state_in, SatelliteBody_State);

  /* ------------------------------------------------------------------------ *
   *                             LOAD PARAMETERS                              *
   * ------------------------------------------------------------------------ */

  /* Load parameters of the body */
  dic = GParser_loadParams(&GParser_state, p_paramFilename_in);

  /* CURRENTLY NO PARAMETERS TO LOAD */
  // TODO Add load parameters into sat struct

  /* Load Rigid Body parameters */
  RigidBody_init(
      &p_satelliteBody_state_in->rigidBody_state,
      p_paramFilename_in);

  /* Close Params */
  GParser_closeParams(&GParser_state, dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create Archive Name */
  sprintf(
      archiveNameBuffer,
      "Bodies/%s/OutputData/SatelliteBody",
      p_satelliteBody_state_in->rigidBody_state.bodyName);

  /* Create archives */
  SatelliteBody_createArchives(
      p_satelliteBody_state_in,
      p_satelliteBody_state_in->rigidBody_state.bodyName);

  return GCONST_TRUE;
}
