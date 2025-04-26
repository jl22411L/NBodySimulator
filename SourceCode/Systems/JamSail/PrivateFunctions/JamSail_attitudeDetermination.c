/*!
 *    @File:         JamSail_attitudeDetermination.c
 *
 *    @Brief:        Function which runs JamSail's determination algorithm
 *
 *    @Date:         05/03/2025
 *
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

/* Function Includes */
#include "Guidance/KeplarianPropogation/PublicFunctions/KeplarianPropogation_PublicFunctions.h"
#include "Guidance/TriadAlgorithm/PublicFunctions/TriadAlgorithm_PublicFunctions.h"
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_AdcsStateEnum.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GUtilities/GUtilities.h"
#include "GZero/GZero.h"

int JamSail_attitudeDetermination(JamSail_State  *p_jamSail_state_inout,
                                  JamSail_Params *p_jamSail_params_in,
                                  double          simTime_s_in,
                                  double          timeStep_s_in)
{
  /* Declare local variables */
  double  jamSailPositionCartesian_GeoCen_m[3];
  double  jamSailPositionSpherical_GeoCen_m[3];
  double  quaternion_InertCenToGeoCen[4];
  double  euler_GeoCenToNed_123[3];
  double  magneticFieldVector_Ned_nT[3];
  double  magneticFieldVector_GeoCen_nT[3];
  double  magneticFieldVector_Bod_nT[3];
  double  quaternion_GeoCenToNed[4];
  double  earthPosition_Fix_m[3];
  double  earthPosition_InertCen_m[3];
  double  sunPosition_InertCen_m[3];
  double  sunSensorMeasured_Bod[3];
  uint8_t i;

  /* Clear variables */
  GZero(&(jamSailPositionSpherical_GeoCen_m[0]), double[3]);
  GZero(&(euler_GeoCenToNed_123[0]), double[3]);
  GZero(&(quaternion_GeoCenToNed[0]), double[4]);
  GZero(&(magneticFieldVector_Ned_nT[0]), double[3]);
  GZero(&(magneticFieldVector_GeoCen_nT[0]), double[3]);
  GZero(&(magneticFieldVector_Bod_nT[0]), double[3]);
  GZero(&(earthPosition_Fix_m[0]), double[3]);
  GZero(&(earthPosition_InertCen_m[0]), double[3]);
  GZero(&(sunPosition_InertCen_m[0]), double[3]);
  GZero(&(sunSensorMeasured_Bod[0]), double[3]);

  /* Find magnetic field in body frame */
  GMath_quaternionPointRotation(
      &(magneticFieldVector_Bod_nT[0]),
      &(p_jamSail_state_inout->magnetometer_state
            .filteredMagneticField_Sen_nT[0]),
      &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  /* Find quaternion from inertial centric frame to geocentric frame */
  quaternion_InertCenToGeoCen[0] = 0.0;
  quaternion_InertCenToGeoCen[1] = 0.0;
  quaternion_InertCenToGeoCen[2] =
      sin((p_jamSail_params_in->averageEarthRotationalSpeedMag_rads) *
          (simTime_s_in - GCONST_J2000_UNIX_TIME_S) / 2);
  quaternion_InertCenToGeoCen[3] =
      cos((p_jamSail_params_in->averageEarthRotationalSpeedMag_rads) *
          (simTime_s_in - GCONST_J2000_UNIX_TIME_S) / 2);

  /* Find sun sensor measuremetn in body frame */
  GMath_quaternionPointRotation(
      &(sunSensorMeasured_Bod[0]),
      &(p_jamSail_state_inout->sunSensor_state.measuredSunVector_Sen_m[0]),
      &(p_jamSail_params_in->sunSensor_params.sensorQuaternion_BodToSen[0]));

  /* Rotate position of JamSail into Geo-Centric frame */
  GMath_quaternionFrameRotation(
      &(jamSailPositionCartesian_GeoCen_m[0]),
      &(p_jamSail_state_inout->positionEstimate_InertCen_m[0]),
      &(quaternion_InertCenToGeoCen[0]));

  /* Find coordinates in spherical form */
  GMath_cartesianToSpherical(&(jamSailPositionSpherical_GeoCen_m[0]),
                             &(jamSailPositionCartesian_GeoCen_m[0]));

  /* Find Magnetic fielf from IGRF model in NED frame */
  Igrf_step(&(p_jamSail_params_in->igrfModel_params),
            &(jamSailPositionSpherical_GeoCen_m[0]),
            (p_jamSail_params_in->earthEqutorialRadius_m),
            simTime_s_in,
            &(magneticFieldVector_Ned_nT[0]));

  /* Create Euler Vector from GeoCen frame to NED frame */
  euler_GeoCenToNed_123[0] = 0.0;
  euler_GeoCenToNed_123[1] = jamSailPositionSpherical_GeoCen_m[1];
  euler_GeoCenToNed_123[2] =
      jamSailPositionSpherical_GeoCen_m[2] + GCONST_PI / 2;

  /* Find quaternion rotation from GeoCen frame to NED frame */
  GMath_eul2Quat(&(euler_GeoCenToNed_123[0]), &(quaternion_GeoCenToNed[0]));

  /* Convert magnetic field into GeoCen frame */
  GMath_quaternionPointRotation(&(magneticFieldVector_GeoCen_nT[0]),
                                &(magneticFieldVector_Ned_nT[0]),
                                &(quaternion_GeoCenToNed[0]));

  /* Rotate magnetic field from Geo-Centric to ECI frame */
  GMath_quaternionPointRotation(
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0]),
      &(magneticFieldVector_GeoCen_nT[0]),
      &(quaternion_InertCenToGeoCen[0]));

  //   /* Find unit vector of magnetic field */
  //   GMath_findUnitVector(
  //       &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0]),
  //       &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0]));

  /* Find an estimate of the magnetic field in the body frame */
  GMath_quaternionFrameRotation(
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_Bod[0]),
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0]),
      &(p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]));

  /* Find the position of the sun in the fixed frame */
  KeplarianPropogation_keplarianToCartesian(
      (p_jamSail_params_in->earthMass_kg),
      (p_jamSail_params_in->sunMass_kg),
      JAMSAIL_EARTH_SUN_SEMI_MAJOR_AXIS_M,
      JAMSAIL_EARTH_SUN_ECCENTRICITY,
      JAMSAIL_EARTH_SUN_INCLINATION,
      JAMSAIL_EARTH_SUN_ARGUMENT_OF_PERIGEE_RAD,
      JAMSAIL_EARTH_SUN_RAANS_RAD,
      JAMSAIL_EARTH_SUN_TIME_SINCE_PERIAPSIS_S,
      simTime_s_in,
      &(earthPosition_Fix_m[0]));

  /* Find the position of the sun in the Inertical Centric frame */
  GMath_quaternionFrameRotation(
      &(earthPosition_InertCen_m[0]),
      &(earthPosition_Fix_m[0]),
      &(p_jamSail_params_in->quaternion_FixToInertCen[0]));

  /* Find position of sun relative to JamSail in inertical centric fram */
  GMath_vectorAdd(&(earthPosition_InertCen_m[0]),
                  &(p_jamSail_state_inout->positionEstimate_InertCen_m[0]),
                  &(sunPosition_InertCen_m[0]));

  /* Find the negative of the sun position so that it is from JamSail to sun */
  for (i = 0; i < 3; i++)
  {
    sunPosition_InertCen_m[i] *= -1.0;
  }

  /* Store position of sun as a unit vector */
  GMath_findUnitVector(
      &(sunPosition_InertCen_m[0]),
      &(p_jamSail_state_inout->sunVectorEstimateNorm_InertCen[0]));

  /* Rotate the sun vector to body frame */
  GMath_quaternionFrameRotation(
      &(p_jamSail_state_inout->sunVectorEstimateNorm_Bod[0]),
      &(sunPosition_InertCen_m[0]),
      &p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]);

  /* Subtract the vector from the body frame to the sensor frame */
  GMath_vectorSub(
      &(p_jamSail_state_inout->sunVectorEstimateNorm_Bod[0]),
      &(p_jamSail_params_in->sunSensor_params.sensorPosition_Bod_m[0]),
      &(p_jamSail_state_inout->sunVectorEstimateNorm_Bod[0]));

  /* Find the norm of the sun vector */
  GMath_findUnitVector(&(p_jamSail_state_inout->sunVectorEstimateNorm_Bod[0]),
                       &(p_jamSail_state_inout->sunVectorEstimateNorm_Bod[0]));

  /* Is sun sensor reading is valid, measure attitude */
  if (p_jamSail_state_inout->sunSensor_state.isSensorReadingInvalid ==
      GCONST_FALSE)
  {
    /* Set measurement to true */
    p_jamSail_state_inout->attitudeMeasuredFlag = GCONST_TRUE;

    /* Record time of measurement */
    p_jamSail_state_inout->timeOfLastMeasurement_s = Utilities.simTime_s;
  }
  else
  {
    /* Set measuremetn flag to false */
    p_jamSail_state_inout->attitudeMeasuredFlag = GCONST_FALSE;

    /* Set time of sun tracking to 0 */
    p_jamSail_state_inout->trackingTimeOfSun_s = 0.0;
  }

  /* Measure JamSail's attitude */
  JamSail_attitudeEstimation(p_jamSail_state_inout,
                             p_jamSail_params_in,
                             timeStep_s_in);

  return GCONST_TRUE;
}