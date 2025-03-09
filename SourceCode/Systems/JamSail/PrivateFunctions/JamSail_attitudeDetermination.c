/*!
 *    @File:         JamSail_attitudeDetermination.c
 *
 *    @Brief:        Function which runs JamSail's determination algorithm
 *
 *    @Date:         05/03/2025
 *
 */

#include <stdio.h>

/* Function Includes */
#include "Guidance/KeplarianPropogation/PublicFunctions/KeplarianPropogation_PublicFunctions.h"
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int JamSail_attitudeDetermination(JamSail_State  *p_jamSail_state_inout,
                                  JamSail_Params *p_jamSail_params_in,
                                  double          simTim_s_in,
                                  double          timeStep_s_in)
{
  /* Declare local variables */
  double jamSailPosition_InertCen_m[3];

  /* Clear variables */
  GZero(&(jamSailPosition_InertCen_m[0]), double[3]);

  /* Perform keplarian propogation to find position of JamSail */
  // KeplarianPropogation_keplarianToCartesian();

  /* Find coordinates in spherical form */
  // TODO

  /* Find Magnetic fielf from IGRF model in NED frame */
  // TODO Igrf_step();

  /* Convert magnetic field into Geo-Centric frame */
  // TODO

  /* Find quaternioon from ECI to Geo-Centric frame */
  // TODO

  /* Rotate magnetic field from Geo-Centric to ECI frame */
  // TODO

  /* Find norm of magnetic field  */
  // TODO

  /* Check if the sun sensor reading is valid */
  if (p_jamSail_state_inout->sunSensor_state.isSensorReadingInvalid)
  {
    /* Perform keplarian propogation to find position of sun */
    // TODO

    // TODO:  Remember to move this down to else part of if statement
    /* Find magnetic field in the body frame */
    // TODO: (Add magnetic field estimate to JamSail state)

    /* Measure JamSail's attitude */
    JamSail_attitudeEstimation(p_jamSail_state_inout,
                               p_jamSail_params_in,
                               timeStep_s_in);
  }
  else
  {
    /* Run estimation of JamSail attitude */

    /* Set flag to indicate that measurement was taken for timestep */
    p_jamSail_state_inout->attitudeMeasuredFlag = GCONST_TRUE;
  }

  int i;
  printf("[");
  for (i = 0; i < 4; i++)
  {
    printf("%lf ", p_jamSail_state_inout->quaternionEstimate_InertCenToBod[i]);
  }
  for (i = 0; i < 3; i++)
  {
    printf("%lf ", p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i]);
  }
  printf("] [");
  for (i = 0; i < 4; i++)
  {
    printf("%lf ",
           p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
               .quaternion_FixToBody[i]);
  }
  for (i = 0; i < 3; i++)
  {
    printf("%lf ",
           p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
               .angularVelocity_rads_Bod[i]);
  }
  printf("]\n");

  /* Archive attitude determination results */
  JamSail_archiveData(p_jamSail_state_inout);

  return GCONST_TRUE;
}