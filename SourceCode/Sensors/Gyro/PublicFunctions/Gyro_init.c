/*!
 *    @File:         Gyro_init.c
 *
 *    @Brief:        Function which will init Gyro model.
 *
 *    @Date:         05/02/2025
 *
 */

/* Function Includes */
#include "Gyro/PrivateFunctions/Gyro_PrivateFunctions.h"

/* Structure Include */
#include "Gyro/DataStructs/Gyro_ParamsStruct.h"
#include "Gyro/DataStructs/Gyro_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int Gyro_init(const char  *p_gyroParamFilename_in,
              Gyro_Params *p_gyro_params_out,
              Gyro_State  *p_gyro_state_out,
              const char  *p_sensorBody_in)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;
  double        sensorFov_deg;

  /* Clear variables */
  GZero(&GParser_state, GParser_State);
  GZero(p_gyro_params_out, Gyro_Params);
  GZero(p_gyro_state_out, Gyro_State);
  p_dic = NULL;

  /* Load parameters */
  p_dic = GParser_loadParams(&GParser_state, p_gyroParamFilename_in);

  /* Check that the parameters from the sensor have been loaded */
  if (p_dic == NULL)
  {
    GError("Failed to load parameters for Gyro: %s", p_gyroParamFilename_in);
  }

  /* ------------------------------------------------------------------------ *
   * Load Parameters of Sensor
   * ------------------------------------------------------------------------ */

  /* load name of sensor */
  GParser_loadString(&GParser_state,
                     p_dic,
                     &(p_gyro_params_out->gyroName[0]),
                     "Sensor:sensorName");

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_gyro_params_out->sensorPosition_Bod_m[0]),
                          "SensorOrientation:sensorPosition_Bod_m",
                          3,
                          1);

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_gyro_params_out->sensorQuaternion_BodToSen[0]),
                          "SensorOrientation:sensorQuaternion_BodToSen",
                          4,
                          1);

  /* Load mean noise components of sensor */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_gyro_params_out->noiseMean_Sen_rads[0]),
                          "SensorNoise:noiseMean_Sen_rads",
                          3,
                          1);

  /* Load standard deviation of noise components for sensor */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_gyro_params_out->noiseStandardDeviation_Sen_rads[0]),
      "SensorNoise:noiseStandardDeviation_Sen_rads",
      3,
      1);

  /* Load amplitude of noise comonents for sensor */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_gyro_params_out->noiseAmplitude_Sen_rads[0]),
                          "SensorNoise:noiseAmplitude_Sen_rads",
                          3,
                          1);

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  Gyro_createArchives(p_gyro_params_out, p_gyro_state_out, p_sensorBody_in);

  return GCONST_TRUE;
}