/*!
 *    @File:         JamSail_init.c
 *
 *    @Brief:        Init function for Jam Sail
 *
 *    @Date:         08/07/2024
 *
 */

/* Function Includes */
#include "Actuators/Magnetorquer/PublicFunctions/Magnetorquer_PublicFunctions.h"
#include "BodyMgr/PublicFunctions/BodyMgr_PublicFunctions.h"
#include "Sensors/Gyro/PublicFunctions/Gyro_PublicFunctions.h"
#include "Sensors/Magnetometer/PublicFunctions/Magnetometer_PublicFunctions.h"
#include "Sensors/SunSensor/PublicFunctions/SunSensor_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int JamSail_init(JamSail_State  *p_jamSail_state_out,
                 JamSail_Params *p_jamSail_params_out,
                 BodyMgr_State  *p_bodyMgr_state_in)
{
  /* Define Local Variables */
  /* None */

  /* Clear Variables */
  p_jamSail_state_out->p_satelliteBody_state = NULL;

  /* ------------------------------------------------------------------------ *
   * Satellite Initialization
   * ------------------------------------------------------------------------ */

  /* Find the JamSail body within bodyMgr */
  BodyMgr_findSatelliteBody(p_bodyMgr_state_in,
                            &(p_jamSail_state_out->p_satelliteBody_state),
                            "JamSail");

  /* Check that body was assigned correctly */
  if (p_jamSail_state_out->p_satelliteBody_state == NULL)
  {
    GError("Satellite body was not asssigned to JamSail state correctly");
  }

  /* ------------------------------------------------------------------------
   * * Sensor Initialization
   * ------------------------------------------------------------------------
   */

  /* Initialize Sun Sensor */
  SunSensor_init("Parameters/SunSensor.ini",
                 &(p_jamSail_params_out->sunSensor_params),
                 &(p_jamSail_state_out->sunSensor_state),
                 &((p_jamSail_state_out->p_satelliteBody_state)
                       ->rigidBody_state.bodyName[0]));

  /* Initialize Magnetometer */
  Magnetometer_init("Parameters/Magnetometer.ini",
                    &(p_jamSail_params_out->magnetometer_params),
                    &(p_jamSail_state_out->magnetometer_state),
                    &((p_jamSail_state_out->p_satelliteBody_state)
                          ->rigidBody_state.bodyName[0]));

  /* Initialize Gyro */
  Gyro_init("Parameters/Gyro.ini",
            &(p_jamSail_params_out->gyro_params),
            &(p_jamSail_state_out->gyro_state),
            &((p_jamSail_state_out->p_satelliteBody_state)
                  ->rigidBody_state.bodyName[0]));

  /* Initialize Accelerometer */
  // TODO

  /* ------------------------------------------------------------------------
   * * Actuator Initialization
   * ------------------------------------------------------------------------
   */

  /* Initialize Magnetorquer */
  Magnetorquer_init("Parameters/Magnetorquer.ini",
                    &(p_jamSail_params_out->magnetorquer_params),
                    &(p_jamSail_state_out->magnetorquer_state),
                    &((p_jamSail_state_out->p_satelliteBody_state)
                          ->rigidBody_state.bodyName[0]));

  /* Initialze Solar Sail */
  // TODO

  return GCONST_TRUE;
}
