/*!
 *    @File:         JamSail_init.c
 *
 *    @Brief:        Init function for Jam Sail
 *
 *    @Date:         08/07/2024
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Function Includes */
#include "Actuators/Magnetorquer/PublicFunctions/Magnetorquer_PublicFunctions.h"
#include "BodyMgr/PublicFunctions/BodyMgr_PublicFunctions.h"
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"
#include "Sensors/Gyro/PublicFunctions/Gyro_PublicFunctions.h"
#include "Sensors/Magnetometer/PublicFunctions/Magnetometer_PublicFunctions.h"
#include "Sensors/SunSensor/PublicFunctions/SunSensor_PublicFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_Const.h"

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int JamSail_init(JamSail_State  *p_jamSail_state_out,
                 JamSail_Params *p_jamSail_params_out,
                 BodyMgr_State  *p_bodyMgr_state_in)
{
  /* Define Local Variables */
  dictionary   *p_dic;
  GParser_State GParser_state;
  int           i;

  /* Clear Variables */
  GZero(&GParser_state, GParser_State);
  p_dic = NULL;

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

  /* ------------------------------------------------------------------------ *
   * Sensor Initialization
   * ------------------------------------------------------------------------ */

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

  /* ------------------------------------------------------------------------ *
   * Actuator Initialization
   * ------------------------------------------------------------------------ */

  /* Initialize Magnetorquer */
  Magnetorquer_init("Parameters/Magnetorquer.ini",
                    &(p_jamSail_params_out->magnetorquer_params),
                    &(p_jamSail_state_out->magnetorquer_state),
                    &((p_jamSail_state_out->p_satelliteBody_state)
                          ->rigidBody_state.bodyName[0]));

  /* Initialze Solar Sail */
  // TODO

  /* ------------------------------------------------------------------------ *
   * ADCS Initialize
   * ------------------------------------------------------------------------ */

  /* Initialize Attitude Determination of JamSail */
  JamSail_initAttitudeDetermination(p_jamSail_state_out, p_jamSail_params_out);

  /* Init IGRF model */
  Igrf_init(&(p_jamSail_params_out->igrfModel_params),
            "Parameters/IgrfParameters.ini",
            13,
            13);

  return GCONST_TRUE;
}
