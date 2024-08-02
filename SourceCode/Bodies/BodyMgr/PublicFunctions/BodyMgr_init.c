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
#include "BodyMgr/ConstantDefs/BodyMgr_BodyTypeEnum.h"
#include "BodyMgr/ConstantDefs/BodyMgr_Const.h"

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
  dictionary   *p_dic;
  GParser_State GParser_state;
  char          parameterBuffer[BODYMGR_MAX_BUFFER_LENGTH];
  char          bodyNameBuffer[BODYMGR_MAX_NUMBER_OF_BODIES]
                     [BODYMGR_BODY_NAME_MAX_BUFFER];
  int bodyTypeList[BODYMGR_MAX_NUMBER_OF_BODIES];
  int nRigidBodies;
  int nCelestialBodies;
  int nSatelliteBodies;
  int nUavBodies;
  int iRigidBodyPointers;
  int iRigidBody;
  int iCelestialBodies;
  int iSatelliteBodies;
  int iUavBodies;
  int i;

  /* Clear Variables & Buffers */
  GZero(p_bodyMgr_state_out, BodyMgr_State);
  GZero(&GParser_state, GParser_State);
  GZero(&parameterBuffer[0], char[BODYMGR_MAX_BUFFER_LENGTH]);
  GZero(
      &bodyNameBuffer[0][0],
      char[BODYMGR_MAX_NUMBER_OF_BODIES][BODYMGR_BODY_NAME_MAX_BUFFER]);
  GZero(&bodyTypeList[0], int[BODYMGR_MAX_NUMBER_OF_BODIES]);
  iRigidBodyPointers = 0;
  iRigidBody         = 0;
  iCelestialBodies   = 0;
  iSatelliteBodies   = 0;
  iUavBodies         = 0;

  /* Load parameters */
  p_dic = GParser_loadParams(&GParser_state, p_bodyMgrFilename);

  /* Find number of bodies */
  p_bodyMgr_state_out->nBodies = GParser_state.maxNumberSection;

  /* ------------------------------------------------------------------------ *
   *                      Gain Information About Bodies                       *
   * ------------------------------------------------------------------------ */

  /* Iterate through the different loadies and load parameters into bodies */
  for (i = 0; i < p_bodyMgr_state_out->nBodies; i++)
  {
    /* Load Parameter Buffer with name of parameter */
    sprintf(&parameterBuffer[0], "Body%d:bodyType", i);

    /* Load the type of body */
    GParser_loadInt(
        &GParser_state,
        p_dic,
        &bodyTypeList[i],
        &parameterBuffer[0]);

    /* See what type of body is being loaded */
    switch (bodyTypeList[i])
    {
    case (RIGID_BODY):
      p_bodyMgr_state_out->nRigidBodies++;
      break;
    case (CELESTIAL_BODY):
      p_bodyMgr_state_out->nCelestialBodies++;
      break;
    case (SATELLITE_BODY):
      p_bodyMgr_state_out->nSatelliteBodies++;
      break;
    case (UAV_BODY):
      p_bodyMgr_state_out->nUavBodies++;
      break;
    default:
      GError("Unknown Body Type %d", bodyTypeList[i]);
      break;
    }

    /* Clear Buffer */
    GZero(&parameterBuffer[0], char[BODYMGR_MAX_BUFFER_LENGTH]);

    /* Load parameter buffer with name of string */
    sprintf(&parameterBuffer[0], "Body%d:bodyName", i);

    /* Load the name of the body */
    GParser_loadString(
        &GParser_state,
        p_dic,
        &bodyNameBuffer[i][0],
        &parameterBuffer[0]);
  }

  /* ------------------------------------------------------------------------ *
   *                        Memory Allocation of Bodies                       *
   * ------------------------------------------------------------------------ */

  /* Assign memory for Rigid bodies pointers */
  p_bodyMgr_state_out->p_rigidBodyPointerList = (RigidBody_State **)calloc(
      p_bodyMgr_state_out->nBodies,
      sizeof(RigidBody_State *));

  /* Assign memory for Pure Rigid Bodies */
  p_bodyMgr_state_out->p_rigidBodyList = (RigidBody_State **)calloc(
      p_bodyMgr_state_out->nRigidBodies,
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

  /* ------------------------------------------------------------------------ *
   *                           Load Specific Bodies                           *
   * ------------------------------------------------------------------------ */

  /* Load parameters for bodies */
  for (i = 0; i < p_bodyMgr_state_out->nBodies; i++)
  {

    /* Load parameterBuffer with name of ini file */
    sprintf(&parameterBuffer[0], "Parameters/%s.ini", bodyNameBuffer[i]);

    switch (bodyTypeList[i])
    {
    case RIGID_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBody) =
          (RigidBody_State *)calloc(1, sizeof(RigidBody_State));

      /* Init RigidBody Body */
      RigidBody_init(
          *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBody),
          &parameterBuffer[0]);

      /* Assign Rigid Body to list */
      *(p_bodyMgr_state_out->p_rigidBodyPointerList + iRigidBodyPointers) =
          *(p_bodyMgr_state_out->p_rigidBodyList + iRigidBody);

      /* Incriment iterators */
      iRigidBodyPointers++;
      iRigidBody++;
      break;

    case CELESTIAL_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_celestialBodyList + iCelestialBodies) =
          (CelestialBody_State *)calloc(1, sizeof(CelestialBody_State));

      /* Init Celestial Body */
      CelestialBody_init(
          *(p_bodyMgr_state_out->p_celestialBodyList + iCelestialBodies),
          &parameterBuffer[0]);

      /* Assign Rigid Body to list */
      *(p_bodyMgr_state_out->p_rigidBodyPointerList + iRigidBodyPointers) =
          &((*(p_bodyMgr_state_out->p_celestialBodyList + iCelestialBodies))
                ->rigidBody_state);

      /* Incriment iterators */
      iRigidBodyPointers++;
      iCelestialBodies++;
      break;

    case SATELLITE_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_satelliteBodyList + iSatelliteBodies) =
          (SatelliteBody_State *)calloc(1, sizeof(SatelliteBody_State));

      /* Init Celestial Body */
      SatelliteBody_init(
          *(p_bodyMgr_state_out->p_satelliteBodyList + iSatelliteBodies),
          &parameterBuffer[0]);

      /* Assign Rigid Body to list */
      *(p_bodyMgr_state_out->p_rigidBodyPointerList + iRigidBodyPointers) =
          &((*(p_bodyMgr_state_out->p_satelliteBodyList + iSatelliteBodies))
                ->rigidBody_state);

      /* Incriment iterators */
      iRigidBodyPointers++;
      iSatelliteBodies++;
      break;

    case UAV_BODY:

      /* Assign memory for body */
      *(p_bodyMgr_state_out->p_uavBodyList + iUavBodies) =
          (UavBody_State *)calloc(1, sizeof(UavBody_State));

      /* Init Celestial Body */
      UavBody_init(
          *(p_bodyMgr_state_out->p_uavBodyList + iUavBodies),
          &parameterBuffer[0]);

      /* Assign Rigid Body to list */
      *(p_bodyMgr_state_out->p_rigidBodyPointerList + iRigidBodyPointers) =
          &((*(p_bodyMgr_state_out->p_uavBodyList + iUavBodies))
                ->rigidBody_state);

      /* Incriment iterators */
      iRigidBodyPointers++;
      iUavBodies++;
      break;

    default:
      GError("Unknown Body Type %d", bodyTypeList[i]);
      break;
    }

    /* Clear parameterBuffer */
    GZero(&parameterBuffer[0], char[BODYMGR_MAX_BUFFER_LENGTH]);
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

  /* Terminate GParser */
  GParser_closeParams(&GParser_state, p_dic);

  return GCONST_TRUE;
}
