/*!
 *    @File:         JamSail_attitudeDetermination.c
 *
 *    @Brief:        Function which runs JamSail's determination algorithm
 *
 *    @Date:         05/03/2025
 *
 */

#include <math.h>
#include <stdio.h>

/* Function Includes */
#include "Guidance/KeplarianPropogation/PublicFunctions/KeplarianPropogation_PublicFunctions.h"
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

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
  double jamSailPositionCartesian_GeoCen_m[3];
  double jamSailPositionSpherical_GeoCen_m[3];
  double quaternion_InertCenToGeoCen[4];
  double euler_GeoCenToNed_123[3];
  double magneticFieldVector_Ned_nT[3];
  double magneticFieldVector_GeoCen_nT[3];
  double quaternion_GeoCenToNed[4];

  /* Clear variables */
  GZero(&(jamSailPositionSpherical_GeoCen_m[0]), double[3]);
  GZero(&(euler_GeoCenToNed_123[0]), double[3]);
  GZero(&(quaternion_GeoCenToNed[0]), double[4]);
  GZero(&(magneticFieldVector_Ned_nT[0]), double[3]);
  GZero(&(magneticFieldVector_GeoCen_nT[0]), double[3]);

  /* Perform keplarian propogation to find position of JamSail */
  KeplarianPropogation_keplarianToCartesian(
      (p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
           .rigidBodyMass_kg),
      (p_jamSail_params_in->earthMass_kg),
      (p_jamSail_params_in->semiMajorAxis_km) * GCONST_KM_TOLERANCE,
      (p_jamSail_params_in->eccentricity),
      (p_jamSail_params_in->inclination_rad),
      (p_jamSail_params_in->argumentOfPerigee_rad),
      (p_jamSail_params_in->raans_rad),
      (p_jamSail_params_in->timeSincePeriapsis_s),
      simTime_s_in,
      &(p_jamSail_state_inout->positionEstimate_InertCen_m[0]));

  /* Find quaternion from inertial centric frame to geocentric frame */
  quaternion_InertCenToGeoCen[0] = 0.0;
  quaternion_InertCenToGeoCen[1] = 0.0;
  quaternion_InertCenToGeoCen[2] =
      sin((p_jamSail_params_in->averageEarthRotationalSpeedMag_rads) *
          (simTime_s_in - GCONST_J2000_UNIX_TIME_S) / 2);
  quaternion_InertCenToGeoCen[3] =
      cos((p_jamSail_params_in->averageEarthRotationalSpeedMag_rads) *
          (simTime_s_in - GCONST_J2000_UNIX_TIME_S) / 2);

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
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen_nT[0]),
      &(magneticFieldVector_GeoCen_nT[0]),
      &(quaternion_InertCenToGeoCen[0]));

  /* Find norm of magnetic field  */
  GMath_vectorNorm(
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen_nT[0]),
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen_nT[0]),
      3);

  /* Find an estiamte of the magnetic field in the body frame */
  GMath_quaternionFrameRotation(
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_Bod_nT[0]),
      &(p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen_nT[0]),
      &(p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]));

  /* Measure JamSail's attitude */
  JamSail_attitudeEstimation(p_jamSail_state_inout,
                             p_jamSail_params_in,
                             timeStep_s_in);

  // /* Check if the sun sensor reading is valid */
  // if (p_jamSail_state_inout->sunSensor_state.isSensorReadingInvalid)
  // {
  //   /* Perform keplarian propogation to find position of sun */
  //   // TODO

  //   // TODO:  Remember to move this down to else part of if statement
  //   /* Find magnetic field in the body frame */
  //   // TODO: (Add magnetic field estimate to JamSail state)
  // }
  // else
  // {
  //   /* Run estimation of JamSail attitude */

  //   /* Set flag to indicate that measurement was taken for timestep */
  //   p_jamSail_state_inout->attitudeMeasuredFlag = GCONST_TRUE;
  // }
  printf("%lf\n", Utilities.simTime_s);

  /* Archive attitude determination results */
  JamSail_archiveData(p_jamSail_state_inout);

  return GCONST_TRUE;
}