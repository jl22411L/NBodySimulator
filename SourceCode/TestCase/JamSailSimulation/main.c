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
#include "JamSail/PublicFunctions/JamSail_PublicFunctions.h"
#include "SatelliteBody/PublicFunctions/SatelliteBody_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "Gravity/DataStructs/Gravity_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GMath/GMath.h"
#include "GUtilities/GUtilities.h"
#include "GZero/GZero.h"

int main(void)
{
  /* Declaring local variables */
  Gravity_Params gravity_params;
  BodyMgr_State  bodyMgr_state;
  JamSail_State  jamSail_state;
  int            i;

  /* Clear local variables */
  GZero(&jamSail_state, JamSail_State);
  GZero(&bodyMgr_state, BodyMgr_State);
  GZero(&gravity_params, Gravity_Params);

  /* ####################################################################### *
   *                          INITIALIZE SIMULATION                          *
   * ####################################################################### */

  /* Initialize GUtilitites */
  GUtilities_init("Parameters/SimulationParameters.ini");

  /* Initialize Gravity Module */
  Gravity_init(&gravity_params, "Parameters/GravityParameters.ini");

  /* Initialize BodyMgr */
  BodyMgr_init(&bodyMgr_state, "Parameters/BodyMgrParameters.ini");

  /* ####################################################################### *
   *                            INITIALIZE JAMSAIL                           *
   * ####################################################################### */

  /* Initialize JamSail */
  JamSail_init(&jamSail_state);

  /* -----------------------------------------------------------------------
   * ENTER CYCLICAL EXECUTION
   * ----------------------------------------------------------------------- */

  /* Display text to indicate that cyclical execution has been reached */
  GLog("# ------------------------ ENTERING CYLICAL EXECUTION "
       "------------------------ #");

  /* Enter into cyclic execution */
  do
  {
    /* ###################################################################### *
     *                             PRE-STEP PHASE                             *
     * ###################################################################### */

    /* ---------------------------------------------------------------------- *
     *                    SIMULATION PRE-STEP CALCULATIONS                    *
     * ---------------------------------------------------------------------- */

    /* Apply gravity to UAV body */
    Gravity_findGravity(&gravity_params,
                        bodyMgr_state.p_rigidBodyPointerList,
                        bodyMgr_state.nBodies);

    /* Step the bodies */
    BodyMgr_step(&bodyMgr_state);

    /* ---------------------------------------------------------------------- *
     *                     JAM-SAIL PRE-STEP CALCULATIONS                     *
     * ---------------------------------------------------------------------- */

    /* Find vector from JamSail to Sun in fixed frame */
    // TODO: The jamSail_state is not initialised, hence this has a sig fault
    // GMath_vectorSub(
    //     &(*(bodyMgr_state.p_rigidBodyPointerList + 2))->position_m_Fix[0],
    //     &((jamSail_state.p_satelliteBody_state)
    //           ->rigidBody_state.position_m_Fix[0]),
    //     &jamSail_state.trueSunVector_m_fix[0]);

    // /* Find vector from JamSail to Sun in body frame */
    // GMath_quaternionPointRotation(
    //     &jamSail_state.trueSunVector_m_bod[0],
    //     &jamSail_state.trueSunVector_m_fix[0],
    //     &((jamSail_state.p_satelliteBody_state)
    //           ->rigidBody_state.quaternion_FixedToBody[0]));

    /* Find magnetic vector in fixed frame */
    // Need to apply model for magnetic field

    /* Find magnectic vector in body frame */
    // Some quaternion rotation

    /* ###################################################################### *
     *                               STEP PHASE                               *
     * ###################################################################### */

    /* ---------------------------------------------------------------------- *
     *                      SIMULATION STEP CALCULATIONS                      *
     * ---------------------------------------------------------------------- */

    /* Step forawrd in time */
    Utilities.simTime_s += Utilities.simTimeStep_s;

    /* ---------------------------------------------------------------------- *
     *                       JAM-SAIL STEP CALCULATIONS                       *
     * ---------------------------------------------------------------------- */

    /* None */

    /* ###################################################################### *
     *                          CHECK END CONDITIONS                          *
     * ###################################################################### */

    /* Check if the simulation duration has been reached */
    // TODO: Should make this its own function in GUtilities
    // TODO: Should also put all termination functions in a function within
    //       JamSailSimulation function
    if (Utilities.simTime_s >= Utilities.simTimeDuration_s)
    {
      /* Set sim status to False to indicate that sim has completed */
      Utilities.runSimStatus = GCONST_FALSE;
    }
  }
  while (Utilities.runSimStatus);

  /* ####################################################################### *
   *                        TERMINATION OF SIMULATION                        *
   * ####################################################################### */

  /* ------------------------------- Bodies -------------------------------- */

  /* Terminate BodyMgr */
  BodyMgr_terminate(&bodyMgr_state);

  return GCONST_EXIT_SUCCESS;
}
