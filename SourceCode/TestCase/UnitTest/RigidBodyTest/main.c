/*
 *    @File:         main.c
 *
 *    @ Brief:       Rigid Body Unit Test
 *
 *    @ Description: This script is a unit test for the Rigid Body structure
 *
 *    @ Date:        24/01/2024
 *
 */

#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"
#include "RigidBody/RigidBody.h"

/* Function Includes */
#include "GIntegral/GIntegral.h"

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GUtilities/GUtilities.h"

int main()
{
  /* Declaring local variables */
  RigidBody_State RigidBody;

  /*-------------------------------------------------------------------------*
   *                            CREATE ARCHIVES                              *
   *-------------------------------------------------------------------------*/
  GArchive_init(&RigidBody.rigidBodyArchive, "ArchiveData/RigidBody");

  /*-------------------------------------------------------------------------*
   *                         INITIALIZE STRUCTURES                           *
   *-------------------------------------------------------------------------*/

  GUtilities_init("parameters/SimulationParameters.ini");

  RigidBody_init(&RigidBody);

  /*-------------------------------------------------------------------------*
   *                         RUN CYCLIC EXECUTION                            *
   *-------------------------------------------------------------------------*/
  do
  {
    /*------------------------------------------------------------------------*
     *                                ARCHIVE                                 *
     *------------------------------------------------------------------------*/
    RigidBody_archiveData(&RigidBody);

    /* Integrate body - Translational */
    GIntegral_3x1Double(
        &RigidBody.position_m[0],
        &RigidBody.fixedFrameVeclocity_ms[0],
        Utilities.simTimeStep_s);

    GIntegral_3x1Double(
        &RigidBody.fixedFrameVeclocity_ms[0],
        &RigidBody.fixedFrameAcceleration_ms2[0],
        Utilities.simTimeStep_s);

    RigidBody.fixedFrameAcceleration_ms2[0] = 0;
    RigidBody.fixedFrameAcceleration_ms2[1] = 0;
    RigidBody.fixedFrameAcceleration_ms2[2] = 0;

    /* Integrate body - Angular */
    GMath_quaternionRateCalc(
        &RigidBody.quaternionRateFixed2Body[0],
        &RigidBody.quaternionFixed2Body[0],
        &RigidBody.angularVelocity_rads[0]);

    GIntegral_4x1Double(
        &RigidBody.quaternionFixed2Body[0],
        &RigidBody.quaternionRateFixed2Body[0],
        Utilities.simTimeStep_s);

    GIntegral_3x1Double(
        &RigidBody.angularVelocity_rads[0],
        &RigidBody.angularAcceleration_rads2[0],
        Utilities.simTimeStep_s);

    RigidBody.angularAcceleration_rads2[0] = 0;
    RigidBody.angularAcceleration_rads2[0] = 0;
    RigidBody.angularAcceleration_rads2[0] = 0;

    /* Step time forward a step */
    Utilities.simTime_s += Utilities.simTimeStep_s;
  }
  while (Utilities.simTime_s <= Utilities.simTimeDuration_s);

  /*-------------------------------------------------------------------------*
   *                             CLOSE ARCHIVES                              *
   *-------------------------------------------------------------------------*/
  GArchive_close(&RigidBody.rigidBodyArchive);

  return GCONST_EXIT_SUCCESS;
}