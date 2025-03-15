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
  double  intermediateKalmanGain[JAMSAIL_EKF_DEGREE_M][JAMSAIL_EKF_DEGREE_M];
  double  errorCovarianceBuffer[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N];
  uint8_t i;

  /* Clear Variables */
  GZero(&(stateEstimateVector), double[JAMSAIL_EKF_ORDER_N]);
  GZero(&(stateEstimateDerivitiveVector), double[JAMSAIL_EKF_ORDER_N]);
  GZero(&(measurementEstimateVector), double[JAMSAIL_EKF_DEGREE_M]);
  GZero(&(measurementSensorVector), double[JAMSAIL_EKF_DEGREE_M]);
  GZero(&(intermediateKalmanGain),
        double[JAMSAIL_EKF_DEGREE_M][JAMSAIL_EKF_DEGREE_M]);
  GZero(&(errorCovarianceBuffer),
        double[JAMSAIL_EKF_ORDER_N][JAMSAIL_EKF_ORDER_N]);

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

  /* Fill state vector with estimates from previous EKF step */
  JamSail_estimationEkfLoadVectors(&(stateEstimateVector[0]),
                                   &(measurementEstimateVector[0]),
                                   &(measurementSensorVector[0]),
                                   p_jamSail_state_inout,
                                   p_jamSail_params_in);

  /* Fill state jacobian */
  JamSail_fillStateJacobian(p_jamSail_state_inout,
                            xxInertiaComponent_Bod_kgm2,
                            yyInertiaComponent_Bod_kgm2,
                            zzInertiaComponent_Bod_kgm2);

  /* Fill observation jacobian */
  JamSail_fillObservationJacobian(p_jamSail_state_inout);

  /* Step EKF */
  ContinuousEkf_step(&(p_jamSail_state_inout->stateJacobian[0][0]),
                     &(p_jamSail_state_inout->observationJacobian[0][0]),
                     &(errorCovarianceBuffer[0][0]),
                     &(p_jamSail_state_inout->errorCovarianceDerivitive[0][0]),
                     &(p_jamSail_params_in->systemNoiseCovariance[0][0]),
                     &(p_jamSail_params_in->sensorNoiseCovariance[0][0]),
                     &(p_jamSail_state_inout->kalmanGain[0][0]),
                     &(intermediateKalmanGain[0][0]),
                     &(measurementEstimateVector[0]),
                     &(measurementSensorVector[0]),
                     JAMSAIL_EKF_ORDER_N,
                     JAMSAIL_EKF_DEGREE_M,
                     timeStep_s_in,
                     &(p_jamSail_state_inout->errorCovariance[0][0]),
                     &(stateEstimateVector[0]));

  /* Find derivitive of state */
  JamSail_findStateDerivitive(p_jamSail_state_inout,
                              &stateEstimateVector[0],
                              xxInertiaComponent_Bod_kgm2,
                              yyInertiaComponent_Bod_kgm2,
                              zzInertiaComponent_Bod_kgm2,
                              &stateEstimateDerivitiveVector[0]);

  /* Step state vector */
  for (i = 0; i < JAMSAIL_EKF_ORDER_N; i++)
  {
    stateEstimateVector[i] += timeStep_s_in * stateEstimateDerivitiveVector[i];
  }

  /* Update estimate members in JamSail_state */
  JamSail_updateEstimateMembers(&stateEstimateVector[0], p_jamSail_state_inout);

  /* Stabalise quaternion so that it is a unit quaternion */
  GMath_findUnitQuaternion(
      &(p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]),
      &(p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]));

  return GCONST_TRUE;
}