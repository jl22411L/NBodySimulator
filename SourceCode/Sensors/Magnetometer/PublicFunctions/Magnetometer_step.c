/*!
 *    @File:         Magnetometer_step.c
 *
 *    @Brief:        Function which will step a magnetometer sensor.
 *
 *    @Date:         01/02/2025
 *
 */

/* Function Includes */
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"
#include "Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Magnetometer/DataStructs/Magnetometer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int Magnetometer_step(Magnetometer_Params *p_magnetometer_params_in,
                      Magnetometer_State  *p_magnetometer_state_out,
                      Igrf_Params         *p_igrf_params_in,
                      CelestialBody_State *p_magneticFieldCelestialBody_in,
                      double              *p_bodyPosition_fix_m_in,
                      double              *p_quaternionToBody_FixToBod_in,
                      double               simTime_s_in)
{
  /* Declare local variables */
  double sensorPositionRelBody_Fix_m[3];

  /* Clear Variables */
  GZero(&(sensorPositionRelBody_Fix_m[0]), double[3]);

  /* Find position of sensor relative to body in fix frame */
  GMath_quaternionFrameRotation(
      &(sensorPositionRelBody_Fix_m[0]),
      &(p_magnetometer_params_in->sensorPosition_Bod_m[0]),
      p_quaternionToBody_FixToBod_in);

  /* Find the magnetic field in the geocentric frame */
  // TODO

  /* Convert magnetic field vector from geocentric frame to body frame */

  /* Find noise component of sensor measurement in body frame */
  // TODO

  /* Find measured component of magnetic field vector in body frame */
  // TODO

  return GCONST_TRUE;
}