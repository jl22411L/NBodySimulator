/*!
 *    @File:         JamSail_detumblingAlgorithm.c
 *
 *    @Brief:        File which contains detumbling algorithm for JamSail.
 *
 *    @Date:         06/04/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_AdcsStateEnum.h"

/* Generic Libraries */
#include "GConst/GConst.h"

int JamSail_detumblingAlgorithm(JamSail_State *p_jamSail_state_inout)
{
  /* Declare local variables */
  double  angularVelocitiesError_rads[3];
  uint8_t i;

  for (i = 0; i < 3; i++)
  {
    angularVelocitiesError_rads[i] =
        0.0 - (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i]);
  }

  return GCONST_TRUE;
}