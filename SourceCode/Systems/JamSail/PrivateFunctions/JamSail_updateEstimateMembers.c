/*!
 *    @File:         JamSail_updateEstimateMembers.c
 *
 *    @Brief:        Function which will take the state vector and update the
 *                   members in the JamSail state struct.
 *
 *    @Date:         08/03/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int JamSail_updateEstimateMembers(double        *p_stateVector_in,
                                  JamSail_State *p_jamSail_state_out)
{
  /* Declare local variables */
  uint8_t i;

  /* Extrct the quaternion from the state vector */
  for (i = 0; i < 4; i++)
  {
    (p_jamSail_state_out->quaternionEstimate_InertCenToBod[i]) =
        *(p_stateVector_in + i);
  }

  /* Extract the angular velocity from the state vector */
  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[i]) =
        *(p_stateVector_in + i + 4);
  }

  return GCONST_TRUE;
}