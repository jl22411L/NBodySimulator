/*!
 *    @File:         Magnetometer_init.c
 *
 *    @Brief:        Function which will init a magnetometer sensor.
 *
 *    @Date:         30/01/2025
 *
 */

/* Function Includes */
#include "Magnetometer/PrivateFunctions/Magnetometer_PrivateFunctions.h"

/* Structure Include */
#include "Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Magnetometer/DataStructs/Magnetometer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int Magnetometer_init(const char          *p_magnetometerParamFilename_in,
                      Magnetometer_Params *p_magnetometerParams_out,
                      Magnetometer_State  *p_magnetometerState_out,
                      const char          *p_sensorBody_in)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;
  double        sensorFov_deg;

  /* Clear variables */
  GZero(&GParser_state, GParser_State);
  GZero(p_magnetometerParams_out, Magnetometer_Params);
  GZero(p_magnetometerState_out, Magnetometer_State);
  p_dic = NULL;

  /* Load parameters */
  p_dic = GParser_loadParams(&GParser_state, p_magnetometerParamFilename_in);

  /* Check that the parameters from the sensor have been loaded */
  if (p_dic == NULL)
  {
    GError("Failed to load parameters for SunSensor: %s",
           p_magnetometerParamFilename_in);
  }

  /* ------------------------------------------------------------------------ *
   * Load Parameters of Sensor
   * ------------------------------------------------------------------------ */

  /* load name of sensor */
  GParser_loadString(&GParser_state,
                     p_dic,
                     &(p_magnetometerParams_out->magnetometerName[0]),
                     "Sensor:sensorName");

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_magnetometerParams_out->sensorPosition_Bod_m[0]),
                          "SensorOrientation:sensorPosition_Bod_m",
                          3,
                          1);

  /* Load position of sensor relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_magnetometerParams_out->sensorQuaternion_Bod[0]),
                          "SensorOrientation:sensorQuaternion_BodToSen",
                          4,
                          1);

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  /*---------------------------- CREATE ARCHIVES ----------------------------*/

  /* Create archives */
  Magnetometer_createArchives(p_magnetometerParams_out,
                              p_magnetometerState_out,
                              p_sensorBody_in);

  return GCONST_TRUE;
}