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
                      double              *p_bodyPosition_Fix_m_in,
                      double              *p_quaternionToBody_FixToBod_in,
                      double               simTime_s_in)
{
  /* Declare local variables */
  double sensorPositionRelBody_Fix_m[3];
  double bodyPositionRelInertialCentric_Fix_m[3];
  double sensorPointRelInerticalCentric_Fix_m[3];
  double sensorPoint_InertCen_m[3];
  double quaternion_FixToSen[4];
  double sphericalPosition_InertCen_m[3];
  double magneticFieldVector_Ned_nT[3];
  double euler_GeoCenToNed_123[3];
  double quaternion_GeoCenToNed[4];
  double magneticFieldVector_GeoCen_nT[3];
  double magneticFieldVector_Fix_nT[3];

  /* Clear Variables */
  GZero(&(sensorPositionRelBody_Fix_m[0]), double[3]);
  GZero(&(bodyPositionRelInertialCentric_Fix_m[0]), double[3]);
  GZero(&(sensorPointRelInerticalCentric_Fix_m[0]), double[3]);
  GZero(&(sensorPoint_InertCen_m[0]), double[3]);
  GZero(&(quaternion_FixToSen[0]), double[4]);
  GZero(&(sphericalPosition_InertCen_m[0]), double[3]);
  GZero(&(magneticFieldVector_Ned_nT[0]), double[3]);
  GZero(&(euler_GeoCenToNed_123[0]), double[3]);
  GZero(&(quaternion_GeoCenToNed[0]), double[4]);
  GZero(&(magneticFieldVector_GeoCen_nT[0]), double[3]);
  GZero(&(magneticFieldVector_Fix_nT[0]), double[3]);

  /*!
   * Find position of sensor relative to body in fix frame. This is done by
   * rotating the sensor position vector actively into the position it would
   * be in, when in the fix frame.
   */
  GMath_quaternionPointRotation(
      &(sensorPositionRelBody_Fix_m[0]),
      &(p_magnetometer_params_in->sensorPosition_Bod_m[0]),
      p_quaternionToBody_FixToBod_in);

  /*!
   * Find position of body relative to Inertial Centric frame in the fix frame.
   */
  GMath_vectorSub(
      p_bodyPosition_Fix_m_in,
      &(p_magneticFieldCelestialBody_in->rigidBody_state.position_Fix_m[0]),
      &(bodyPositionRelInertialCentric_Fix_m[0]));

  /*!
   * Find position of point relative to the Inertial Centric frame in the fix
   * frame.
   */
  GMath_vectorAdd(&(bodyPositionRelInertialCentric_Fix_m[0]),
                  &(p_magnetometer_params_in->sensorPosition_Bod_m[0]),
                  &(bodyPositionRelInertialCentric_Fix_m[0]));

  /* Find quaternion which represents from fix to sesor frame */
  GMath_quaternionMul(&(quaternion_FixToSen[0]),
                      &(p_magnetometer_params_in->sensorQuaternion_BodToSen[0]),
                      p_quaternionToBody_FixToBod_in);

  /* Find the position of point in Inertical Centric frame */
  GMath_quaternionFrameRotation(&(sensorPoint_InertCen_m[0]),
                                &(bodyPositionRelInertialCentric_Fix_m[0]),
                                &(quaternion_FixToSen[0]));

  /* Find the sensor position in spherical coordinates */
  GMath_cartesianToSpherical(&(sphericalPosition_InertCen_m[0]),
                             &(sensorPoint_InertCen_m[0]));

  /* Find magnetic field from IGRF */
  Igrf_step(p_igrf_params_in,
            &(sphericalPosition_InertCen_m[0]),
            p_magneticFieldCelestialBody_in->equitorialRadius_m,
            simTime_s_in,
            &(magneticFieldVector_Ned_nT[0]));

  /* Create Euler Vector from GeoCen frame to NED frame */
  euler_GeoCenToNed_123[0] = 0.0;
  euler_GeoCenToNed_123[1] = sphericalPosition_InertCen_m[1];
  euler_GeoCenToNed_123[2] = sphericalPosition_InertCen_m[2] + GCONST_PI / 2;

  /* Find quaternion rotation from GeoCen frame to NED frame */
  GMath_eul2Quat(&(euler_GeoCenToNed_123[0]), &(quaternion_GeoCenToNed[0]));

  /* Convert magnetic field into GeoCen frame */
  GMath_quaternionFrameRotation(&(magneticFieldVector_GeoCen_nT[0]),
                                &(magneticFieldVector_Ned_nT[0]),
                                &(quaternion_GeoCenToNed[0]));

  /* Convert the magnetic field into the fix frame */
  GMath_quaternionPointRotation(
      &(magneticFieldVector_Fix_nT[0]),
      &(magneticFieldVector_GeoCen_nT[0]),
      &(p_magneticFieldCelestialBody_in->rigidBody_state
            .quaternion_FixToBody[0]));

  /* Find the magnetic field vector in the sensor frame */
  GMath_quaternionFrameRotation(
      &(p_magnetometer_state_out->trueMagneticFieldMeasurement_Sen_nT[0]),
      &(magneticFieldVector_Fix_nT[0]),
      &(quaternion_FixToSen[0]));

  /* Find noise component of sensor measurement in body frame */
  // TODO

  /* Find measured component of magnetic field vector in body frame */
  // TODO

  return GCONST_TRUE;
}