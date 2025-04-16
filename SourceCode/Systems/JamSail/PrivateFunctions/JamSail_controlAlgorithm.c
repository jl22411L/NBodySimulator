/*!
 *    @File:         JamSail_controlAlgorithm.c
 *
 *    @Brief:        Private function which determines jamsail's control
 *                   algorithm.
 *
 *    @Date:         06/04/2025
 *
 */

/* Function Includes */
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_AdcsStateEnum.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int JamSail_controlAlgorithm(JamSail_State  *p_jamSail_state_out,
                             JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  /* None */

  switch (p_jamSail_state_out->adcsState)
  {
  case (JAMSAIL_ADCSSTATE_STARTUP):
    /* Apply detumbling control algorithm */
    JamSail_detumblingAlgorithm(p_jamSail_state_out, p_jamSail_params_in);
    break;
  case (JAMSAIL_ADCSSTATE_DETUMBLING):
    /* Apply detumbling control algorithm */
    JamSail_detumblingAlgorithm(p_jamSail_state_out, p_jamSail_params_in);
    break;
  case (JAMSAIL_ADCSSTATE_SUN_SEARCHING):
    /* Apply control algorithm to search for the sun */
    JamSail_sunSearchingControl(p_jamSail_state_out, p_jamSail_params_in);
    break;
  case (JAMSAIL_ADCSSTATE_SUN_TRACKING):
    /* Apply control algorithm to track the sun */
    JamSail_sunTrackingControl(p_jamSail_state_out, p_jamSail_params_in);
    break;
  case (JAMSAIL_ADCSSTATE_NOMINAL):
    /* Find required quaternion */
    JamSail_findRequiredQuaternion(
        p_jamSail_state_out,
        p_jamSail_params_in,
        &(p_jamSail_state_out->requiredQuaternion_InertCenToBod[0]));

    /* Apply nominal control algorithm */
    JamSail_nominalAlgorithm(
        p_jamSail_state_out,
        p_jamSail_params_in,
        &(p_jamSail_state_out->requiredQuaternion_InertCenToBod[0]));
    break;
  default:
    /* If state is unknown put into detumbling mode */
    p_jamSail_state_out->adcsState = JAMSAIL_ADCSSTATE_DETUMBLING;
    break;
  }

  return GCONST_TRUE;
}