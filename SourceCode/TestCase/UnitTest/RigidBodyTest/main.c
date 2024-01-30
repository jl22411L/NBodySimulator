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
   *                         INITIALIZE STRUCTURES                           *
   *-------------------------------------------------------------------------*/

  GUtilities_init("parameters/SimulationParameters.ini");

  RigidBody_init(&RigidBody);

  /*-------------------------------------------------------------------------*
   *                         RUN CYCLIC EXECUTION                            *
   *-------------------------------------------------------------------------*/
  do
  {
    /* Integrate body - Translational */
    GIntegral_3x1Double(
        &RigidBody.position_m,
        &RigidBody.fixedFrameVeclocity_ms,
        Utilities.simTimeStep_s);

    GIntegral_3x1Double(
        &RigidBody.fixedFrameVeclocity_ms,
        &RigidBody.fixedFrameAcceleration_ms2,
        Utilities.simTimeStep_s);

    RigidBody.fixedFrameAcceleration_ms2[0] = 0;
    RigidBody.fixedFrameAcceleration_ms2[1] = 0;
    RigidBody.fixedFrameAcceleration_ms2[2] = 0;

    /* Integrate body - Angular */
    GMath_quaternionRateCalc(
        &RigidBody.quaternionRateFixed2Body,
        &RigidBody.quaternionFixed2Body,
        &RigidBody.angularVelocity_rads);

    GIntegral_4x1Double(
        &RigidBody.quaternionFixed2Body,
        &RigidBody.quaternionRateFixed2Body,
        Utilities.simTimeStep_s);

    GIntegral_3x1Double(
        &RigidBody.angularVelocity_rads,
        &RigidBody.angularAcceleration_rads2,
        Utilities.simTimeStep_s);

    RigidBody.angularAcceleration_rads2[0] = 0;
    RigidBody.angularAcceleration_rads2[0] = 0;
    RigidBody.angularAcceleration_rads2[0] = 0;

    /* Step time forward a step */
    Utilities.simTime_s += Utilities.simTimeStep_s;
  }
  while (Utilities.simTime_s <= Utilities.simTimeDuration_s);

  return GCONST_EXIT_SUCCESS;
}