/*!
 *    @File:         JamSail_step.c
 *
 *    @Brief:        Function which will step JamSail in the simulation.
 *
 *    @Date:         29/01/2025
 *
 */

#include <stdint.h>

/* Function Includes */
#include "Actuators/Magnetorquer/PublicFunctions/Magnetorquer_PublicFunctions.h"
#include "BodyMgr/PublicFunctions/BodyMgr_PublicFunctions.h"
#include "Guidance/ContinuousEkf/PublicFunctions/ContinuousEkf_PublicFunctions.h"
#include "Guidance/KeplarianPropogation/PublicFunctions/KeplarianPropogation_PublicFunctions.h"
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"
#include "SensorFilters/PublicFunctions/SensorFilter_PublicFunctions.h"
#include "Sensors/Gyro/PublicFunctions/Gyro_PublicFunctions.h"
#include "Sensors/Magnetometer/PublicFunctions/Magnetometer_PublicFunctions.h"
#include "Sensors/SunSensor/PublicFunctions/SunSensor_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_AdcsStateEnum.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GUtilities/GUtilities.h"

int JamSail_step(JamSail_State  *p_jamSail_state_out,
                 JamSail_Params *p_jamSail_params_in,
                 BodyMgr_State  *p_bodyMgr_state_in,
                 Igrf_Params    *p_igrf_params_in,
                 double          simTime_s_in,
                 double          simTimeStep_s_in)
{
  /* Declare local variables */
  CelestialBody_State *p_sunCelestialBody;
  CelestialBody_State *p_earthCelestialBody;
  uint8_t              i;

  /* Clear Variables */
  p_sunCelestialBody   = NULL;
  p_earthCelestialBody = NULL;

  /* Find the Sun body */
  GAssess(BodyMgr_findCelestialBody(p_bodyMgr_state_in,
                                    &(p_sunCelestialBody),
                                    "Sun"));

  /* Check that a celestial body was found */
  if (p_sunCelestialBody == NULL)
  {
    GError("Sun Body was not found correctly");
  }

  /* Find the Earth body */
  GAssess(BodyMgr_findCelestialBody(p_bodyMgr_state_in,
                                    &(p_earthCelestialBody),
                                    "Earth"));

  /* Check that a celestial body was found */
  if (p_earthCelestialBody == NULL)
  {
    GError("Earth Body was not found correctly");
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
                    p_earthCelestialBody,
                    &(p_jamSail_state_out->p_satelliteBody_state
                          ->rigidBody_state.position_Fix_m[0]),
                    &(p_jamSail_state_out->p_satelliteBody_state
                          ->rigidBody_state.quaternion_FixToBody[0]),
                    simTime_s_in);

  /* Step Gyro */
  Gyro_step(&(p_jamSail_params_in->gyro_params),
            &(p_jamSail_state_out->gyro_state),
            &((p_jamSail_state_out->p_satelliteBody_state)
                  ->rigidBody_state.angularVelocity_rads_Bod[0]));

  /* ------------------------------------------------------------------------ *
   * JamSail's ADCS
   * ------------------------------------------------------------------------ */

  /* Check and update step of JamSail */
  JamSail_updateState(p_jamSail_state_out, p_jamSail_params_in);

  /* Step Low-High Pass Filter */
  JamSail_filterSensors(p_jamSail_state_out, p_jamSail_params_in);

  /* Perform keplarian propogation to find position of JamSail */
  KeplarianPropogation_keplarianToCartesian(
      (p_jamSail_params_in->jamSailMass_kg),
      (p_jamSail_params_in->earthMass_kg),
      (p_jamSail_params_in->semiMajorAxis_km) * GCONST_KM_TOLERANCE,
      (p_jamSail_params_in->eccentricity),
      (p_jamSail_params_in->inclination_rad),
      (p_jamSail_params_in->argumentOfPerigee_rad),
      (p_jamSail_params_in->raans_rad),
      (p_jamSail_params_in->timeSincePeriapsis_s),
      simTime_s_in,
      &(p_jamSail_state_out->positionEstimate_InertCen_m[0]));

  /* Step Determination Algorithm */
  JamSail_attitudeDetermination(p_jamSail_state_out,
                                p_jamSail_params_in,
                                simTime_s_in,
                                simTimeStep_s_in);

  /* ----------------------------- Archive Data ---------------------------- */

  /* Archive attitude determination results */
  JamSail_archiveData(p_jamSail_state_out);

  /* ------------------------------------------------------------------------ *
   * Step Actuators
   * ------------------------------------------------------------------------ */

  /* Step Magnetorquer */
  Magnetorquer_step(&(p_jamSail_state_out->magnetorquer_state),
                    &(p_jamSail_params_in->magnetorquer_params),
                    p_igrf_params_in,
                    p_earthCelestialBody,
                    &((p_jamSail_state_out->p_satelliteBody_state)
                          ->rigidBody_state.position_Fix_m[0]),
                    &((p_jamSail_state_out->p_satelliteBody_state)
                          ->rigidBody_state.quaternion_FixToBody[0]),
                    simTime_s_in);

  /* ------------------------------------------------------------------------ *
   * Find resultant loads
   * ------------------------------------------------------------------------ */

  /* Find the resultant Torque on JamSail */
  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_out->p_satelliteBody_state->rigidBody_state
         .resultantMoment_Nm_Bod[i]) =
        (p_jamSail_state_out->controlTorque_Bod_Nm[i]);
  }

  return GCONST_TRUE;
}