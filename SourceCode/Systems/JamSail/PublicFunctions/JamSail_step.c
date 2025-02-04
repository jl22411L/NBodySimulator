/*!
 *    @File:         JamSail_step.c
 *
 *    @Brief:        Function which will step JamSail in the simulation.
 *
 *    @Date:         29/01/2025
 *
 */

/* Function Includes */
#include "BodyMgr/PublicFunctions/BodyMgr_PublicFunctions.h"
#include "Magnetometer/PublicFunctions/Magnetometer_PublicFunctions.h"
#include "SunSensor/PublicFunctions/SunSensor_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int JamSail_step(JamSail_State  *p_jamSail_state_out,
                 JamSail_Params *p_jamSail_params_in,
                 BodyMgr_State  *p_bodyMgr_state_in,
                 Igrf_Params    *p_igrf_params_in,
                 double          simTime_s_in)
{
  /* Declare local variables */
  CelestialBody_State *p_sunCelestialBody;

  /* Clear Variables */
  p_sunCelestialBody = NULL;

  /* Find the sun body */
  GAssess(BodyMgr_findCelestialBody(p_bodyMgr_state_in,
                                    &(p_sunCelestialBody),
                                    "Sun"));

  /* Check that a celestial body was found */
  if (p_sunCelestialBody == NULL)
  {
    GError("Sun Body was not found correctly");
  }

  /* ------------------------------------------------------------------------ *
   * Step Sensors
   * ------------------------------------------------------------------------ */

  /* Step Sun Sensor */
  SunSensor_step(&((p_jamSail_state_out->p_satelliteBody_state)
                       ->rigidBody_state.position_Fix_m[0]),
                 &((p_jamSail_state_out->p_satelliteBody_state)
                       ->rigidBody_state.quaternion_FixToBody[0]),
                 p_sunCelestialBody,
                 p_bodyMgr_state_in,
                 &(p_jamSail_params_in->sunSensor_params),
                 &(p_jamSail_state_out->sunSensor_state));

  /* Step Magnetometer */
  Magnetometer_step(&(p_jamSail_params_in->magnetometer_params),
                    &(p_jamSail_state_out->magnetometer_state),
                    p_igrf_params_in,
                    p_sunCelestialBody,
                    &(p_jamSail_state_out->p_satelliteBody_state
                          ->rigidBody_state.position_Fix_m[0]),
                    &(p_jamSail_state_out->p_satelliteBody_state
                          ->rigidBody_state.quaternion_FixToBody[0]),
                    simTime_s_in);

  /* Step IMU */
  // TODO

  /* ------------------------------------------------------------------------ *
   * Step Determination Algorithms
   * ------------------------------------------------------------------------ */

  /* Step Low-High Pass Filter */
  // TODO

  /* Step Determination Algorithm */
  // TODO

  /* ------------------------------------------------------------------------ *
   * Step Control Algorithms
   * ------------------------------------------------------------------------ */

  /* Step Control Algorithm */
  // TODO

  /* ------------------------------------------------------------------------ *
   * Step Actuators
   * ------------------------------------------------------------------------ */

  /* Step Magnetorquer */
  // TODO

  return GCONST_TRUE;
}