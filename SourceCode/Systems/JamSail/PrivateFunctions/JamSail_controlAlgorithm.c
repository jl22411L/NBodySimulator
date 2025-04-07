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

  if (p_jamSail_state_out->adcsState == DETUMBLING)
  {
    /* Apply detumbling control algorithm */
    JamSail_detumblingAlgorithm(p_jamSail_state_out, p_jamSail_params_in);
  }
  else if (p_jamSail_state_out->adcsState == NOMINAL)
  {
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
  }

  return GCONST_TRUE;
}