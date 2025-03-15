/*!
 *    @File:         main.c
 *
 *    @ Brief:       Main c file for system test, which is meant to test new
 *                   systems of simulator.
 *
 *    @ Date:        02/05/2024
 *
 */

#include <signal.h>
#include <stdio.h>

/* Function Includes */
#include "BodyMgr/PublicFunctions/BodyMgr_PublicFunctions.h"
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "Gravity/PublicFunctions/Gravity_PublicFunctions.h"
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"
#include "JamSail/PublicFunctions/JamSail_PublicFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"
#include "Sensors/Magnetometer/PublicFunctions/Magnetometer_PublicFunctions.h"
#include "Sensors/SunSensor/PublicFunctions/SunSensor_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "Gravity/DataStructs/Gravity_ParamsStruct.h"
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h" // TODO: Complete todo at bottom of function and remove
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GUtilities/GUtilities.h"
#include "GZero/GZero.h"

int main(void)
{
  /* Declaring local variables */
  Gravity_Params gravity_params;
  BodyMgr_State  bodyMgr_state;
  JamSail_State  jamSail_state;
  JamSail_Params jamSail_params;
  Igrf_Params    igrf_params;
  int            i;

  /* Clear local variables */
  GZero(&jamSail_state, JamSail_State);
  GZero(&jamSail_params, JamSail_Params);
  GZero(&bodyMgr_state, BodyMgr_State);
  GZero(&gravity_params, Gravity_Params);
  GZero(&igrf_params, Igrf_Params);

  /* ------------------------------------------------------------------------ *
   * Initialze Simulation
   * ------------------------------------------------------------------------ */

  /* Initialize GUtilitites */
  GUtilities_init("Parameters/SimulationParameters.ini");

  /* Initialize Gravity Module */
  Gravity_init(&gravity_params, "Parameters/GravityParameters.ini");

  /* Initialize BodyMgr */
  BodyMgr_init(&bodyMgr_state, "Parameters/BodyMgrParameters.ini");

  /* Initialize the IGRF model (This is simulating true earth magnetic field) */
  Igrf_init(&igrf_params, "Parameters/IgrfParameters.ini", 13, 13);

  /* ------------------------------------------------------------------------ *
   * Initialize JamSail
   * ------------------------------------------------------------------------ */

  /* Initialize JamSail */
  JamSail_init(&jamSail_state, &jamSail_params, &bodyMgr_state);

  /* ----------------------------------------------------------------------- *
   * ENTER CYCLICAL EXECUTION
   * ----------------------------------------------------------------------- */

  /* Display text to indicate that cyclical execution has been reached */
  GLog("# -------------------------- ENTERING CYLICAL EXECUTION "
       "-------------------------- #");

  /* Enter into cyclic execution */
  do
  {
    /* ---------------------------------------------------------------------- *
     * Pre-Step Calculations
     * ---------------------------------------------------------------------- */

    /* Apply gravity to UAV body */
    Gravity_findGravity(&gravity_params,
                        bodyMgr_state.p_rigidBodyPointerList,
                        bodyMgr_state.nBodies);

    /* ---------------------------------------------------------------------- *
     * Step Phase
     * ---------------------------------------------------------------------- */

    /* Step JamSail */
    JamSail_step(&jamSail_state,
                 &jamSail_params,
                 &bodyMgr_state,
                 &igrf_params,
                 Utilities.simTime_s,
                 Utilities.simTimeStep_s);

    /* Step the bodies */
    BodyMgr_step(&bodyMgr_state);

    /* Step forawrd in time */
    Utilities.simTime_s += Utilities.simTimeStep_s;

    /* ---------------------------------------------------------------------- *
     * Check End Conditions
     * ---------------------------------------------------------------------- */

    /* Check if the simulation duration has been reached */
    // TODO: Should make this its own function in GUtilities
    // TODO: Should also put all termination functions in a function within
    //       JamSailSimulation function
    if (Utilities.simTime_s >= Utilities.simTimeEnd_s)
    {
      /* Set sim status to False to indicate that sim has completed */
      Utilities.runSimStatus = GCONST_FALSE;
    }
  }
  while (Utilities.runSimStatus);

  /* ------------------------------------------------------------------------ *
   * Termination Phase
   * ------------------------------------------------------------------------ */

  /* Terminate BodyMgr */
  BodyMgr_terminate(&bodyMgr_state);

  /* Terminate JamSail */
  JamSail_terminate(&jamSail_state);

  return GCONST_EXIT_SUCCESS;
}
