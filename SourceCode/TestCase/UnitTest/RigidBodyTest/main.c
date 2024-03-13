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
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GIntegral/GIntegral.h"
#include "GMath/GMath.h"
#include "GUtilities/GUtilities.h"

int main()
{
  /* Declaring local variables */
  SatelliteBody_State satelliteBody;

  /*-------------------------------------------------------------------------*
   *                           INITIALIZE BODIES                             *
   *-------------------------------------------------------------------------*/

  GUtilities_init("Parameters/SimulationParameters.ini");

  SatelliteBody_init(&satelliteBody, "Parameters/Truths.ini", "Truths");

  /*-------------------------------------------------------------------------*
   *                         RUN CYCLIC EXECUTION                            *
   *-------------------------------------------------------------------------*/
  do
  {
    SatelliteBody_step(&satelliteBody);

    /* Step time forward a step */
    Utilities.simTime_s += Utilities.simTimeStep_s;
  }
  while (Utilities.simTime_s <= Utilities.simTimeDuration_s);

  /*-------------------------------------------------------------------------*
   *                             CLOSE ARCHIVES                              *
   *-------------------------------------------------------------------------*/
  SatelliteBody_terminate(&satelliteBody);

  return GCONST_EXIT_SUCCESS;
}
