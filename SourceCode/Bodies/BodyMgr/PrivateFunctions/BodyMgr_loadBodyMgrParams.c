/*
 *    @File:         BodyMgr_loadBodyMgrParams.c
 *
 *    @Brief:        Loads data relavant for the bodyMgr to load the data of the
 *                   different bodies.
 *
 *    @Date:         01/06/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"

/* Data include */
#include "BodyMgr/ConstantDefs/BodyMge_Const.h"
#include "BodyMgr/ConstantDefs/BodyMgr_BodyType.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int BodyMgr_loadBodyMgrParams(
    BodyMgr_State *p_bodyMgr_state_out,
    const char    *p_bodyMgrFilename)
{
  /* Declare Local Variables */
  GParser_State GParser_state;
  dictionary   *p_dic;
  char          parameterBuffer[BODYMGR_PARAMETER_BUFFER];
  int           i;

  /* Clear Variables and Buffers */
  GZero(&parameterBuffer[0], char[BODYMGR_PARAMETER_BUFFER]);
  GZero(&GParser_state, GParser_State);

  /* Load parameters into GParser_state struct */
  p_dic = GParser_loadParams(&GParser_state, p_bodyMgrFilename);

  /* Find number of bodies. This should be equal to the number of sections */
  p_bodyMgr_state_out->nBodies = GParser_state.maxNumberSection;

  /* Load each body individually */
  for (i = 0; i < p_bodyMgr_state_out->nBodies; i++)
  {
    /* Load buffer with name of body type */
    sprintf(parameterBuffer, "Body%d:bodyType", i);

    /* Load body type */
    GParser_loadInt(&GParser_state, p_dic, &bodyTypeList[i], parameterBuffer);

    /* Clear buffer */
    GZero(&parameterBuffer[0], char[BODYMGR_PARAMETER_BUFFER]);

    /* Load buffer with name of body type */
    sprintf(parameterBuffer, "Body%d:bodyName", i);

    /* Load body name */
    GParser_loadString(
        &GParser_state,
        p_dic,
        &bodyNameBuffer[i][0],
        parameterBuffer);

    GZero(&parameterBuffer[0], char[BODYMGR_PARAMETER_BUFFER]);

    switch (bodyTypeList[i])
    {
    case RIGID_BODY:
      p_bodyMgr_state_out->nRigidBodies++;
      break;

    case CELESTIAL_BODY:
      p_bodyMgr_state_out->nCelestialBodies++;
      break;

    case SATELLITE_BODY:
      p_bodyMgr_state_out->nSatelliteBodies++;
      break;

    case UAV_BODY:
      p_bodyMgr_state_out->nUavBodies++;
      break;

    default:
      GError("Unknown Body Type %d", bodyTypeList[i]);
      break;
    }
  }

  return GCONST_TRUE;
}
