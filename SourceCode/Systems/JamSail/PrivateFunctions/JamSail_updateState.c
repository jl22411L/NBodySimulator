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
  GMath_vectorMag(&angularVelocityMagnitude_radps,
                  &(p_jamSail_state_out->angularVelocityEstimate_Bod_rads[0]),
                  3);

  switch (p_jamSail_state_out->adcsState)
  {
  case (JAMSAIL_ADCSSTATE_STARTUP):
    /* If start up procedure has finished, switch to sun searching mode */
    if (((Utilities.simTime_s - p_jamSail_params_in->startTime_s) >
         JAMSAIL_STARTUP_PROCESS_TIME_S) &&
        (angularVelocityMagnitude_radps <
         p_jamSail_params_in
             ->nominalToDetumblingModeAngularVelocityCutoff_radps))
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_SUN_SEARCHING;
    }
    /* Else put in detumbling mode */
    else if (((Utilities.simTime_s - p_jamSail_params_in->startTime_s) >
              JAMSAIL_STARTUP_PROCESS_TIME_S))
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_DETUMBLING;
    }
    break;

  case (JAMSAIL_ADCSSTATE_DETUMBLING):
    /* Check if angular velocities are reduced low enough */
    if (angularVelocityMagnitude_radps <
        p_jamSail_params_in->detumblingToNominalModeAngularVelocityCutoff_radps)
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_SUN_SEARCHING;
    }
    break;

  case (JAMSAIL_ADCSSTATE_SUN_SEARCHING):
    /* If we find the sun, go to sun tracking mode */
    if ((p_jamSail_state_out->sunSensor_state.isSensorReadingInvalid ==
         GCONST_FALSE) &&
        (angularVelocityMagnitude_radps <
         p_jamSail_params_in
             ->nominalToDetumblingModeAngularVelocityCutoff_radps))
    {
      /* Set tracking time to 0 */
      p_jamSail_state_out->trackingTimeOfSun_s = 0.0;

      /* Switch state to track the sun */
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_SUN_TRACKING;
    }
    /* If the angular velocities are too large, go to detumbling mode */
    else if (angularVelocityMagnitude_radps >
             p_jamSail_params_in
                 ->nominalToDetumblingModeAngularVelocityCutoff_radps)
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_DETUMBLING;
    }
    break;

  case (JAMSAIL_ADCSSTATE_SUN_TRACKING):
    /* If we find the sun, incriment the time we have been tracking the sun */
    if ((p_jamSail_state_out->sunSensor_state.isSensorReadingInvalid ==
         GCONST_FALSE))
    {
      p_jamSail_state_out->trackingTimeOfSun_s += Utilities.simTimeStep_s;
    }
    /* If sun is no longer found, go back to searching for it. */
    else
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_SUN_SEARCHING;
    }

    /* If suns been tracked for sufficient amount of time, start nominal mode */
    if ((p_jamSail_state_out->trackingTimeOfSun_s > 600) &&
        (angularVelocityMagnitude_radps <
         p_jamSail_params_in
             ->nominalToDetumblingModeAngularVelocityCutoff_radps))
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_NOMINAL;
    }

    /* If angular velocities are too large, switch to detumbling mode */
    if (angularVelocityMagnitude_radps >
        p_jamSail_params_in->nominalToDetumblingModeAngularVelocityCutoff_radps)
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_DETUMBLING;
    }
    break;
  case (JAMSAIL_ADCSSTATE_NOMINAL):
    /* IF we havn't measured the sun for some time, go searching for it */
    if ((Utilities.simTime_s - (p_jamSail_state_out->timeOfLastMeasurement_s) >
         300) &&
        (angularVelocityMagnitude_radps <
         p_jamSail_params_in
             ->nominalToDetumblingModeAngularVelocityCutoff_radps))
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_SUN_SEARCHING;
    }

    /* If angular velocities are too large, switch to detumbling mode */
    if (angularVelocityMagnitude_radps >
        p_jamSail_params_in->nominalToDetumblingModeAngularVelocityCutoff_radps)
    {
      p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_DETUMBLING;
    }
    break;
  default:
    /* If state is unknown put into detumbling mode */
    p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_DETUMBLING;
    break;
  }

  return GCONST_TRUE;
}