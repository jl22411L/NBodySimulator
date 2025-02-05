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
#include "BodyMgr/PublicFunctions/BodyMgr_PublicFunctions.h"
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "Gravity/PublicFunctions/Gravity_PublicFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"
#include "UavBody/PublicFunctions/UavBody_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
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
  Gravity_Params gravity_params;
  BodyMgr_State  bodyMgr_state;
  int            i;

  /* Clear local variables */
  GZero(&bodyMgr_state, BodyMgr_State);
  GZero(&gravity_params, Gravity_Params);

  /*-------------------------------------------------------------------------*
   *                          INITIALIZATION SECTION                         *
   *-------------------------------------------------------------------------*/

  /* Initialize GUtilitites */
  GUtilities_init("Parameters/SimulationParameters.ini");

  /* Initialize Gravity Module */
  Gravity_init(&gravity_params, "Parameters/GravityParameters.ini");

  /* Initialize BodyMgr */
  BodyMgr_init(&bodyMgr_state, "Parameters/BodyMgrParameters.ini");

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
    Gravity_findGravity(&gravity_params,
                        bodyMgr_state.p_rigidBodyPointerList,
                        bodyMgr_state.nBodies);

    /* ---------------------------------------------------------------------- *
     *                            STEP SIMULATION                             *
     * ---------------------------------------------------------------------- */

    /* ------------------------------- Bodies ------------------------------- */

    /* ------------------------------ Time --------------------------------- */

    /* Step forawrd in time */
    Utilities.simTime_s += Utilities.simTimeStep_s;

    /* ---------------------------------------------------------------------- *
     *                          CHECK END CONDITION                           *
     * ---------------------------------------------------------------------- */

    /* Check if the simulation duration has been reached */
    if (Utilities.simTime_s >= Utilities.simTimeEnd_s)
    {
      /* Set sim status to False to indicate that sim has completed */
      Utilities.runSimStatus = GCONST_FALSE;
    }
  }
  while (Utilities.runSimStatus);

  /*-------------------------------------------------------------------------*
   *                        TERMINATION OF SIMULATION                        *
   *-------------------------------------------------------------------------*/

  /* ------------------------------- Bodies -------------------------------- */

  /* Terminate BodyMgr */
  BodyMgr_terminate(&bodyMgr_state);

  return GCONST_EXIT_SUCCESS;
}
