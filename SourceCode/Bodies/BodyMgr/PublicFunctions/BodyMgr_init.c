/*
 *    @File:         BodyMgr_init.c
 *
 *    @Brief:        Function which will init BodyMgr for simulation.
 *
 *    @Date:         29/05/2024
 *
 */

#include <stdio.h>

/* Function Includes */
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"
#include "UavBody/PublicFunctions/UavBody_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
#include "BodyMgr/ConstantDefs/BodyMge_Const.h"
#include "BodyMgr/ConstantDefs/BodyMgr_BodyType.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int BodyMgr_init(
    BodyMgr_State *p_bodyMgr_state_out,
    const char    *p_bodyMgrFilename)
{
  /* Declare Local Variables */
  GParser_State GParser_state;
  dictionary   *p_dic;
  char          parameterBuffer[BODYMGR_PARAMETER_BUFFER];
  char bodyNameBuffer[BODYMGR_MAX_NUMBER_OF_BODIES][BODYMGR_NAME_BUFFER];
  int  bodyTypeList[BODYMGR_MAX_NUMBER_OF_BODIES];
  int  nRigidBodies;
  int  nCelestialBodies;
  int  nSatelliteBodies;
  int  nUavBodies;
  int  iRigidBodies;
  int  iCelestialBodies;
  int  iSatelliteBodies;
  int  iUavBodies;
  int  i;

  /* Clear Variables & Buffers */
  GZero(&GParser_state, GParser_State);
  GZero(p_bodyMgr_state_out, BodyMgr_State);
  GZero(&parameterBuffer[0], char[BODYMGR_PARAMETER_BUFFER]);
  GZero(
      &bodyNameBuffer[0][0],
      char[BODYMGR_MAX_NUMBER_OF_BODIES][BODYMGR_NAME_BUFFER]);
  GZero(&bodyTypeList[0], int[BODYMGR_MAX_NUMBER_OF_BODIES]);
  nRigidBodies     = 0;
  nCelestialBodies = 0;
  nSatelliteBodies = 0;
  nUavBodies       = 0;
  iRigidBodies     = 0;
  iCelestialBodies = 0;
  iSatelliteBodies = 0;
  iUavBodies       = 0;

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

  /* Assign memory for Rigid bodies pointers */
  p_bodyMgr_state_out->p_rigidBodyList = (RigidBody_State **)calloc(
      p_bodyMgr_state_out->nBodies,
      sizeof(RigidBody_State *));

  /* Assign memory for Satellite bodies pointers */
  p_bodyMgr_state_out->p_satelliteBodyList = (SatelliteBody_State **)calloc(
      p_bodyMgr_state_out->nSatelliteBodies,
      sizeof(SatelliteBody_State *));

  /* Assign memory for Celestial bodies pointers */
  p_bodyMgr_state_out->p_celestialBodyList = (CelestialBody_State **)calloc(
      p_bodyMgr_state_out->nCelestialBodies,
      sizeof(CelestialBody_State *));

  /* Assign memory for UAV bodies pointers */
  p_bodyMgr_state_out->p_uavBodyList = (UavBody_State **)calloc(
      p_bodyMgr_state_out->nUavBodies,
      sizeof(UavBody_State *));

  /* Load parameters for bodies */
  for (i = 0; i < p_bodyMgr_state_out->nBodies; i++)
  {

    /* Load parameterBuffer with name of ini file */
    sprintf(&parameterBuffer[0], "Parameters/%s.ini", bodyNameBuffer[i]);

    switch (bodyTypeList[i])
    {
    case RIGID_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies) =
          (RigidBody_State *)calloc(1, sizeof(RigidBody_State));

      /* Init RigidBody Body */
      RigidBody_init(
          *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies),
          &parameterBuffer[i]);

      /* Incriment iterators */
      iRigidBodies++;

      break;

    case CELESTIAL_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies) =
          (RigidBody_State *)calloc(1, sizeof(RigidBody_State));

      *(p_bodyMgr_state_out->p_celestialBodyList + iCelestialBodies) =
          (CelestialBody_State *)calloc(1, sizeof(CelestialBody_State));

      /* Init Celestial Body */
      CelestialBody_init(
          *(p_bodyMgr_state_out->p_celestialBodyList + iCelestialBodies),
          &parameterBuffer[0]);

      /* Assign Rigid Body to list */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies) =
          &((*(p_bodyMgr_state_out->p_celestialBodyList + iCelestialBodies))
                ->rigidBody_state);

      /* Incriment iterators */
      iRigidBodies++;
      iCelestialBodies++;
      break;

    case SATELLITE_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies) =
          (RigidBody_State *)calloc(1, sizeof(RigidBody_State));

      *(p_bodyMgr_state_out->p_satelliteBodyList + iSatelliteBodies) =
          (SatelliteBody_State *)calloc(1, sizeof(SatelliteBody_State));

      /* Init Celestial Body */
      SatelliteBody_init(
          *(p_bodyMgr_state_out->p_satelliteBodyList + iSatelliteBodies),
          &parameterBuffer[0]);

      /* Assign Rigid Body to list */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies) =
          &((*(p_bodyMgr_state_out->p_satelliteBodyList + iSatelliteBodies))
                ->rigidBody_state);

      /* Incriment iterators */
      iRigidBodies++;
      iSatelliteBodies++;
      break;

    case UAV_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies) =
          (RigidBody_State *)calloc(1, sizeof(RigidBody_State));

      *(p_bodyMgr_state_out->p_uavBodyList + iUavBodies) =
          (UavBody_State *)calloc(1, sizeof(UavBody_State));

      /* Init Celestial Body */
      UavBody_init(
          *(p_bodyMgr_state_out->p_uavBodyList + iUavBodies),
          &parameterBuffer[0]);

      /* Assign Rigid Body to list */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBodies) =
          &((*(p_bodyMgr_state_out->p_uavBodyList + iUavBodies))
                ->rigidBody_state);

      /* Incriment iterators */
      iRigidBodies++;
      iUavBodies++;
      break;

    default:
      GError("Unknown Body Type %d", bodyTypeList[i]);
      break;
    }

    /* Clear parameterBuffer */
    GZero(&parameterBuffer[0], char[BODYMGR_PARAMETER_BUFFER]);
  }

  /* Check that the number of bodies matches */
  if (p_bodyMgr_state_out->nBodies !=
      p_bodyMgr_state_out->nRigidBodies +
          p_bodyMgr_state_out->nSatelliteBodies +
          p_bodyMgr_state_out->nUavBodies +
          p_bodyMgr_state_out->nCelestialBodies)
  {
    GError(
        "Bodies do not match, nBodies=%d, nRigidBodies=%d, "
        "nSatelliteBodies=%d, nUavBodies=%d, nCelestialBodies=%d",
        p_bodyMgr_state_out->nBodies,
        p_bodyMgr_state_out->nRigidBodies,
        p_bodyMgr_state_out->nSatelliteBodies,
        p_bodyMgr_state_out->nUavBodies,
        p_bodyMgr_state_out->nCelestialBodies);
  }

  return GCONST_TRUE;
}
