/*!
 *    @File:         JamSail_PrivateFunctions.h
 *
 *    @Brief:        Header file containing the private functions for JamSail.
 *
 *    @Date:         06/03/2025
 *
 */

#ifndef H_JAMSAIL_PRIVATEFUNCTIONS_H
#define H_JAMSAIL_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Private function which will write outputs of JamSails ADCS
 *                algorithm.
 *
 * @param[in]     p_jamSail_state_in
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @param[in]     p_jamSail_params_in
 *                Pointer to the params struct of JamSail filled with correct
 *                coefficients.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int JamSail_archiveData(JamSail_State *p_jamSail_state_in);

/*!
 * @brief         Private function which will perform the attitude determination
 *                algorithm for JamSail.
 *
 * @param[in,out] p_jamSail_state_inout
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @param[in]     p_jamSail_params_in
 *                Pointer to the params struct of JamSail filled with correct
 *                coefficients.
 *
 * @param[in]     timeStep_s_in
 *                Change in time since last call for attitude determination.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int JamSail_attitudeDetermination(JamSail_State  *p_jamSail_state_inout,
                                         JamSail_Params *p_jamSail_params_in,
                                         double          simTim_s_in,
                                         double          timeStep_s_in);

/*!
 * @brief         Private function which will esitimate the attitude of JamSail
 *
 * @param[in,out] p_jamSail_state_inout
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @param[in]     p_jamSail_params_in
 *                Pointer to the params struct of JamSail filled with correct
 *                coefficients.
 *
 * @param[in]     timeStep_s_in
 *                Change in time since last call for attitude determination.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int JamSail_attitudeEstimation(JamSail_State  *p_jamSail_state_inout,
                                      JamSail_Params *p_jamSail_params_in,
                                      double          timeStep_s_in);

/*!
 * @brief         Loads the state, measurement estimation and measurement
 *                sensor vectors for EKF when it is in estimation mode.
 *
 * @param[out]    p_stateEstimateVector_out
 *                Pointer containing address of state estimation vector to be
 *                filled.
 *
 * @param[out]    p_measurementEstimateVector_out
 *                Pointer containing address of measurement estimation vector to
 *                be filled.
 *
 * @param[out]    p_measurementSensorVector_out
 *                Pointer containing address of measurement sensor vector to be
 *                filled.
 *
 * @param[in]     p_jamSail_state_in
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @param[in]     p_jamSail_params_in
 *                Pointer to the params struct of JamSail filled with correct
 *                coefficients.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int
    JamSail_estimationEkfLoadVectors(double *p_stateEstimateVector_out,
                                     double *p_measurementEstimateVector_out,
                                     double *p_measurementSensorVector_out,
                                     JamSail_State  *p_jamSail_state_in,
                                     JamSail_Params *p_jamSail_params_in);

/*!
 * @brief         Fills the observation matrix for the EKF.

 * @param[in]     p_jamSail_state_out
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int JamSail_fillObservationJacobian(JamSail_State *p_jamSail_state_out);

/*!
 * @brief         Function which will fill the state jacobian manually. This
 *                functions code is not by any means pretty but serves the
 *                purpose.
 *
 * @param[out]    p_jamSail_state_out
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @param[in]     xxInertia_Bod_kgm2_in
 *                XX component of inertia matrix of JamSail.
 *
 * @param[in]     yyInertia_Bod_kgm2_in
 *                YY component of inertia matrix of JamSail.
 *
 * @param[in]     zzInertia_Bod_kgm2_in
 *                ZZ component of inertia matrix of JamSail.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int JamSail_fillStateJacobian(JamSail_State *p_jamSail_state_out,
                                     double         xxInertia_Bod_kgm2_in,
                                     double         yyInertia_Bod_kgm2_in,
                                     double         zzInertia_Bod_kgm2_in);

/*!
 * @brief         Function which finds the derivitive of the state vector.
 *
 *                stateVector = [
 *                quaternion_InertCenToBod[0],
 *                quaternion_InertCenToBod[1],
 *                quaternion_InertCenToBod[2],
 *                quaternion_InertCenToBod[3],
 *                angularVelocity_Bod[0],
 *                angularVelocity_Bod[1],
 *                angularVelocity_Bod[2]
 *                ]
 *
 * @param[in]     p_jamSail_state_in
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @param[in]     p_stateVector_in
 *                Pointer to state vector for EKF
 *
 * @param[in]     xxInertia_Bod_kgm2_in
 *                XX component of inertia matrix of JamSail.
 *
 * @param[in]     yyInertia_Bod_kgm2_in
 *                YY component of inertia matrix of JamSail.
 *
 * @param[in]     zzInertia_Bod_kgm2_in
 *                ZZ component of inertia matrix of JamSail.
 *
 * @param[out]    p_stateDerivitiveVector_out
 *                Pointer to derivitve state vector which will be filled.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int JamSail_findStateDerivitive(JamSail_State *p_jamSail_state_in,
                                       double        *p_stateVector_in,
                                       double         xxInertia_Bod_kgm2_in,
                                       double         yyInertia_Bod_kgm2_in,
                                       double         zzInertia_Bod_kgm2_in,
                                       double *p_stateDerivitiveVector_out);

/*!
 * @brief         Private function which will init JamSail's attitude
 *                determination system.
 *
 * @param[out]    p_jamSail_state_out
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @param[out]    p_jamSail_params_out
 *                Pointer to the params struct of JamSail filled with correct
 *                coefficients.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int
    JamSail_initAttitudeDetermination(JamSail_State  *p_jamSail_state_out,
                                      JamSail_Params *p_jamSail_params_out);

/*!
 * @brief         Function which takes the elements from the state vector and
 *                updates the members in the JamSail state struct.
 *
 * @param[in]     p_stateVector_in
 *                Pointer to state vector for EKF
 *
 * @param[out]    p_jamSail_state_in
 *                Pointer containing the address of the struct of JamSail's
 *                state.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int JamSail_updateEstimateMembers(double        *p_stateVector_in,
                                         JamSail_State *p_jamSail_state_out);

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_PRIVATEFUNCTIONS_H */