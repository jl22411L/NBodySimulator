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
#include "SunSensor/PrivateFunctions/SunSensor_PrivateFunctions.h"

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "SunSensor/DataStructs/SunSensor_ParamsStruct.h"
#include "SunSensor/DataStructs/SunSensor_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int SunSensor_step(double              *p_bodyPosition_Fix_m_in,
                   double              *p_quaternion_FixToBod_in,
                   CelestialBody_State *p_sunCelestialBody_in,
                   BodyMgr_State       *p_bodyMgr_state_in,
                   SunSensor_Params    *p_sunSensor_params_in,
                   SunSensor_State     *p_sunSensor_state_out)
{
  /* Declare local variables */
  double sunPositionRelToBody_Fix_m[3];
  double sunPosition_Bod_m[3];
  double sunPositionRelToSen_Bod_m[3];
  double sunPosition_Sen_m[3];

  /* Clear Buffers */
  GZero(&(sunPositionRelToBody_Fix_m[0]), double[3]);
  GZero(&(sunPosition_Bod_m[0]), double[3]);
  GZero(&(sunPositionRelToSen_Bod_m[0]), double[3]);
  GZero(&(sunPosition_Sen_m[0]), double[3]);

  /* ------------------------------------------------------------------------ *
   * Sun Component of Sun Sensor
   * ------------------------------------------------------------------------ */

  /* Find true position of sun in fixed frame relative to the body frame */
  GMath_vectorSub(&(p_sunCelestialBody_in->rigidBody_state.position_m_Fix[0]),
                  p_bodyPosition_Fix_m_in,
                  &(sunPositionRelToBody_Fix_m[0]));

  /* Find true position of sun in body frame */
  GMath_quaternionPointRotation(&(sunPosition_Bod_m[0]),
                                &(sunPositionRelToBody_Fix_m[0]),
                                &(sunPosition_Bod_m[0]));

  /* Find true position of sun in sensor frame relative to body frame */
  GMath_vectorSub(&(sunPosition_Bod_m[0]),
                  &(p_sunSensor_params_in->sensorPosition_Bod_m[0]),
                  &(sunPositionRelToSen_Bod_m[0]));

  /* Find true position of sun in sensor frame */
  GMath_quaternionPointRotation(
      &(sunPosition_Sen_m[0]),
      &(sunPositionRelToSen_Bod_m[0]),
      &(p_sunSensor_params_in->sensorQuaternion_Bod[0]));

  /* Find the direction of the sun as a unit vector */
  GMath_vectorNorm(&(p_sunSensor_state_out->trueSunVector_Sensor_m[0]),
                   &(sunPosition_Sen_m[0]),
                   3);

  /* ------------------------------------------------------------------------ *
   * Check reading on sun sensor is valid
   * ------------------------------------------------------------------------ */

  /* Set blocked flag to false and let checks change if this is not the case */
  p_sunSensor_state_out->isSensorReadingInvalid = GCONST_FALSE;

  /* Find if the vector is blocked by a celestial body */
  SunSensor_checkForBlocking(
      &(p_sunCelestialBody_in->rigidBody_state.position_m_Fix[0]),
      p_bodyPosition_Fix_m_in,
      (p_bodyMgr_state_in->p_celestialBodyList),
      p_bodyMgr_state_in->nCelestialBodies,
      &(p_sunSensor_state_out->isSensorReadingInvalid));

  /* Check that sun vector is within fov of sun sensor */
  SunSensor_checkWithinFov(p_sunSensor_state_out, p_sunSensor_params_in);

  /* ------------------------------------------------------------------------ *
   * Find Noise
   * ------------------------------------------------------------------------ */

  /* Find albedo effects from celestial bodies */
  // TODO

  /* Find noise component of the measurement */
  // TODO

  /* ------------------------------------------------------------------------ *
   * Determine Measured Result of Sensor
   * ------------------------------------------------------------------------ */

  /* Find the output measured reading of the sun vector */
  if (p_sunSensor_state_out->isSensorReadingInvalid == GCONST_TRUE)
  {
    /* If sun is blocked only include the noise components in measurement */
    p_sunSensor_state_out->measuredSunVector_Sensor_m[0] =
        p_sunSensor_state_out->noiseVector_Sensor_m[0] +
        p_sunSensor_state_out->albedoComponentNoise_Sensor_m[0];

    p_sunSensor_state_out->measuredSunVector_Sensor_m[1] =
        p_sunSensor_state_out->noiseVector_Sensor_m[1] +
        p_sunSensor_state_out->albedoComponentNoise_Sensor_m[1];

    p_sunSensor_state_out->measuredSunVector_Sensor_m[2] =
        p_sunSensor_state_out->noiseVector_Sensor_m[2] +
        p_sunSensor_state_out->albedoComponentNoise_Sensor_m[2];
  }
  else
  {
    /* Else, include the true sun sensor vecor */
    p_sunSensor_state_out->measuredSunVector_Sensor_m[0] =
        p_sunSensor_state_out->trueSunVector_Sensor_m[0] +
        p_sunSensor_state_out->noiseVector_Sensor_m[0] +
        p_sunSensor_state_out->albedoComponentNoise_Sensor_m[0];

    p_sunSensor_state_out->measuredSunVector_Sensor_m[1] =
        p_sunSensor_state_out->trueSunVector_Sensor_m[1] +
        p_sunSensor_state_out->noiseVector_Sensor_m[1] +
        p_sunSensor_state_out->albedoComponentNoise_Sensor_m[1];

    p_sunSensor_state_out->measuredSunVector_Sensor_m[2] =
        p_sunSensor_state_out->trueSunVector_Sensor_m[2] +
        p_sunSensor_state_out->noiseVector_Sensor_m[2] +
        p_sunSensor_state_out->albedoComponentNoise_Sensor_m[2];
  }

  /* Write archive */
  SunSensor_archiveData(p_sunSensor_state_out);

  return GCONST_TRUE;
}