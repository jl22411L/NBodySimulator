/*
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
#include "SunSensor/DataStructs/SunSensor_Params.h"
#include "SunSensor/DataStructs/SunSensor_State.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int SunSensor_init(const char       *p_sunSensorParamFilename_in,
                   SunSensor_Params *p_sunSensor_params_out,
                   SunSensor_State  *p_sunSesor_state_out,
                   const char       *p_sensorBody_in)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;

  /* Clear variables */
  GZero(&GParser_state, GParser_State);
  GZero(p_sunSensor_params_out, SunSensor_Params);
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
                     &p_sunSensor_params_out->sunSensorName[0],
                     "Sensor:sensorName");

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_sunSensor_params_out->sensorPosition_Bod_m[0]),
                          "SensorOrientation:sensorPosition_Bod_m",
                          1,
                          3);

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_sunSensor_params_out->sensorQuaternion_Bod[0]),
                          "SensorOrientation:sensorQuaternion_Bod",
                          1,
                          4);

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  SunSensor_createArchives(p_sunSensor_params_out,
                           p_sunSesor_state_out,
                           p_sensorBody_in);

  return GCONST_TRUE;
}