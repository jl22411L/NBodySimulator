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

#include "BodyTypes/RigidBody/RigidBody.h"

/* Function Includes */
/* None */

/* Structure Include */
/* None */

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
  RigidBody_State RigidBody;

  /*-------------------------------------------------------------------------*
   *                            CREATE ARCHIVES                              *
   *-------------------------------------------------------------------------*/
  GArchive_init(&RigidBody.rigidBodyArchive, "ArchiveData/RigidBody");

  /*-------------------------------------------------------------------------*
   *                         INITIALIZE STRUCTURES                           *
   *-------------------------------------------------------------------------*/

  GUtilities_init("parameters/SimulationParameters.ini");

  RigidBody_init(&RigidBody, "parameters/RigidBody_params.ini");

  /*-------------------------------------------------------------------------*
   *                         RUN CYCLIC EXECUTION                            *
   *-------------------------------------------------------------------------*/
  do
  {
    RigidBody_step(&RigidBody);

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
