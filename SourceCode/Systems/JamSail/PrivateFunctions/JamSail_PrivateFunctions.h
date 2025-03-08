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
 * @brief         Private function which will perform the attitude determination
 *                algorithm for JamSail.
 *
 * @param[in,out] p_jamSail_state_out
 *                Pointer containing the address of the struct which contains
 *                JamSail. This function will load the members of the struct.
 *
 * @param[in]     p_jamSail_params_in
 *                Pointer to the params struct of JamSail whose members will be
 *                filled.
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
                                         double          timeStep_s_in);

/*!
 * @brief         Private function which will esitimate the attitude of JamSail
 *
 * @param[in,out] p_jamSail_state_out
 *                Pointer containing the address of the struct which contains
 *                JamSail. This function will load the members of the struct.
 *
 * @param[in]     p_jamSail_params_in
 *                Pointer to the params struct of JamSail whose members will be
 *                filled.
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

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_PRIVATEFUNCTIONS_H */