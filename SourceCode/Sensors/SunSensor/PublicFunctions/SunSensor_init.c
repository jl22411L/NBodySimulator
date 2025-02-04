/*!
 *    @File:         SunSensor_init.c
 *
 *    @Brief:        Function which will init SunSensor model
 *
 *    @Date:         11/11/2024
 *
 */

/* Function Includes */
#include "SunSensor/PrivateFunctions/SunSensor_PrivateFunctions.h"

/* Structure Include */
#include "SunSensor/DataStructs/SunSensor_ParamsStruct.h"
#include "SunSensor/DataStructs/SunSensor_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int SunSensor_init(const char       *p_sunSensorParamFilename_in,
                   SunSensor_Params *p_sunSensor_params_out,
                   SunSensor_State  *p_sunSensor_state_out,
                   const char       *p_sensorBody_in)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;
  double        sensorFov_deg;

  /* Clear variables */
  GZero(&GParser_state, GParser_State);
  GZero(p_sunSensor_params_out, SunSensor_Params);
  GZero(p_sunSensor_state_out, SunSensor_State);
  p_dic = NULL;

  /* Load parameters */
  p_dic = GParser_loadParams(&GParser_state, p_sunSensorParamFilename_in);

  /* Check that the parameters from the sensor have been loaded */
  if (p_dic == NULL)
  {
    GError("Failed to load parameters for SunSensor: %s",
           p_sunSensorParamFilename_in);
  }

  /* ------------------------------------------------------------------------ *
   * Load Parameters of Sensor
   * ------------------------------------------------------------------------ */

  /* load name of sensor */
  GParser_loadString(&GParser_state,
                     p_dic,
                     &(p_sunSensor_params_out->sunSensorName[0]),
                     "Sensor:sensorName");

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_sunSensor_params_out->sensorPosition_Bod_m[0]),
                          "SensorOrientation:sensorPosition_Bod_m",
                          3,
                          1);

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_sunSensor_params_out->sensorQuaternion_BodToSen[0]),
      "SensorOrientation:sensorQuaternion_BodToSen",
      4,
      1);

  /* Load FOV of sun sensor into temporary variable */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &sensorFov_deg,
                     "SensorCharecteristics:sensorFov_deg");

  /* Load the fov of sun sensor as radians into params struct */
  p_sunSensor_params_out->sensorFov_rad = sensorFov_deg * GCONST_DEG_TO_RAD;

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  SunSensor_createArchives(p_sunSensor_params_out,
                           p_sunSensor_state_out,
                           p_sensorBody_in);

  return GCONST_TRUE;
}