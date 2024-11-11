/*
 *    @File:         SunSensor_step.c
 *
 *    @Brief:        File which contains the function declaration for stepping
 *                   Sun Sensor.
 *
 *    @Date:         11/11/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "SunSensor/DataStructs/SunSensor_Params.h"
#include "SunSensor/DataStructs/SunSensor_State.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int SunSensor_step(double           *p_sunPosition_Fix_m_in,
                   double           *p_bodyPosition_Fix_m_in,
                   double           *p_quaternion_FixToBod_in,
                   SunSensor_Params *p_sunSensor_params_in,
                   SunSensor_State  *p_sunSensor_state_out)
{
  /* Declare local variables */
  double sunVector_Bod_m[3];
  double sunVectorRelToSensor_Bod_m[3];

  /* Clear Buffers */
  GZero(&sunVector_Bod_m[0], double[3]);
  GZero(&sunVectorRelToSensor_Bod_m[0], double[3]);

  /* Find the true position of the sun in the body frame */
  GMath_vectorSub(p_sunPosition_Fix_m_in,
                  p_bodyPosition_Fix_m_in,
                  &sunVector_Bod_m[0]);

  /* Find the true measurent in the body frame relative to the sensor frame */
  GMath_vectorSub(&(sunVector_Bod_m[0]),
                  &(p_sunSensor_params_in->sensorPosition_Bod_m[0]),
                  &(sunVectorRelToSensor_Bod_m[0]));

  /* Find the true value in the sensor frame */
  GMath_quaternionPointRotation(
      &(p_sunSensor_state_out->trueSunVector_Sensor_m[0]),
      &(sunVectorRelToSensor_Bod_m[0]),
      &(p_sunSensor_params_in->sensorQuaternion_Bod[0]));

  /* Find noise component of the measurement */
  // TODO

  /* Find the output measured reading of the sun vector */
  p_sunSensor_state_out->measuredSunVector_Sensor_m[0] =
      p_sunSensor_state_out->trueSunVector_Sensor_m[0] +
      p_sunSensor_state_out->noiseVector_Sensor_m[0];

  p_sunSensor_state_out->measuredSunVector_Sensor_m[1] =
      p_sunSensor_state_out->trueSunVector_Sensor_m[1] +
      p_sunSensor_state_out->noiseVector_Sensor_m[1];

  p_sunSensor_state_out->measuredSunVector_Sensor_m[2] =
      p_sunSensor_state_out->trueSunVector_Sensor_m[2] +
      p_sunSensor_state_out->noiseVector_Sensor_m[2];

  /* Write archive */
  // TODO

  return GCONST_TRUE;
}