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
#include "Gravity/PublicFunctions/Gravity_PublicFunctions.h"
#include "UavBody/PublicFunctions/UavBody_PublicFunctions.h"

/* Structure Include */
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
  UavBody_State  uavBody_state;
  Gravity_Params gravity_params;

  /* Clear local variables */
  GZero(&uavBody_state, UavBody_State);

  /*-------------------------------------------------------------------------*
   *                          INITIALIZATION SECTION                         *
   *-------------------------------------------------------------------------*/

  /* Initialize GUtilitites */
  GUtilities_init("Parameters/SimulationParameters.ini");

  /* Initialize Gravity Module */
  Gravity_init(&gravity_params, "Parameters/GravityParameters.ini");

  /* Initialize Bodies */
  UavBody_init(&uavBody_state, "Parameters/CR-1.ini");

  /* Create an array of the rigid bpdies */

  /*-------------------------------------------------------------------------*
   *                         ENTER CYCLICAL EXECUTION                        *
   *-------------------------------------------------------------------------*/

  /* Display text to indicate that cyclical execution has been reached */
  GLog("# ------------------------ ENTERING CYLICAL EXECUTION "
       "------------------------ #");

  /* Enter into cyclic execution */
  do
  {
    int i = 1;

    /* Apply gravity to UAV body */
    Gravity_findGravity(&gravity_params, &uavBody_state.rigidBody_state, i);

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

  return GCONST_EXIT_SUCCESS;
}
