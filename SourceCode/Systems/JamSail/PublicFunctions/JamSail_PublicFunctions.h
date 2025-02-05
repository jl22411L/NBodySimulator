/*
 *    @File:         JamSail_PublicFunctions.h
 *
 *    @Brief:        Header file containing the public functions for JamSail.
 *
 *    @Date:         02/08/2024
 *
 */

#ifndef H_JAMSAIL_PUBLICFUNCTIONS_H
#define H_JAMSAIL_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       This function will init the JamSail body, loading all the
 *              parameters it will need to run its operation.
 *
 * @param[out]  p_jamSail_state_in
 *              Pointer containing the address of the struct which contains
 *              JamSail. This function will load the members of the struct.
 *
 * @param[out]  p_jamSail_params_out
 *              Pointer to the params struct of JamSail whose members will be
 *              filled.
 *
 * @param[in]   p_bodyMgr_state_in
 *              Pointer containing the address of an initialized BodyMgr_State
 *              struct. The address of the satelliite body within the
 *              BodyMgr_State struct that corresponds to JamSail will be found
 *              and stored in the approporate member of JamSail_State struct.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int JamSail_init(JamSail_State  *p_jamSail_state_out,
                        JamSail_Params *p_jamSail_params_out,
                        BodyMgr_State  *p_bodyMgr_state_in);

/*!
 * @brief       Function which will step JamSail forward along with all its
 *              sensors.
 *
 * @param[out]  p_jamSail_state_out
 *              Pointer containing the address of JamSail state struct.
 *
 * @param[in]   p_jamSail_params_in
 *              Pointer contaiing the address of JamSail params struct.
 *
 * @param[in]   p_bodyMgr_state_in
 *              Pointer containing the address of bodyMgr state struct.
 *
 * @param[in]   p_igrf_params_in
 *              Pointer contaiing the address of IGRF params struct.
 *
 * @param[in]   simTime_s_in
 *              Time of simulation in Unix time in seconds.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int JamSail_step(JamSail_State  *p_jamSail_state_out,
                        JamSail_Params *p_jamSail_params_in,
                        BodyMgr_State  *p_bodyMgr_state_in,
                        Igrf_Params    *p_igrf_params_in,
                        double          simTime_s_in);

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_PUBLICFUNCTIONS_H */
