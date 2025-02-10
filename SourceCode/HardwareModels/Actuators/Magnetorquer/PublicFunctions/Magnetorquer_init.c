/*!
 *    @File:         Magnetorquer_init.c
 *
 *    @Brief:        C file which contains init function to load parameters
 *                   to initialize Magnetorquer.
 *
 *    @Date:         10/02/2025
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_ParamsStruct.h"
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int Magnetorquer_init(const char          *p_magnetorquerParamFilename_in,
                      Magnetorquer_Params *p_magnetorquerParams_out,
                      Magnetorquer_State  *p_magnetorquerState_out,
                      const char          *p_actuatorBody_in)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;
  double        actuatorFov_deg;

  /* Clear variables */
  GZero(&GParser_state, GParser_State);
  GZero(p_magnetorquerParams_out, Magnetorquer_Params);
  GZero(p_magnetorquerState_out, Magnetorquer_State);
  p_dic = NULL;

  /* Load parameters */
  p_dic = GParser_loadParams(&GParser_state, p_magnetorquerParamFilename_in);

  /* Check that the parameters from the actuator have been loaded */
  if (p_dic == NULL)
  {
    GError("Failed to load parameters for Magnetorquer: %s",
           p_magnetorquerParamFilename_in);
  }

  /* ------------------------------------------------------------------------ *
   * Load Parameters of Actuator
   * ------------------------------------------------------------------------ */

  /* load name of actuator */
  GParser_loadString(&GParser_state,
                     p_dic,
                     &(p_magnetorquerParams_out->magnetorquerName[0]),
                     "Actuator:actuatorName");

  /* Load position of actuator relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_magnetorquerParams_out->coilArea_Sen_m2[0]),
                          "ActuatorCharecteristics:coilArea_Sen_m2",
                          3,
                          1);

  /* Load position of actuator relative to COG */
  GParser_loadDoubleArray(&GParser_state,
                          p_dic,
                          &(p_magnetorquerParams_out->coilTurns_Sen[0]),
                          "ActuatorCharecteristics:coilTurns_Sen",
                          3,
                          1);

  /* Load position of actuator relative to COG */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_magnetorquerParams_out->actuatorPosition_Bod_m[0]),
      "ActuatorOrientation:actuatorPosition_Bod_m",
      3,
      1);

  /* Load position of actuator relative to COG */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_magnetorquerParams_out->actuatorQuaternion_BodToSen[0]),
      "ActuatorOrientation:actuatorQuaternion_BodToSen",
      4,
      1);

  /* Load noise mean value of actuator */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_magnetorquerParams_out->systemNoiseMean_Sen_Nm[0]),
      "ActuatorNoise:systemNoiseMean_Sen_Nm",
      3,
      1);

  /* Load noise standard deviation value of actuator */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_magnetorquerParams_out->systemNoiseStandardDeviation_Sen_Nm[0]),
      "ActuatorNoise:systemNoiseStandardDeviation_Sen_Nm",
      3,
      1);

  /* Load noise amplitude value of actuator */
  GParser_loadDoubleArray(
      &GParser_state,
      p_dic,
      &(p_magnetorquerParams_out->systemNoiseAmplitude_Sen_Nm[0]),
      "ActuatorNoise:systemNoiseAmplitude_Sen_Nm",
      3,
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