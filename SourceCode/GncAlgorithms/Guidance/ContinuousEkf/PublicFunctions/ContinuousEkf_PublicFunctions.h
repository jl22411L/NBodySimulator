/*!
 *    @File:         ContinuousEkf_PublicFunctions.h
 *
 *    @Brief:        Header file containing the Public Functions for Continuous
 *                   EKF.
 *
 *    @Date:         05/03/2025
 *
 */

#ifndef H_CONTINUOUSEKF_PUBLICFUNCTIONS_H
#define H_CONTINUOUSEKF_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Function which will step a continuous EKF.
 *
 *                This function has been set up so that it does not allocate any
 *                memory to variables dynamically or use any buffers. Because of
 *                this, some variables act as buffers. This is to still allow
 *                generability of the EKF and allows for other libraries or
 *                modules to wrap around this one to offer more custom ability
 *                for different systems.
 *
 * @param[in]     p_stateJacobian_in
 *                Pointer containing the address of the measurement jacobian of
 *                the EKF. This should have the dimensions [ekfDegreeM_in x
 *                ekfOrderN_in]
 *
 * @param[in]     p_measurementJacobian_in
 *                Pointer containing the address of the state jacobian of the
 *                EKF. This should have the dimensions [ekfOrderN_in x
 *                ekfOrderN_in]
 *
 * @param[in]     p_updatedErrorCovariance_in
 *                Pointer containing the address of the updated error
 *                covariance. This matrix should have the form [ekfOrderN_in x
 *                ekfOrderN_in]
 *
 *                This essentially acts as a buffer. The updated error
 *                covariance will be automatically applied to the error
 *                covariance matrix in this function.
 *
 * @param[in]     p_errorCovarianceDerivitive_in
 *                Pointer containing the address of the error covariance
 *                derivitive matrix.
 *
 *                This array should have dimensions of
 *                [ekfOrderN_in x ekfOrderN_in]
 *
 * @param[in]     p_systemNoiseCovariance_in
 *                Pointer containing the address of the system noise covariance.
 *                This essentially is used to filter out erros in the state
 *                model and counter any innaccuracies it may have. (Should be
 *                imperrically tuned)
 *
 *                This array should have dimensions of
 *                [ekfOrderN_in x ekfOrderN_in]
 *
 * @param[in]     p_sensorNoiseCovariance_in
 *                Pointer containing the address of the noise covariance metrix.
 *                This matrix will filter out the noise from sensors. (Should be
 *                imperrically tuned)
 *
 *                This array should have dimensions of
 *                [ekfDegreeM_in x ekfDegreeM_in]
 *
 * @param[in]     p_kalmanGain_in
 *                Pointer containing the address of the Kalman Gain matrix. This
 *                shold take the form [ekfOrderN_in x ekfDegreeM_in]
 *
 * @param[in]     p_intermediateKalmanGain_in
 *                Pointer containing the address of the intermediate KalmanGain.
 *                This is essentially a workaround to avoid having to use a
 *                buffer or dynamically allocate memory. The intermediate Kalman
 *                gain takes the form off:
 *                      intermediateKalmanGain = (H*P*H^T + R)^-1
 *
 *                This then takes advantage of the GMath_invMat() function
 *                which can have the output also be the input to the function.
 *                This array should have dimensions of [ekfDegreeM_in x
 *                ekfDegreeM_in]
 *
 * @param[in]     p_measurementEstimation_in
 *                Pointer containing the address of the measurement estimation,
 *                based on the state vector.
 *
 *                This should have the dimensions [1 x ekfDegreeM_in]
 *
 * @param[in]     p_sensorMeasurement_in
 *                Pointer containing the address of the measurement vector.
 *
 *                This should have the dimensions [1 x ekfDegreeM_in]
 *
 * @param[in]     ekfOrderN_in
 *                Order of the EKF. This represents the number of elements in
 *                the state vector.
 *
 * @param[in]     ekfDegreeM_in
 *                Order of the EKF. This represents the number of elements in
 *                the measurement vector.
 *
 * @param[in]     timeStep_s_in
 *                Change in time since last EKF call.
 *
 * @param[in,out] p_errorCovariance_inout
 *                Pointer containing error covariance at current timestep. The
 *                change in error covariance will be calculated fromt the
 *                derivitive and time step, beore being summed with this matrix.
 *
 *                This array should have dimensions of
 *                [ekfOrderN_in x ekfOrderN_in]
 *
 * @param[in,out] p_stateEstimation_inout
 *                Pointer containing the addess of the state of the system.
 *
 *                This should have the dimensions [1 x ekfOrderN_in]
 *
 * @return        Upon successful completion of function, a GCONST_TRUE will be
 *                returned. Upon an unsuccessful completion, a GCONST_FALSE will
 *                be returned.
 */
extern int ContinuousEkf_step(double *p_stateJacobian_in,
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
                              double *p_stateEstimation_inout);

#ifdef __cplusplus
}
#endif
#endif /* H_CONTINUOUSEKF_PUBLICFUNCTIONS_H */