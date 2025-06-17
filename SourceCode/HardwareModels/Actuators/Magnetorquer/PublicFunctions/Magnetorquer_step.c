/*!
 *    @File:         Magnetorquer_step.c
 *
 *    @Brief:        File containing declaration of function which will step the
 *                   magnetorquer.
 *
 *    @Date:         10/02/2025
 *
 */

#include <stdint.h>

/* Function Includes */
#include "Actuators/Magnetorquer/PrivateFunctions/Magnetorquer_PrivateFunctions.h"

/* Structure Include */
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_ParamsStruct.h"
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GRand/GRand.h"
#include "GZero/GZero.h"

int Magnetorquer_step(Magnetorquer_State  *p_magnetorquer_state_out,
                      Magnetorquer_Params *p_magnetorquer_params_in,
                      Igrf_Params         *p_igrf_params_in,
                      CelestialBody_State *p_magneticFieldCelestialBody_in,
                      double              *p_bodyPosition_Fix_m_in,
                      double              *p_quaternionToBody_FixToBod_in,
                      double               simTime_s_in)
{
  /* Declare local variables */
  double  actuatorPositionRelBody_Fix_m[3];
  double  bodyPositionRelInertialCentric_Fix_m[3];
  double  actuatorPointRelInerticalCentric_Fix_m[3];
  double  actuatorPoint_GeoCen_m[3];
  double  quaternion_FixToSen[4];
  double  quaternion_InertCenToFix[4];
  double  sphericalPosition_GeoCen_m[3];
  double  magneticFieldVector_Ned_nT[3];
  double  euler_GeoCenToNed_123[3];
  double  quaternion_GeoCenToNed[4];
  double  magneticFieldVector_GeoCen_nT[3];
  double  magneticFieldVector_Fix_nT[3];
  uint8_t i;

  /* Clear Variables */
  GZero(&(actuatorPositionRelBody_Fix_m[0]), double[3]);
  GZero(&(bodyPositionRelInertialCentric_Fix_m[0]), double[3]);
  GZero(&(actuatorPointRelInerticalCentric_Fix_m[0]), double[3]);
  GZero(&(actuatorPoint_GeoCen_m[0]), double[3]);
  GZero(&(quaternion_FixToSen[0]), double[4]);
  GZero(&(quaternion_InertCenToFix[0]), double[4]);
  GZero(&(sphericalPosition_GeoCen_m[0]), double[3]);
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
      &(actuatorPositionRelBody_Fix_m[0]),
      &(p_magnetorquer_params_in->actuatorPosition_Bod_m[0]),
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
                  &(actuatorPositionRelBody_Fix_m[0]),
                  &(bodyPositionRelInertialCentric_Fix_m[0]));

  /* Find the quaternion representing rotation from InertCen to GeoCen frame */
  GMath_quaternionConjugate(
      &(quaternion_InertCenToFix[0]),
      &(p_magneticFieldCelestialBody_in->quaternion_FixToInertCen[0]));

  /* Find the position of point in Geo-Centric frame */
  GMath_quaternionFrameRotation(
      &(actuatorPoint_GeoCen_m[0]),
      &(bodyPositionRelInertialCentric_Fix_m[0]),
      &(p_magneticFieldCelestialBody_in->rigidBody_state
            .quaternion_FixToBody[0]));

  /* Find the sensor position in spherical coordinates */
  GMath_cartesianToSpherical(&(sphericalPosition_GeoCen_m[0]),
                             &(actuatorPoint_GeoCen_m[0]));

  /* Find magnetic field from IGRF */
  Igrf_step(p_igrf_params_in,
            &(sphericalPosition_GeoCen_m[0]),
            p_magneticFieldCelestialBody_in->equitorialRadius_m,
            simTime_s_in,
            &(magneticFieldVector_Ned_nT[0]));

  /* Create Euler Vector from GeoCen frame to NED frame */
  euler_GeoCenToNed_123[0] = 0.0;
  euler_GeoCenToNed_123[1] = sphericalPosition_GeoCen_m[1];
  euler_GeoCenToNed_123[2] = sphericalPosition_GeoCen_m[2] + GCONST_PI / 2;

  /* Find quaternion rotation from GeoCen frame to NED frame */
  GMath_eul2Quat(&(euler_GeoCenToNed_123[0]), &(quaternion_GeoCenToNed[0]));

  /* Convert magnetic field into GeoCen frame */
  GMath_quaternionPointRotation(&(magneticFieldVector_GeoCen_nT[0]),
                                &(magneticFieldVector_Ned_nT[0]),
                                &(quaternion_GeoCenToNed[0]));

  /* Convert the magnetic field into the fix frame */
  GMath_quaternionPointRotation(
      &(magneticFieldVector_Fix_nT[0]),
      &(magneticFieldVector_GeoCen_nT[0]),
      &(p_magneticFieldCelestialBody_in->rigidBody_state
            .quaternion_FixToBody[0]));

  /* Find quaternion which represents from fix to sensor frame */
  GMath_quaternionMul(
      &(quaternion_FixToSen[0]),
      p_quaternionToBody_FixToBod_in,
      &(p_magnetorquer_params_in->actuatorQuaternion_BodToSen[0]));

  /* Find the magnetic field vector on the actuator in the sensor frame */
  GMath_quaternionFrameRotation(
      &(p_magnetorquer_state_out->externalMagneticField_Sen_nT[0]),
      &(magneticFieldVector_Fix_nT[0]),
      &(quaternion_FixToSen[0]));

  /* Add the noise of the external magnetic field */
  for (i = 0; i < 3; i++)
  {
    p_magnetorquer_state_out->externalMagneticField_Sen_nT[i] +=
        p_magnetorquer_state_out->externalMagneticFieldNoise_Sen_nT[i];
  }

  /* Find the dipole moment in the sensor frame */
  for (i = 0; i < 3; i++)
  {
    p_magnetorquer_state_out->dipoleMoment_Sen_GAm2[i] =
        (p_magnetorquer_state_out->inputCurrent_Sen_A[i]) *
        (p_magnetorquer_params_in->coilTurns_Sen[i]) *
        (p_magnetorquer_params_in->coilArea_Sen_m2[i]) * GCONST_NM_TOLERANCE;
  }

  /* Find the true magnetic torque of the actuator */
  GMath_crossProduct(
      &(p_magnetorquer_state_out->dipoleMoment_Sen_GAm2[0]),
      &(p_magnetorquer_state_out->externalMagneticField_Sen_nT[0]),
      &(p_magnetorquer_state_out->trueMagnetorquerTorque_Sen_Nm[0]));

  for (i = 0; i < 3; i++)
  {
    /*!
     * Find the system noise of the actuator. If current is below threshold, set
     * the system noise to zero. Otherwise, apply a gaussian noise.
     */
    if ((p_magnetorquer_state_out->inputCurrent_Sen_A[i]) <
        MAGNETORQUER_MIN_CURRENT_THRESHOLD_A)
    {
      p_magnetorquer_state_out->systemNoiseTorque_Sen_Nm[i] = 0.0;
    }
    else
    {
      p_magnetorquer_state_out->systemNoiseTorque_Sen_Nm[i] =
          (p_magnetorquer_params_in->systemNoiseAmplitude_Sen_Nm[i]) *
          GRand_gaussianDistribution(
              (p_magnetorquer_params_in->systemNoiseMean_Sen_Nm[i]),
              (p_magnetorquer_params_in
                   ->systemNoiseStandardDeviation_Sen_Nm[i]));
    }

    /* Find the total torque of the system in the sensor frame */
    p_magnetorquer_state_out->totalTorque_Sen_Nm[i] =
        p_magnetorquer_state_out->trueMagnetorquerTorque_Sen_Nm[i] +
        p_magnetorquer_state_out->systemNoiseTorque_Sen_Nm[i];
  }

  /* Find the total torque in the body frame frame */
  GMath_quaternionPointRotation(
      &(p_magnetorquer_state_out->totalTorque_Bod_Nm[0]),
      &(p_magnetorquer_state_out->totalTorque_Sen_Nm[0]),
      &(p_magnetorquer_params_in->actuatorQuaternion_BodToSen[0]));

  /* Find the total torque in the fix frame */
  GMath_quaternionPointRotation(
      &(p_magnetorquer_state_out->totalTorque_Fix_Nm[0]),
      &(p_magnetorquer_state_out->totalTorque_Bod_Nm[0]),
      p_quaternionToBody_FixToBod_in);

  /* Archive data */
  Magnetorquer_archiveData(p_magnetorquer_state_out);

  return GCONST_TRUE;
}