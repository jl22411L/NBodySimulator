/*!
 *    @File:         Magnetometer_step.c
 *
 *    @Brief:        Function which will step a magnetometer sensor.
 *
 *    @Date:         01/02/2025
 *
 */

#include <math.h>
#include <stdint.h>

/* Function Includes */
#include "CelestialBody/PublicFunctions/CelestialBody_PublicFunctions.h"
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"
#include "SensorFilters/PublicFunctions/SensorFilter_PublicFunctions.h"
#include "Sensors/Magnetometer/PrivateFunctions/Magnetometer_PrivateFunctions.h"

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"
#include "Sensors/Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Sensors/Magnetometer/DataStructs/Magnetometer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GRand/GRand.h"
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
  double  jamSailPositionRelToInertCen_Fix_m[3];
  double  jamSailPosition_InertCen_m[3];
  double  sensorPositionRelToBody_InertCen_m[3];
  double  sensorPosition_InertCen_m[3];
  double  sensorPosition_GeoCen_m[3];
  double  sensorPositionSpherical_GeoCen_m[3];
  double  quaternion_BodToFix[4];
  double  quaternion_BodToInertCen[4];
  double  quaternion_InertCenToGeoCen[4];
  double  quaternion_GeoCenToNed[4];
  double  quaternion_InertCenToSen[4];
  double  quaternion_InertCenToBod[4];
  double  euler123_GeoCenToNed[3];
  double  magneticFieldVector_Ned_nT[3];
  double  magneticFieldVector_GeoCen_nT[3];
  double  magneticFieldVector_InertCen_nT[3];
  uint8_t i;

  /* Clear Variables */
  GZero(&(jamSailPositionRelToInertCen_Fix_m[0]), double[3]);
  GZero(&(jamSailPosition_InertCen_m[0]), double[3]);
  GZero(&(sensorPositionRelToBody_InertCen_m[0]), double[3]);
  GZero(&(sensorPosition_InertCen_m[0]), double[3]);
  GZero(&(sensorPosition_GeoCen_m[0]), double[3]);
  GZero(&(sensorPositionSpherical_GeoCen_m[0]), double[3]);
  GZero(&(quaternion_BodToFix[0]), double[4]);
  GZero(&(quaternion_BodToInertCen[0]), double[4]);
  GZero(&(quaternion_InertCenToGeoCen[0]), double[4]);
  GZero(&(quaternion_GeoCenToNed[0]), double[4]);
  GZero(&(quaternion_InertCenToSen[0]), double[4]);
  GZero(&(quaternion_InertCenToBod[0]), double[4]);
  GZero(&(euler123_GeoCenToNed[0]), double[3]);
  GZero(&(magneticFieldVector_Ned_nT[0]), double[3]);
  GZero(&(magneticFieldVector_GeoCen_nT[0]), double[3]);
  GZero(&(magneticFieldVector_InertCen_nT[0]), double[3]);

  /* Find the position of JamSail relative to the Inertical Centric Frame */
  GMath_vectorSub(
      p_bodyPosition_Fix_m_in,
      &(p_magneticFieldCelestialBody_in->rigidBody_state.position_Fix_m[0]),
      &(jamSailPositionRelToInertCen_Fix_m[0]));

  /* Find the position of JamSail in the Inertial Centric frame */
  GMath_quaternionFrameRotation(
      &(jamSailPosition_InertCen_m[0]),
      &(jamSailPositionRelToInertCen_Fix_m[0]),
      &(p_magneticFieldCelestialBody_in->quaternion_FixToInertCen[0]));

  /* Find quaternion from body to fix frame */
  GMath_quaternionConjugate(&(quaternion_BodToFix[0]),
                            p_quaternionToBody_FixToBod_in);

  /* Find quaternion from body to Inertial Centric frame */
  GMath_quaternionMul(
      &(quaternion_BodToInertCen[0]),
      &(p_magneticFieldCelestialBody_in->quaternion_FixToInertCen[0]),
      &(quaternion_BodToFix[0]));

  /* Find the position of the sensor in the Inertical Centric frame */
  GMath_quaternionFrameRotation(
      &(sensorPositionRelToBody_InertCen_m[0]),
      &(p_magnetometer_params_in->sensorPosition_Bod_m[0]),
      &(quaternion_BodToInertCen[0]));

  /* Find the position of the sensor in the Inertical Centric Frame */
  GMath_vectorAdd(&(sensorPositionRelToBody_InertCen_m[0]),
                  &(jamSailPosition_InertCen_m[0]),
                  &(sensorPosition_InertCen_m[0]));

  /* Find quaternion which rotates the Inertial Centric to Geo Centric frame */
  quaternion_InertCenToGeoCen[0] = 0.0;
  quaternion_InertCenToGeoCen[1] = 0.0;
  quaternion_InertCenToGeoCen[2] =
      sin((GCONST_PI / (p_magneticFieldCelestialBody_in->sideRealTime_s)) *
          (simTime_s_in - GCONST_J2000_UNIX_TIME_S));
  quaternion_InertCenToGeoCen[3] =
      cos((GCONST_PI / (p_magneticFieldCelestialBody_in->sideRealTime_s)) *
          (simTime_s_in - GCONST_J2000_UNIX_TIME_S));

  /* Stabalize quaternion */
  GMath_findUnitQuaternion(&(quaternion_InertCenToGeoCen[0]),
                           &(quaternion_InertCenToGeoCen[0]));

  /* Find the position of the sensor in the Geo Centric frame */
  GMath_quaternionFrameRotation(&(sensorPosition_GeoCen_m[0]),
                                &(sensorPosition_InertCen_m[0]),
                                &(quaternion_InertCenToGeoCen[0]));

  /* Convert position of the sensor from cartesian to spherical coordinates */
  GMath_cartesianToSpherical(&(sensorPositionSpherical_GeoCen_m[0]),
                             &(sensorPosition_GeoCen_m[0]));

  // TODO: THe simulated rotation angle does not match up with the
  // theoretical.
  //       This may be due to dirft of the numerical integration. To get
  //       around this, some runge-kutta integration method may need to be
  //       applied.
  //
  // TODO: the inert cen frame is defined at j2000. This function does not
  // seem
  //       to take that into consideration. Check!!
  //
  //   /* Check the rotation angle of the earth matches up */
  //   CelestialBody_checkRotationAngle(
  //       &(quaternion_InertCenToGeoCen[0]),
  //       p_magneticFieldCelestialBody_in->sideRealTime_s,
  //       simTime_s_in);

  /* Find magnetic field from IGRF */
  Igrf_step(p_igrf_params_in,
            &(sensorPositionSpherical_GeoCen_m[0]),
            p_magneticFieldCelestialBody_in->equitorialRadius_m,
            simTime_s_in,
            &(magneticFieldVector_Ned_nT[0]));

  /* Create Euler Vector from GeoCen frame to NED frame */
  euler123_GeoCenToNed[0] = 0.0;
  euler123_GeoCenToNed[1] = sensorPositionSpherical_GeoCen_m[1];
  euler123_GeoCenToNed[2] = sensorPositionSpherical_GeoCen_m[2] + GCONST_PI / 2;

  /* Find quaternion rotation from GeoCen frame to NED frame */
  GMath_eul2Quat(&(euler123_GeoCenToNed[0]), &(quaternion_GeoCenToNed[0]));

  /* Convert magnetic field into GeoCen frame */
  GMath_quaternionPointRotation(&(magneticFieldVector_GeoCen_nT[0]),
                                &(magneticFieldVector_Ned_nT[0]),
                                &(quaternion_GeoCenToNed[0]));

  /* Convert the magnetic field to the Inertical Centric frame */
  GMath_quaternionPointRotation(&(magneticFieldVector_InertCen_nT[0]),
                                &(magneticFieldVector_GeoCen_nT[0]),
                                &(quaternion_InertCenToGeoCen[0]));

  /* Find quaternion from inertial centric frame to body frame */
  GMath_quaternionConjugate(&(quaternion_InertCenToBod[0]),
                            &(quaternion_BodToInertCen[0]));

  /* Find quaternion from inertial centric frame to sensor frame */
  GMath_quaternionMul(&(quaternion_InertCenToSen[0]),
                      &(p_magnetometer_params_in->sensorQuaternion_BodToSen[0]),
                      &(quaternion_InertCenToBod[0]));

  /* Convert magnetic field from inertial centric frame to sensor frame */
  GMath_quaternionFrameRotation(
      &(p_magnetometer_state_out->trueMagneticFieldMeasurement_Sen_nT[0]),
      &(magneticFieldVector_InertCen_nT[0]),
      &(quaternion_InertCenToSen[0]));

  /* Find noise due to external magnetic field */
  // TODO

  /* Find noise component of sensor measurement in body frame */
  for (i = 0; i < 3; i++)
  {
    p_magnetometer_state_out->sensorMagneticFieldNoise_Sen_nT[i] =
        (p_magnetometer_params_in->noiseAmplitude_Sen_nT[i]) *
        GRand_gaussianDistribution(
            p_magnetometer_params_in->noiseMean_Sen_nT[i],
            p_magnetometer_params_in->noiseStandardDeviation_Sen_nT[i]);
  }

  /* Find measured component of magnetic field vector in body frame */
  for (i = 0; i < 3; i++)
  {
    p_magnetometer_state_out->measuredMagneticField_Sen_nT[i] =
        p_magnetometer_state_out->trueMagneticFieldMeasurement_Sen_nT[i] +
        p_magnetometer_state_out->externalMagneticFieldNoise_Sen_nT[i] +
        p_magnetometer_state_out->sensorMagneticFieldNoise_Sen_nT[i];
  }

  /* Move old sensor reading to previous reading (Used in low pass filter ) */
  for (i = 0; i < 3; i++)
  {
    p_magnetometer_state_out->previousFilteredMagneticField_Sen_nT[i] =
        p_magnetometer_state_out->filteredMagneticField_Sen_nT[i];
  }

  /* Archive data */
  Magnetometer_archiveData(p_magnetometer_state_out);

  return GCONST_TRUE;
}