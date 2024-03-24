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

/* Function Includes */
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GIntegral/GIntegral.h"
#include "GMath/GMath.h"
#include "GUtilities/GUtilities.h"

int main(void)
{
  /* Declaring local variables */
  SatelliteBody_State satelliteBody;
  CelestialBody_State celestialBody;

  /*-------------------------------------------------------------------------*
   *                           INITIALIZE BODIES                             *
   *-------------------------------------------------------------------------*/

  GUtilities_init("Parameters/SimulationParameters.ini");

  SatelliteBody_init(&satelliteBody, "Parameters/Truths.ini");
  CelestialBody_init(&celestialBody, "Parameters/Earth.ini");

  /*-------------------------------------------------------------------------*
   *                         RUN CYCLIC EXECUTION                            *
   *-------------------------------------------------------------------------*/
  do
  {
    satelliteBody.rigidBody_state.resultantForce_N_Fixed[0] = 1000;
    satelliteBody.rigidBody_state.resultantForce_N_Fixed[1] = 5000;
    satelliteBody.rigidBody_state.resultantForce_N_Fixed[2] = 200;

    satelliteBody.rigidBody_state.resultantMoment_Nm_Bod[0] = 10;
    satelliteBody.rigidBody_state.resultantMoment_Nm_Bod[1] = 1;
    satelliteBody.rigidBody_state.resultantMoment_Nm_Bod[2] = 14;

    SatelliteBody_step(&satelliteBody);
    // CelestialBody_step(&celestialBody);

    /* Step time forward a step */
    Utilities.simTime_s += Utilities.simTimeStep_s;
  }
  while (Utilities.simTime_s <= Utilities.simTimeDuration_s);

  /*-------------------------------------------------------------------------*
   *                             CLOSE ARCHIVES                              *
   *-------------------------------------------------------------------------*/
  SatelliteBody_terminate(&satelliteBody);
  CelestialBody_terminate(&celestialBody);

  return GCONST_EXIT_SUCCESS;
}
