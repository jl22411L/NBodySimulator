/*
 *    @File:         JamSail_updateState.c
 *
 *    @Brief:        Function which checks and udpates JamSail's state.
 *
 *    @Date:         08/04/2025
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_AdcsStateEnum.h"
#include "JamSail/ConstantDefs/JamSail_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GUtilities/GUtilities.h"

int JamSail_updateState(JamSail_State  *p_jamSail_state_out,
                        JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  double angularVelocityMagnitude_radps;

  /* Find the magnitude of the angular velocity */
  GMath_vectorMag(
      &angularVelocityMagnitude_radps,
      &(p_jamSail_state_out->gyro_state.filteredGyroVector_Sen_rads[0]));

  /* Check to see if start up procedure has completed */
  if ((p_jamSail_params_in->startTime_s) - Utilities.simTime_s <
      JAMSAIL_STARTUP_PROCESS_TIME_S)
  {
    /* Make sure that the state of JamSail is in startup */
    p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_STARTUP;
  }

  /* Check to see if JamSail should be in detumbling mode */
  else if (angularVelocityMagnitude_radps >
               ((p_jamSail_params_in
                     ->nominalToDetumblingModeAngularVelocityCutoff_radps)) &&
           (p_jamSail_state_out->adcsState == JAMSAIL_ADCSSTATE_NOMINAL))
  {
    p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_DETUMBLING;
  }

  /* Check to see if JamSail should be in nominal mode */
  else if ((angularVelocityMagnitude_radps <
            (p_jamSail_params_in
                 ->detumblingToNominalModeAngularVelocityCutoff_radps)) &&
           (p_jamSail_state_out->adcsState == JAMSAIL_ADCSSTATE_DETUMBLING))
  {
    p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_NOMINAL;
  }

  return GCONST_TRUE;
}