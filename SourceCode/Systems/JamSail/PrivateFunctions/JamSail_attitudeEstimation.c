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
#include <stdio.h> // REMOVE

/* Function Includes */
#include "Guidance/ContinuousEkf/PrivateFunctions/ContinuousEkf_PrivateFunctions.h"
#include "Guidance/ContinuousEkf/PublicFunctions/ContinuousEkf_PublicFunctions.h"
#include "JamSail/PrivateFunctions/JamSail_PrivateFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
#include "JamSail/ConstantDefs/JamSail_Const.h"

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
  double  stateEstimateVector[JAMSAIL_EKF_ORDER_N];
  double  stateEstimateDerivitiveVector[JAMSAIL_EKF_ORDER_N];
  double  measurementEstimateVector[JAMSAIL_EKF_DEGREE_M];
  double  measurementSensorVector[JAMSAIL_EKF_DEGREE_M];
  double  differenceVector[JAMSAIL_EKF_DEGREE_M];
  double  stateJacobian[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];
  double  observationJacobian[JAMSAIL_EKF_DEGREE_M][JAMSAIL_EKF_ORDER_N];
  double  errorCovarianceBuffer[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];
  double  errorCovarianceDerivitive[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];
  double  kalmanGain[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_DEGREE_M];
  double  kalmanGainBuffer[JAMSAIL_EKF_DEGREE_M][JAMSAIL_EKF_DEGREE_M];
  double  rotationMatrix[3][3];
  double  vectorBuffer[3];
  double  stateUpdate[7];
  uint8_t i;
  uint8_t j;

  /* Clear Variables */
  GZero(&(stateEstimateVector), double[JAMSAIL_EKF_ORDER_N]);
  GZero(&(stateEstimateDerivitiveVector), double[JAMSAIL_EKF_ORDER_N]);
  GZero(&(measurementEstimateVector), double[JAMSAIL_EKF_DEGREE_M]);
  GZero(&(measurementSensorVector), double[JAMSAIL_EKF_DEGREE_M]);
  GZero(&(differenceVector), double[JAMSAIL_EKF_DEGREE_M]);
  GZero(&(stateJacobian[0][0]),
        double[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N]);
  GZero(&(observationJacobian[0][0]),
        double[JAMSAIL_EKF_DEGREE_M][JAMSAIL_EKF_ORDER_N]);
  GZero(&(errorCovarianceBuffer[0][0]),
        double[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N]);
  GZero(&(errorCovarianceDerivitive[0][0]),
        double[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N]);
  GZero(&(p_jamSail_state_inout->kalmanGain[0][0]),
        double[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_DEGREE_M]);
  GZero(&(p_jamSail_state_inout->kalmanGain[0][0]),
        double[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_DEGREE_M]);
  GZero(&kalmanGain[0], double[3]);
  GZero(&kalmanGainBuffer[0], double[3]);
  GZero(&rotationMatrix[0][0], double[3][3]);
  GZero(&vectorBuffer[0], double[3]);
  GZero(&stateUpdate[0], double[7]);

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

  /* Load state vector */
  //   GMath_quaternionConjugate(
  //       &(stateEstimateVector[0]),
  //       &(p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]));

  for (i = 0; i < 4; i++)
  {
    stateEstimateVector[i] =
        p_jamSail_state_inout->quaternionEstimate_InertCenToBod[i];
  }
  for (i = 0; i < 3; i++)
  {
    stateEstimateVector[i + 4] =
        p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i];
  }

  /* Load measurement vector */
  GMath_quaternionPointRotation(
      &measurementSensorVector[0],
      &p_jamSail_state_inout->gyro_state.filteredGyroVector_Sen_rads[0],
      &p_jamSail_params_in->gyro_params.sensorQuaternion_BodToSen[0]);
  GMath_quaternionPointRotation(
      &measurementSensorVector[3],
      &p_jamSail_state_inout->magnetometer_state
           .filteredMagneticField_Sen_nT[0],
      &p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]);

  if (p_jamSail_state_inout->sunSensor_state.isSensorReadingInvalid ==
      GCONST_TRUE)
  {
    measurementSensorVector[6] =
        p_jamSail_state_inout->sunVectorEstimateNorm_Bod[0];
    measurementSensorVector[7] =
        p_jamSail_state_inout->sunVectorEstimateNorm_Bod[1];
    measurementSensorVector[8] =
        p_jamSail_state_inout->sunVectorEstimateNorm_Bod[2];
  }
  else
  {
    GMath_quaternionPointRotation(
        &measurementSensorVector[6],
        &p_jamSail_state_inout->sunSensor_state.filteredSunVector_Sen_m[0],
        &p_jamSail_params_in->sunSensor_params.sensorQuaternion_BodToSen[0]);
  }

  /* Load measurement vector */
  measurementEstimateVector[0] =
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0];
  measurementEstimateVector[1] =
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1];
  measurementEstimateVector[2] =
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2];
  measurementEstimateVector[3] =
      p_jamSail_state_inout->magneticFieldEstimateNorm_Bod[0];
  measurementEstimateVector[4] =
      p_jamSail_state_inout->magneticFieldEstimateNorm_Bod[1];
  measurementEstimateVector[5] =
      p_jamSail_state_inout->magneticFieldEstimateNorm_Bod[2];
  measurementEstimateVector[6] =
      p_jamSail_state_inout->sunVectorEstimateNorm_Bod[0];
  measurementEstimateVector[7] =
      p_jamSail_state_inout->sunVectorEstimateNorm_Bod[1];
  measurementEstimateVector[8] =
      p_jamSail_state_inout->sunVectorEstimateNorm_Bod[2];

  GMath_findUnitVector(&measurementSensorVector[3],
                       &measurementSensorVector[3]);
  GMath_findUnitVector(&measurementSensorVector[6],
                       &measurementSensorVector[6]);
  GMath_findUnitVector(&measurementEstimateVector[3],
                       &measurementEstimateVector[3]);
  GMath_findUnitVector(&measurementEstimateVector[6],
                       &measurementEstimateVector[6]);

  /* Find differeence */
  for (i = 0; i < 9; i++)
  {
    differenceVector[i] =
        measurementSensorVector[i] - measurementEstimateVector[i];
  }

  /* Find state jacobian */
  stateJacobian[0][1] =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);
  stateJacobian[0][2] =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  stateJacobian[0][3] =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  stateJacobian[1][0] =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);
  stateJacobian[1][2] =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  stateJacobian[1][3] =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  stateJacobian[2][0] =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  stateJacobian[2][1] =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  stateJacobian[2][3] =
      0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);
  stateJacobian[3][0] =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);
  stateJacobian[3][1] =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]);
  stateJacobian[3][2] =
      -0.5 * (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]);

  stateJacobian[0][4] = 0.5 * (stateEstimateVector[3]);
  stateJacobian[0][5] = -0.5 * (stateEstimateVector[2]);
  stateJacobian[0][6] = 0.5 * (stateEstimateVector[1]);
  stateJacobian[1][4] = 0.5 * (stateEstimateVector[2]);
  stateJacobian[1][5] = 0.5 * (stateEstimateVector[3]);
  stateJacobian[1][6] = -0.5 * (stateEstimateVector[0]);
  stateJacobian[2][4] = -0.5 * (stateEstimateVector[1]);
  stateJacobian[2][5] = 0.5 * (stateEstimateVector[0]);
  stateJacobian[2][6] = 0.5 * (stateEstimateVector[3]);
  stateJacobian[3][4] = -0.5 * (stateEstimateVector[0]);
  stateJacobian[3][5] = -0.5 * (stateEstimateVector[1]);
  stateJacobian[3][6] = -0.5 * (stateEstimateVector[2]);

  stateJacobian[4][5] =
      (yyInertiaComponent_Bod_kgm2 - zzInertiaComponent_Bod_kgm2) /
      xxInertiaComponent_Bod_kgm2 *
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2];
  stateJacobian[4][6] =
      (yyInertiaComponent_Bod_kgm2 - zzInertiaComponent_Bod_kgm2) /
      xxInertiaComponent_Bod_kgm2 *
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1];
  stateJacobian[5][4] =
      (zzInertiaComponent_Bod_kgm2 - xxInertiaComponent_Bod_kgm2) /
      yyInertiaComponent_Bod_kgm2 *
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2];
  stateJacobian[5][6] =
      (zzInertiaComponent_Bod_kgm2 - xxInertiaComponent_Bod_kgm2) /
      yyInertiaComponent_Bod_kgm2 *
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0];
  stateJacobian[6][4] =
      (xxInertiaComponent_Bod_kgm2 - yyInertiaComponent_Bod_kgm2) /
      zzInertiaComponent_Bod_kgm2 *
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1];
  stateJacobian[6][5] =
      (xxInertiaComponent_Bod_kgm2 - yyInertiaComponent_Bod_kgm2) /
      zzInertiaComponent_Bod_kgm2 *
      p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0];

  /* Find observation jacobian */
  observationJacobian[0][4] = 1.0;
  observationJacobian[1][5] = 1.0;
  observationJacobian[2][6] = 1.0;

  rotationMatrix[0][0] = 2 * stateEstimateVector[0];
  rotationMatrix[0][1] = 2 * stateEstimateVector[1];
  rotationMatrix[0][2] = 2 * stateEstimateVector[2];
  rotationMatrix[1][0] = 2 * stateEstimateVector[1];
  rotationMatrix[1][1] = -2 * stateEstimateVector[0];
  rotationMatrix[1][2] = 2 * stateEstimateVector[3];
  rotationMatrix[2][0] = 2 * stateEstimateVector[2];
  rotationMatrix[2][1] = -2 * stateEstimateVector[3];
  rotationMatrix[2][2] = -2 * stateEstimateVector[0];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[3][0] = vectorBuffer[0];
  observationJacobian[4][0] = vectorBuffer[1];
  observationJacobian[5][0] = vectorBuffer[2];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->sunVectorEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[6][0] = vectorBuffer[0];
  observationJacobian[7][0] = vectorBuffer[1];
  observationJacobian[8][0] = vectorBuffer[2];

  rotationMatrix[0][0] = -2 * stateEstimateVector[1];
  rotationMatrix[0][1] = 2 * stateEstimateVector[0];
  rotationMatrix[0][2] = -2 * stateEstimateVector[2];
  rotationMatrix[1][0] = 2 * stateEstimateVector[0];
  rotationMatrix[1][1] = 2 * stateEstimateVector[1];
  rotationMatrix[1][2] = 2 * stateEstimateVector[2];
  rotationMatrix[2][0] = 2 * stateEstimateVector[3];
  rotationMatrix[2][1] = 2 * stateEstimateVector[2];
  rotationMatrix[2][2] = -2 * stateEstimateVector[1];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[3][1] = vectorBuffer[0];
  observationJacobian[4][1] = vectorBuffer[1];
  observationJacobian[5][1] = vectorBuffer[2];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->sunVectorEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[6][1] = vectorBuffer[0];
  observationJacobian[7][1] = vectorBuffer[1];
  observationJacobian[8][1] = vectorBuffer[2];

  rotationMatrix[0][0] = -2 * stateEstimateVector[2];
  rotationMatrix[0][1] = 2 * stateEstimateVector[3];
  rotationMatrix[0][2] = 2 * stateEstimateVector[0];
  rotationMatrix[1][0] = -2 * stateEstimateVector[3];
  rotationMatrix[1][1] = -2 * stateEstimateVector[2];
  rotationMatrix[1][2] = 2 * stateEstimateVector[1];
  rotationMatrix[2][0] = 2 * stateEstimateVector[0];
  rotationMatrix[2][1] = 2 * stateEstimateVector[1];
  rotationMatrix[2][2] = 2 * stateEstimateVector[2];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[3][2] = vectorBuffer[0];
  observationJacobian[4][2] = vectorBuffer[1];
  observationJacobian[5][2] = vectorBuffer[2];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->sunVectorEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[6][2] = vectorBuffer[0];
  observationJacobian[7][2] = vectorBuffer[1];
  observationJacobian[8][2] = vectorBuffer[2];

  rotationMatrix[0][0] = 2 * stateEstimateVector[3];
  rotationMatrix[0][1] = 2 * stateEstimateVector[2];
  rotationMatrix[0][2] = -2 * stateEstimateVector[1];
  rotationMatrix[1][0] = -2 * stateEstimateVector[2];
  rotationMatrix[1][1] = 2 * stateEstimateVector[3];
  rotationMatrix[1][2] = 2 * stateEstimateVector[0];
  rotationMatrix[2][0] = 2 * stateEstimateVector[1];
  rotationMatrix[2][1] = -2 * stateEstimateVector[0];
  rotationMatrix[2][2] = 2 * stateEstimateVector[3];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->magneticFieldEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[3][3] = vectorBuffer[0];
  observationJacobian[4][3] = vectorBuffer[1];
  observationJacobian[5][3] = vectorBuffer[2];

  GMath_matMul(&rotationMatrix[0][0],
               3,
               3,
               &p_jamSail_state_inout->sunVectorEstimateNorm_InertCen[0],
               3,
               1,
               &vectorBuffer[0]);

  observationJacobian[6][3] = vectorBuffer[0];
  observationJacobian[7][3] = vectorBuffer[1];
  observationJacobian[8][3] = vectorBuffer[2];

  /* Find kalman gain */
  ContinuousEkf_findKalmanGain(
      &kalmanGainBuffer[0][0],
      &observationJacobian[0][0],
      &p_jamSail_params_in->sensorNoiseCovariance[0][0],
      &p_jamSail_state_inout->errorCovariance[0][0],
      JAMSAIL_EKF_ORDER_N,
      JAMSAIL_EKF_DEGREE_M,
      &kalmanGain[0][0]);

  /* Find vector to update state by */
  GMath_matMul(&kalmanGain[0][0],
               JAMSAIL_EKF_ORDER_N,
               JAMSAIL_EKF_DEGREE_M,
               &differenceVector[0],
               JAMSAIL_EKF_DEGREE_M,
               1,
               &stateUpdate[0]);

  for (i = 0; i < 7; i++)
  {
    stateEstimateVector[i] += stateUpdate[i];
  }

  //   /* Unload state vector */
  //   GMath_quaternionConjugate(
  //       &p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0],
  //       &stateEstimateVector[0]);
  for (i = 0; i < 4; i++)
  {
    p_jamSail_state_inout->quaternionEstimate_InertCenToBod[i] =
        stateEstimateVector[i];
  }

  GMath_findUnitQuaternion(
      &p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0],
      &p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]);

  for (i = 0; i < 3; i++)
  {
    p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i] =
        stateEstimateVector[i + 4];
  }

  /* Update error covatiance */
  ContinuousEkf_findUpdatedErrorCovariance(
      &kalmanGain[0][0],
      &observationJacobian[0][0],
      &p_jamSail_state_inout->errorCovariance[0][0],
      &errorCovarianceBuffer[0][0],
      JAMSAIL_EKF_ORDER_N,
      JAMSAIL_EKF_DEGREE_M);

  // ----------
  double quaternion_InertCenToFix[4];
  double quaternion_InertCenToBod[4];

  GMath_quaternionConjugate(&quaternion_InertCenToFix[0],
                            &p_jamSail_params_in->quaternion_FixToInertCen[0]);

  GMath_quaternionMul(&quaternion_InertCenToBod[0],
                      &quaternion_InertCenToFix[0],
                      &p_jamSail_state_inout->p_satelliteBody_state
                           ->rigidBody_state.quaternion_FixToBody[0]);

  printf("[");
  for (i = 0; i < 4; i++)
  {
    printf("%lf ",
           p_jamSail_state_inout->quaternionEstimate_InertCenToBod[i] -
               quaternion_InertCenToBod[i]);
  }
  printf("]");

  /* Step Control Algorithm */
  JamSail_controlAlgorithm(p_jamSail_state_inout, p_jamSail_params_in);

  for (i = 0; i < 3; i++)
  {
    if (p_jamSail_state_inout->controlTorque_Bod_Nm[i] > 0.001)
    {
      (p_jamSail_state_inout->controlTorque_Bod_Nm[i]) = 0.001;
    }
    else if (p_jamSail_state_inout->controlTorque_Bod_Nm[i] < -0.001)
    {
      (p_jamSail_state_inout->controlTorque_Bod_Nm[i]) = -0.001;
    }
  }

  /* Find state derivitive */
  stateEstimateDerivitiveVector[4] =
      (p_jamSail_state_inout->controlTorque_Bod_Nm[0] -
       p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1] *
           p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2] *
           (zzInertiaComponent_Bod_kgm2 - yyInertiaComponent_Bod_kgm2)) /
      xxInertiaComponent_Bod_kgm2;

  stateEstimateDerivitiveVector[5] =
      (p_jamSail_state_inout->controlTorque_Bod_Nm[1] -
       p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2] *
           p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0] *
           (xxInertiaComponent_Bod_kgm2 - zzInertiaComponent_Bod_kgm2)) /
      yyInertiaComponent_Bod_kgm2;

  stateEstimateDerivitiveVector[6] =
      (p_jamSail_state_inout->controlTorque_Bod_Nm[2] -
       p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0] *
           p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1] *
           (yyInertiaComponent_Bod_kgm2 - xxInertiaComponent_Bod_kgm2)) /
      zzInertiaComponent_Bod_kgm2;

  GMath_quaternionFrameRateCalc(
      &stateEstimateDerivitiveVector[0],
      &p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0],
      &p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]);

  ContinuousEkf_findCovarianceDerivitive(
      &stateJacobian[0][0],
      &p_jamSail_state_inout->errorCovariance[0][0],
      &p_jamSail_params_in->systemNoiseCovariance[0][0],
      JAMSAIL_EKF_ORDER_N,
      &errorCovarianceDerivitive[0][0]);

  for (i = 0; i < 7; i++)
  {
    stateEstimateVector[i] += stateEstimateDerivitiveVector[i] * timeStep_s_in;
  }

  GMath_findUnitQuaternion(
      &stateEstimateVector[0],
      &p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]);

  for (i = 0; i < 3; i++)
  {
    p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i] =
        stateEstimateVector[i + 4];
  }

  /* Integrate error co variance */
  for (i = 0; i < JAMSAIL_EKF_ORDER_N; i++)
  {
    for (j = 0; j < JAMSAIL_EKF_ORDER_N; j++)
    {
      p_jamSail_state_inout->errorCovariance[i][j] +=
          errorCovarianceDerivitive[i][j] * timeStep_s_in;
    }
  }

  return GCONST_TRUE;
}