/*!
 *    @File:         JamSail_attitudeDetermination.c
 *
 *    @Brief:        Function which runs JamSail's determination algorithm
 *
 *    @Date:         05/03/2025
 *
 */

#include <stdint.h>

/* Function Includes */
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int JamSail_attitudeDetermination(JamSail_State  *p_jamSail_state_inout,
                                  JamSail_Params *p_jamSail_params_in,
                                  double          timeStep_s_in)
{
  /* Declare local variables */
  /* None */

  /* Measure JamSail's attitude */
  JamSail_attitudeEstimation(p_jamSail_state_inout,
                             p_jamSail_params_in,
                             timeStep_s_in);

  // /* Check if the sun sensor reading is valid */
  // if (p_jamSail_state_inout->sunSensor_state.isSensorReadingInvalid)
  // {}
  // else
  // {
  //   /* Run estimation of JamSail attitude */
  // }

  return GCONST_TRUE;
}