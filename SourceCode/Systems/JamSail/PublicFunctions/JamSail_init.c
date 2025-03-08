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
  char          parameterBuffer[64];
  dictionary   *p_dic;
  GParser_State GParser_state;
  int           i;

  /* Clear Variables */
  GZero(&GParser_state, GParser_State);
  GZero(&parameterBuffer, char[64]);
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
   * EKF Initialize
   * ------------------------------------------------------------------------ */

  // TODO: Move all this to own function in JamSail_initEkf
  /* Load parameters */
  p_dic = GParser_loadParams(&GParser_state, "Parameters/JamSail.ini");

  /* Check that the parameters from the sensor have been loaded */
  if (p_dic == NULL)
  {
    GError("Failed to load parameters for Gyro: %s", "Parameters/JamSail.ini");
  }

  /* Load parameters for EKF system noise covariance matricies */
  for (i = 0; i < 7; i++)
  {
    /* Load name of parameter into buffer */
    sprintf(&(parameterBuffer[0]),
            "EkfProperties:systemNoiseCovariance[%d][%d]",
            i,
            i);

    /* Load parameter into member of JamSails params struct */
    GParser_loadDouble(&GParser_state,
                       p_dic,
                       &(p_jamSail_params_out->systemNoiseCovariance[i][i]),
                       &(parameterBuffer[0]));

    /* Clear buffer */
    GZero(&parameterBuffer, char[64]);
  }

  /* Load parameters for EKF sensor noise covariance matricies */
  for (i = 0; i < 3; i++)
  {
    /* Load name of parameter into buffer */
    sprintf(&(parameterBuffer[0]),
            "EkfProperties:sensorNoiseCovariance[%d][%d]",
            i,
            i);

    /* Load parameter into member of JamSails params struct */
    GParser_loadDouble(&GParser_state,
                       p_dic,
                       &(p_jamSail_params_out->sensorNoiseCovariance[i][i]),
                       &(parameterBuffer[0]));

    /* Clear buffer */
    GZero(&parameterBuffer, char[32]);
  }

  /* Set initial condition of quaternion. (All other elements are zero) */
  (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]) = 1.0;

  /* Set initial condition for error covariance */
  for (i = 0; i < 7; i++)
  {
    p_jamSail_state_out->errorCovariance[i][i] = 1.0;
  }

  /* Load the measurement jacobian matrix for the EKF with coefficient */
  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_out->measurementJacobian[i][i + 4]) = 1.0;
  }

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  /* Init Archives */
  // TODO: put in own function
  GArchive_init(&p_jamSail_state_out->ekfArchive,
                "Bodies/JamSail/ArchiveData/ContinuousEkf");

  /* Add column */
  GArchive_addCol(&p_jamSail_state_out->ekfArchive,
                  "quaternionEstimate_InertCenToBod",
                  4,
                  1);

  /* Add column */
  GArchive_addCol(&p_jamSail_state_out->ekfArchive,
                  "angularVelocityEstimate_Bod_rads",
                  3,
                  1);

  // /* Add column */
  // GArchive_addCol(&p_jamSail_state_out->ekfArchive,
  //                 "magneticFieldEstimate_Bod_nT",
  //                 3,
  //                 1);

  /* Write header for archive */
  GArchive_writeHeader(&p_jamSail_state_out->ekfArchive);

  return GCONST_TRUE;
}
