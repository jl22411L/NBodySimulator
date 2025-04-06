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
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_AdcsStateEnum.h"

/* Generic Libraries */
#include "GConst/GConst.h"

int JamSail_controlAlgorithm(JamSail_State *p_jamSail_state_in)
{
  /* Declare local variables */
  /* None */

  if (p_jamSail_state_in->adcsState == DETUMBLING)
  {
    // TODO
  }
  else if (p_jamSail_state_in->adcsState == NOMINAL)
  {
    // TODO
  }

  return GCONST_TRUE;
}