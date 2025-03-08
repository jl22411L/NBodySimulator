/*!
 *    @File:         JamSail_attitudeEstimation.c
 *
 *    @Brief:        Private function definition for attitude estimation of
 *                   JamSail.
 *
 *    @Date:         07/03/2025
 *
 */

#include <stdint.h>

/* Function Includes */
#include "Guidance/ContinuousEkf/PublicFunctions/ContinuousEkf_PublicFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int JamSail_attitudeEstimation(JamSail_State  *p_jamSail_state_inout,
                               JamSail_Params *p_jamSail_params_in,
                               double          timeStep_s_in)
{
  /* Declare local variables */
  double  xxInertiaComponent_Bod_kgm2;
  double  yyInertiaComponent_Bod_kgm2;
  double  zzInertiaComponent_Bod_kgm2;
  double  filteredAngularVelocity_Bod_rads[3];
  // double  filteredMagneticField_Bod_nT[3];
  double  stateEstimateVector[7];
  double  stateEstimateDerivitiveVector[7];
  double  measurementEstimateVector[3];
  double  measurementSensorVector[3];
  double  intermediateKalmanGain[3][3];
  double  errorCovarianceBuffer[7][7];
  uint8_t i;

  /* Clear Variables */
  GZero(&(filteredAngularVelocity_Bod_rads), double[3]);
  // GZero(&(filteredMagneticField_Bod_nT), double[3]);
  GZero(&(stateEstimateVector), double[7]);
  GZero(&(stateEstimateDerivitiveVector), double[7]);
  GZero(&(measurementEstimateVector), double[3]);
  GZero(&(measurementSensorVector), double[3]);
  GZero(&(intermediateKalmanGain), double[3][3]);
  GZero(&(errorCovarianceBuffer), double[7][7]);

  /* Extract diagnol of inertia components */
  xxInertiaComponent_Bod_kgm2 =
      (p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
           .inertiaMatrix_Bod_kgm2[0][0]);
  yyInertiaComponent_Bod_kgm2 =
      (p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
           .inertiaMatrix_Bod_kgm2[1][1]);
  zzInertiaComponent_Bod_kgm2 =
      (p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
           .inertiaMatrix_Bod_kgm2[2][2]);

  /* Find derivitives of state space vector */
  GMath_quaternionRateCalc(&(stateEstimateDerivitiveVector[0]),
                           &(stateEstimateVector[0]),
                           &(stateEstimateVector[4]));
  stateEstimateDerivitiveVector[4] =
      ((p_jamSail_state_inout->magnetorquer_state.totalTorque_Bod_Nm[0]) -
       (zzInertiaComponent_Bod_kgm2 - yyInertiaComponent_Bod_kgm2) *
           filteredAngularVelocity_Bod_rads[1] *
           filteredAngularVelocity_Bod_rads[2]) /
      xxInertiaComponent_Bod_kgm2;
  stateEstimateDerivitiveVector[5] =
      ((p_jamSail_state_inout->magnetorquer_state.totalTorque_Bod_Nm[1]) -
       (xxInertiaComponent_Bod_kgm2 - zzInertiaComponent_Bod_kgm2) *
           filteredAngularVelocity_Bod_rads[0] *
           filteredAngularVelocity_Bod_rads[2]) /
      yyInertiaComponent_Bod_kgm2;
  stateEstimateDerivitiveVector[6] =
      ((p_jamSail_state_inout->magnetorquer_state.totalTorque_Bod_Nm[2]) -
       (yyInertiaComponent_Bod_kgm2 - xxInertiaComponent_Bod_kgm2) *
           filteredAngularVelocity_Bod_rads[0] *
           filteredAngularVelocity_Bod_rads[1]) /
      zzInertiaComponent_Bod_kgm2;

  // stateEstimateDerivitiveVector[7]  = stateEstimateDerivitiveVector[10];
  // stateEstimateDerivitiveVector[8]  = stateEstimateDerivitiveVector[11];
  // stateEstimateDerivitiveVector[9]  = stateEstimateDerivitiveVector[12];
  // stateEstimateDerivitiveVector[10] = stateEstimateDerivitiveVector[13];
  // stateEstimateDerivitiveVector[11] = stateEstimateDerivitiveVector[14];
  // stateEstimateDerivitiveVector[12] = stateEstimateDerivitiveVector[15];
  // stateEstimateDerivitiveVector[13] = 0.0;
  // stateEstimateDerivitiveVector[14] = 0.0;
  // stateEstimateDerivitiveVector[15] = 0.0;

  /* Fill state vector with estimates from previous EKF step */
  // TODO: Put in own private function
  for (i = 0; i < 4; i++)
  {
    stateEstimateVector[i] =
        (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[i]);
  }
  for (i = 0; i < 3; i++)
  {
    stateEstimateVector[i + 4] =
        (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i]);
  }
  // for (i = 0; i < 3; i++)
  // {
  //   stateEstimateVector[i + 7] =
  //       (p_jamSail_state_inout->magneticFieldEstimate_Bod_nT[i]);
  // }
  // for (i = 0; i < 3; i++)
  // {
  //   stateEstimateVector[i + 10] =
  //       (p_jamSail_state_inout->magneticFieldFirstDerivitiveEstimate_Bod_nT[i]);
  // }
  // for (i = 0; i < 3; i++)
  // {
  //   stateEstimateVector[i + 13] =
  //       (p_jamSail_state_inout
  //            ->magneticFieldSecondDerivitiveEstimate_Bod_nT[i]);
  // }

  /* Fill measurement estimate vector */
  // TODO: Put in own private funtion
  for (i = 0; i < 3; i++)
  {
    measurementEstimateVector[i] =
        (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i]);
  }
  // for (i = 0; i < 3; i++)
  // {
  //   measurementEstimateVector[i + 3] =
  //       (p_jamSail_state_inout->magneticFieldEstimate_Bod_nT[i]);
  // }

  /* Find the measured angular velocity in the body frame */
  GMath_quaternionPointRotation(
      &(filteredAngularVelocity_Bod_rads[0]),
      &(p_jamSail_state_inout->gyro_state.filteredGyroVector_Sen_rads[0]),
      &(p_jamSail_params_in->gyro_params.sensorQuaternion_BodToSen[0]));

  // /* Find the measured magnetic field in the body frame */
  // GMath_quaternionPointRotation(
  //     &(filteredMagneticField_Bod_nT[0]),
  //     &(p_jamSail_state_inout->magnetometer_state
  //           .filteredMagneticField_Sen_nT[0]),
  //     &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  /* Fill sensor measurement vector */
  // TODO: Put in own private function
  for (i = 0; i < 3; i++)
  {
    measurementSensorVector[i] = filteredAngularVelocity_Bod_rads[i];
  }
  // for (i = 0; i < 3; i++)
  // {
  //   measurementSensorVector[i + 3] = filteredMagneticField_Bod_nT[i];
  // }

  /* Fill state jacobian matrix */
  // TODO: Put in private function
  (p_jamSail_state_inout->stateJacobian[0][0]) = 0.0;
  (p_jamSail_state_inout->stateJacobian[0][1]) =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);
  (p_jamSail_state_inout->stateJacobian[0][2]) =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_inout->stateJacobian[0][3]) =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_inout->stateJacobian[1][0]) =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);
  (p_jamSail_state_inout->stateJacobian[1][1]) = 0.0;
  (p_jamSail_state_inout->stateJacobian[1][2]) =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_inout->stateJacobian[1][3]) =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_inout->stateJacobian[2][0]) =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_inout->stateJacobian[2][1]) =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_inout->stateJacobian[2][2]) = 0.0;
  (p_jamSail_state_inout->stateJacobian[2][3]) =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);
  (p_jamSail_state_inout->stateJacobian[3][0]) =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_inout->stateJacobian[3][1]) =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_inout->stateJacobian[3][2]) =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);
  (p_jamSail_state_inout->stateJacobian[3][3]) = 0.0;

  (p_jamSail_state_inout->stateJacobian[0][4]) =
      0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);
  (p_jamSail_state_inout->stateJacobian[0][5]) =
      -0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]);
  (p_jamSail_state_inout->stateJacobian[0][6]) =
      0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]);
  (p_jamSail_state_inout->stateJacobian[1][4]) =
      0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]);
  (p_jamSail_state_inout->stateJacobian[1][5]) =
      0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);
  (p_jamSail_state_inout->stateJacobian[1][6]) =
      -0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]);
  (p_jamSail_state_inout->stateJacobian[2][4]) =
      -0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]);
  (p_jamSail_state_inout->stateJacobian[2][5]) =
      0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]);
  (p_jamSail_state_inout->stateJacobian[2][6]) =
      0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);
  (p_jamSail_state_inout->stateJacobian[3][4]) =
      -0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]);
  (p_jamSail_state_inout->stateJacobian[3][5]) =
      -0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]);
  (p_jamSail_state_inout->stateJacobian[3][6]) =
      -0.5 * (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]);

  (p_jamSail_state_inout->stateJacobian[4][4]) = 0.0;
  (p_jamSail_state_inout->stateJacobian[4][5]) =
      -(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]) *
      (zzInertiaComponent_Bod_kgm2 - yyInertiaComponent_Bod_kgm2) /
      xxInertiaComponent_Bod_kgm2;
  (p_jamSail_state_inout->stateJacobian[4][6]) =
      -(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]) *
      (zzInertiaComponent_Bod_kgm2 - yyInertiaComponent_Bod_kgm2) /
      xxInertiaComponent_Bod_kgm2;
  (p_jamSail_state_inout->stateJacobian[5][4]) =
      -(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]) *
      (xxInertiaComponent_Bod_kgm2 - zzInertiaComponent_Bod_kgm2) /
      yyInertiaComponent_Bod_kgm2;
  (p_jamSail_state_inout->stateJacobian[5][5]) = 0.0;
  (p_jamSail_state_inout->stateJacobian[5][6]) =
      -(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]) *
      (xxInertiaComponent_Bod_kgm2 - zzInertiaComponent_Bod_kgm2) /
      yyInertiaComponent_Bod_kgm2;
  (p_jamSail_state_inout->stateJacobian[6][4]) =
      -(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]) *
      (yyInertiaComponent_Bod_kgm2 - xxInertiaComponent_Bod_kgm2) /
      zzInertiaComponent_Bod_kgm2;
  (p_jamSail_state_inout->stateJacobian[6][5]) =
      -(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]) *
      (yyInertiaComponent_Bod_kgm2 - xxInertiaComponent_Bod_kgm2) /
      zzInertiaComponent_Bod_kgm2;
  (p_jamSail_state_inout->stateJacobian[6][6]) = 0.0;

  // for (i = 0; i < 6; i++)
  // {
  //   (p_jamSail_state_inout->stateJacobian[i + 7][i + 10]) = 1.0;
  // }

  /* Archive elements frok EKF */
  // TODO: Put in private function
  for (i = 0; i < 7; i++)
  {
    GArchive_addVal(&(p_jamSail_state_inout->ekfArchive),
                    stateEstimateVector[i]);
  }

  GArchive_writeLine(&(p_jamSail_state_inout->ekfArchive));

  /* Step EKF */
  ContinuousEkf_step(&(p_jamSail_state_inout->stateJacobian[0][0]),
                     &(p_jamSail_state_inout->measurementJacobian[0][0]),
                     &(errorCovarianceBuffer[0][0]),
                     &(p_jamSail_state_inout->errorCovarianceDerivitive[0][0]),
                     &(p_jamSail_params_in->systemNoiseCovariance[0][0]),
                     &(p_jamSail_params_in->sensorNoiseCovariance[0][0]),
                     &(p_jamSail_state_inout->kalmanGain[0][0]),
                     &(intermediateKalmanGain[0][0]),
                     &(measurementEstimateVector[0]),
                     &(measurementSensorVector[0]),
                     7,
                     3,
                     timeStep_s_in,
                     &(p_jamSail_state_inout->errorCovariance[0][0]),
                     &(stateEstimateVector[0]));

  /* Stabalise quaternion so that it is a unit quaternion */
  GMath_findUnitQuaternion(&(stateEstimateVector[0]),
                           &(stateEstimateVector[0]));

  double quaternion_InertCenToBod[4] = {0, 0, 0, 0};
  double quaternion_InertCenToFix[4] = {-0.2027872954, 0.0, 0.0, 0.9792228106};
  GMath_quaternionMul(&(quaternion_InertCenToBod[0]),
                      &(p_jamSail_state_inout->p_satelliteBody_state
                            ->rigidBody_state.quaternion_FixToBody[0]),
                      &(quaternion_InertCenToFix[0]));

  /* Extract state elements from state vector */
  // TODO: Put in private functions
  for (i = 0; i < 4; i++)
  {
    (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[i]) =
        stateEstimateVector[i];
  }

  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i]) =
        stateEstimateVector[i + 4];
  }
  // for (i = 0; i < 3; i++)
  // {
  //   (p_jamSail_state_inout->magneticFieldEstimate_Bod_nT[i]) =
  //       stateEstimateVector[i + 7];
  // }
  // for (i = 0; i < 3; i++)
  // {
  //   (p_jamSail_state_inout->magneticFieldFirstDerivitiveEstimate_Bod_nT[i]) =
  //       stateEstimateVector[i + 10];
  // }
  // for (i = 0; i < 3; i++)
  // {
  //   (p_jamSail_state_inout->magneticFieldSecondDerivitiveEstimate_Bod_nT[i])
  //   =
  //       stateEstimateVector[i + 13];
  // }

  return GCONST_TRUE;
}