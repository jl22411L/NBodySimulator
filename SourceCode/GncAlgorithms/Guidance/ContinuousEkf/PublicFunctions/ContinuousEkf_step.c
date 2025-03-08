/*!
 *    @File:         ContinuousEkf_step.c
 *
 *    @Brief:        Function which will step the EKF
 *
 *    @Date:         05/03/2025
 *
 */

/* Function Includes */
#include "Guidance/ContinuousEkf/PrivateFunctions/ContinuousEkf_PrivateFunctions.h"

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int ContinuousEkf_step(double *p_stateJacobian_in,
                       double *p_measurementJacobian_in,
                       double *p_updatedErrorCovariance_in,
                       double *p_errorCovarianceDerivitive_in,
                       double *p_systemNoiseCovariance_in,
                       double *p_sensorNoiseCovariance_in,
                       double *p_kalmanGain_in,
                       double *p_intermediateKalmanGain_in,
                       double *p_measurementEstimation_in,
                       double *p_sensorMeasurement_in,
                       uint8_t ekfOrderN_in,
                       uint8_t ekfDegreeM_in,
                       double  timeStep_s_in,
                       double *p_errorCovariance_inout,
                       double *p_stateEstimation_inout)
{
  /* Declare local variables */
  /* None */

  /* Find the Kalman Gain */
  ContinuousEkf_findKalmanGain(p_intermediateKalmanGain_in,
                               p_measurementJacobian_in,
                               p_sensorNoiseCovariance_in,
                               p_errorCovariance_inout,
                               ekfOrderN_in,
                               ekfDegreeM_in,
                               p_kalmanGain_in);

  /* Apply state correction */
  ContinuousEkf_stateCorrection(p_kalmanGain_in,
                                p_sensorMeasurement_in,
                                p_measurementEstimation_in,
                                p_stateJacobian_in,
                                ekfOrderN_in,
                                ekfDegreeM_in,
                                p_stateEstimation_inout);

  /* Update error covariance */
  ContinuousEkf_findUpdatedErrorCovariance(p_kalmanGain_in,
                                           p_measurementJacobian_in,
                                           p_errorCovariance_inout,
                                           p_updatedErrorCovariance_in,
                                           ekfOrderN_in,
                                           ekfDegreeM_in);

  /* Find the error covariance derivitive */
  ContinuousEkf_findCovarianceDerivitive(p_stateJacobian_in,
                                         p_errorCovariance_inout,
                                         p_systemNoiseCovariance_in,
                                         ekfOrderN_in,
                                         p_errorCovarianceDerivitive_in);

  /* Find the error covariance */
  ContinuousEkf_stepCovariance(p_errorCovarianceDerivitive_in,
                               timeStep_s_in,
                               ekfOrderN_in,
                               p_errorCovariance_inout);

  return GCONST_TRUE;
}