/*!
 *    @File:         ContinuousEkf_PrivateFunctions.h
 *
 *    @Brief:        Private function header file for Continuous EKF
 *
 *    @Date:         04/03/2025
 *
 */

#ifndef H_CONTINUOUSEKF_PRIVATEFUNCTIONS_H
#define H_CONTINUOUSEKF_PRIVATEFUNCTIONS_H

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
 * @brief         Function which will find the covariance derivitive which will
 *                then be used to find the error covariance. It follows the
 *                equation:
 *                  dP = F*P + P*F^T + Q
 *
 * @param[in]     p_stateJacobian_in
 *                Pointer containing the address of the jacobian matrix
 *                representing the state model. This should follow the
 *                continuous EKF representation and not follow the discrete
 *                form (Taylor Series).
 *
 * @param[in]     p_errorCovariance_in
 *                Pointer containing the address of the error covariance matrix.
 *                This should be from the previous step. (Note: EKFs follow a
 *                different integration process than the simulator.)
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
 * @param[in]     ekfOrderN_in
 *                Order of the EKF. This represents the number of elements in
 *                the state vector.
 *
 * @param[out]    p_errorCovarianceDerivitive_out
 *                Pointer containing the address of the error covariance
 *                derivitive matrix, where the output would be stored.
 *
 *                This array should have dimensions of
 *                [ekfOrderN_in x ekfOrderN_in]
 *
 * @return        Upon successful completion of function, a GCONST_TRUE will be
 *                returned. Upon an unsuccessful completion, a GCONST_FALSE will
 *                be returned.
 */
extern int ContinuousEkf_findCovarianceDerivitive(
    double *p_stateJacobian_in,
    double *p_errorCovariance_in,
    double *p_systemNoiseCovariance_in,
    uint8_t ekfOrderN_in,
    double *p_errorCovarianceDerivitive_out);

/*!
 * @brief         Function which will compute the Kalman Gain. This takes the
 *                form of the equaion:
 *                    K = Pk*(H^T)*(H*P*H^T + R)^-1
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
 * @param[in]     p_measurementJacobian_in
 *                Pointer containing address of jacobian matrix representing the
 *                linearised form of the measurement matrix. It should have the
 *                dimenions [ekfDegreeM_in x ekfOrderN_in]
 *
 * @param[in]     p_sensorNoiseCovariance_in
 *                Pointer containing the address of the noise covariance metrix.
 *                This matrix will filter out the noise from sensors. (Should be
 *                imperrically tuned)
 *
 * @param[in]     p_errorCovariance_in
 *                Pointer containing the address of the error covariance. This
 *                matrix should have the form [ekfOrderN_in x ekfOrderN_in]
 *
 * @param[in]     ekfOrderN_in
 *                Order of the EKF. This represents the number of elements in
 *                the state vector.
 *
 * @param[in]     ekfDegreeM_in
 *                Order of the EKF. This represents the number of elements in
 *                the measurement vector.
 *
 * @param[out]    p_kalmanGain_out
 *                Pointer containing the address of the Kalman Gain matrix. This
 *                shold take the form [ekfOrderN_in x ekfDegreeM_in]
 *
 * @return        Upon successful completion of function, a GCONST_TRUE will be
 *                returned. Upon an unsuccessful completion, a GCONST_FALSE will
 *                be returned.
 */
extern int ContinuousEkf_findKalmanGain(double *p_intermediateKalmanGain_in,
                                        double *p_measurementJacobian_in,
                                        double *p_sensorNoiseCovariance_in,
                                        double *p_errorCovariance_in,
                                        uint8_t ekfOrderN_in,
                                        uint8_t ekfDegreeM_in,
                                        double *p_kalmanGain_out);

/*!
 * @brief         Function which will find he updated covariance of the EKF.
 *                This applies the forumla:
 *                    P = P - K*H*P
 *
 * @param[in]     p_kalmanGain_in
 *                Pointer containing the address of the Kalman Gain matrix. This
 *                shold take the form [ekfOrderN_in x ekfDegreeM_in]
 *
 * @param[in]     p_measurementJacobian_in
 *                Pointer containing address of jacobian matrix representing the
 *                linearised form of the measurement matrix. It should have the
 *                dimenions [ekfDegreeM_in x ekfOrderN_in]
 *
 * @param[in]     p_errorCovariance_inout
 *                Pointer containing the address of the error covariance. This
 *                matrix should have the form [ekfOrderN_in x ekfOrderN_in]
 *
 *                Due to the implementation of the function, the updated error
 *                covariance matrix will act as a buffer before having its
 *                values are applied to the error covariance matrix.
 *
 * @param[out]    p_updatedErrorCovariance_in
 *                Pointer containing the address of the updated error
 *                covariance. This matrix should have the form [ekfOrderN_in x
 *                ekfOrderN_in]
 *
 *                This essentially acts as a buffer. The updated error
 *                covariance will be automatically applied to the error
 *                covariance matrix in this function.
 *
 * @param[in]     ekfOrderN_in
 *                Order of the EKF. This represents the number of elements in
 *                the state vector.
 *
 * @param[in]     ekfDegreeM_in
 *                Order of the EKF. This represents the number of elements in
 *                the measurement vector.
 *
 * @return        Upon successful completion of function, a GCONST_TRUE will be
 *                returned. Upon an unsuccessful completion, a GCONST_FALSE will
 *                be returned.
 */
extern int ContinuousEkf_findUpdatedErrorCovariance(
    double *p_kalmanGain_in,
    double *p_measurementJacobian_in,
    double *p_errorCovariance_inout,
    double *p_updatedErrorCovarianceBuffer_in,
    uint8_t ekfOrderN_in,
    uint8_t ekfDegreeM_in);

/*!
 * @brief         Function which applied the state correction based on
 *                measurement values from sensors.
 *
 *                This follows the formula:
 *                        x = x + K*(y-z)
 *
 * @param[in]     p_kalmanGain_in
 *                Pointer containing the address of the kalman gain.
 *
 * @param[in]     p_sensorMeasurement_in
 *                Pointer containing the address of the measurement vector.
 *
 * @param[in]     p_measurementEstimation_in
 *                Pointer containing the address of the measurement estimation,
 *                based on the state vector.
 *
 * @param[in]     p_stateJacobian_in
 *                Pointer containing the address of the jacobian matrix
 *                representing the linearised form of the state model.
 *
 * @param[in]     ekfOrderN_in
 *                Order of the EKF. This represents the number of elements in
 *                the state vector.
 *
 * @param[in]     ekfDegreeM_in
 *                Order of the EKF. This represents the number of elements in
 *                the measurement vector.
 *
 * @param[in,out] p_stateCorrection_out
 *                Pointer containing the address othe updated state estimation
 *
 * @return        Upon successful completion of function, a GCONST_TRUE will be
 *                returned. Upon an unsuccessful completion, a GCONST_FALSE will
 *                be returned.
 */
extern int ContinuousEkf_stateCorrection(double *p_kalmanGain_in,
                                         double *p_sensorMeasurement_in,
                                         double *p_measurementEstimation_in,
                                         double *p_stateJacobian_in,
                                         uint8_t ekfOrderN_in,
                                         uint8_t ekfDegreeM_in,
                                         double *p_stateCorrection_inout);

/*!
 * @brief         Function which will apply eulers integration to step the
 *                error covariance from the error covariance derivitive.
 *
 * @param[in]     p_errorCovarianceDerivitive_in
 *                Pointer containing the address of the error covariance
 *                derivitive matrix.
 *
 *                This array should have dimensions of
 *                [ekfOrderN_in x ekfOrderN_in]
 *
 * @param[in]     timeStep_s_in
 *                Change in time since last EKF call.
 *
 * @param[in]     ekfOrderN_in
 *                Order of the EKF. This represents the number of elements in
 *                the state vector.
 *
 * @param[in,out] p_errorCovariance_inout
 *                Pointer containing error covariance at current timestep. The
 *                change in error covariance will be calculated fromt the
 *                derivitive and time step, beore being summed with this matrix.
 *
 * @return        Upon successful completion of function, a GCONST_TRUE will be
 *                returned. Upon an unsuccessful completion, a GCONST_FALSE will
 *                be returned.
 */
extern int ContinuousEkf_stepCovariance(double *p_errorCovarianceDerivitive_in,
                                        double  timeStep_s_in,
                                        uint8_t ekfOrderN_in,
                                        double *p_errorCovariance_inout);

#ifdef __cplusplus
}
#endif
#endif /* H_CONTINUOUSEKF_PRIVATEFUNCTIONS_H */