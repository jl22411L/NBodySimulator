/*
 *    @File:         main.c
 *
 *    @ Brief:       Main c file for system test, which is meant to test new
 *                   systems of simulator.
 *
 *    @ Date:        02/05/2024
 *
 */

#include <stdio.h>

/* Function Includes */
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "Gravity/PublicFunctions/Gravity_PublicFunctions.h"
#include "UavBody/PublicFunctions/UavBody_PublicFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "Gravity/DataStructs/Gravity_ParamsStruct.h"
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GUtilities/GUtilities.h"
#include "GZero/GZero.h"

int main(void)
{
  /* Declaring local variables */
  UavBody_State       uavBody_state;
  Gravity_Params      gravity_params;
  CelestialBody_State celestialBody_state;
  RigidBody_State    *rigidBodyArr_state[2];

  /* Clear local variables */
  GZero(&uavBody_state, UavBody_State);
  GZero(&celestialBody_state, CelestialBody_State);

  /*-------------------------------------------------------------------------*
   *                          INITIALIZATION SECTION *
   *-------------------------------------------------------------------------*/

  /* Initialize GUtilitites */
  GUtilities_init("Parameters/SimulationParameters.ini");

  /* Initialize Gravity Module */
  Gravity_init(&gravity_params, "Parameters/GravityParameters.ini");

  /* Initialize Bodies */
  UavBody_init(&uavBody_state, "Parameters/CR-1.ini");
  CelestialBody_init(&celestialBody_state, "Parameters/Earth.ini");

  /* Create an array of pointers which point to the rigid bodies */
  rigidBodyArr_state[0] = &(uavBody_state.rigidBody_state);
  rigidBodyArr_state[1] = &(celestialBody_state.rigidBody_state);

  /*-------------------------------------------------------------------------*
   *                         ENTER CYCLICAL EXECUTION                        *
   *-------------------------------------------------------------------------*/

  /* Display text to indicate that cyclical execution has been reached */
  GLog("# ------------------------ ENTERING CYLICAL EXECUTION "
       "------------------------ #");

  /* Enter into cyclic execution */
  do
  {
    /* ---------------------------------------------------------------------- *
     *                   APPLY EXTERNAL LOADS TO RIGID BODY                   *
     * ---------------------------------------------------------------------- */

    /* Apply gravity to UAV body */
    Gravity_findGravity(
        &gravity_params,
        &rigidBodyArr_state[0],
        Utilities.numberOfBodies);

    /* ---------------------------------------------------------------------- *
     *                            STEP SIMULATION                             *
     * ---------------------------------------------------------------------- */

    /* Step UAV Body */
    UavBody_step(&uavBody_state);

    /* Step Celestial Body */
    CelestialBody_step(&celestialBody_state);

    /* Step forawrd in time */
    Utilities.simTime_s += Utilities.simTimeStep_s;

    /* Check if the simulation duration has been reached */
    if (Utilities.simTime_s >= Utilities.simTimeDuration_s)
    {
      /* Set sim status to False to indicate that sim has completed */
      Utilities.runSimStatus = GCONST_FALSE;
    }
  }
  while (Utilities.runSimStatus);

  /*-------------------------------------------------------------------------*
   *                         TERMINATION OF SIMULATION                       *
   *-------------------------------------------------------------------------*/

  /* Terminate bodies */
  UavBody_terminate(&uavBody_state);
  CelestialBody_terminate(&celestialBody_state);

  return GCONST_EXIT_SUCCESS;
}
