/*!
 *    @File:         Magnetorquer_PublicFunctions.h
 *
 *    @Brief:        Header file containing all the public functions for the
 *                   magnetorquer.
 *
 *    @Date:         10/02/2025
 *
 */

#ifndef H_MAGNETORQUER_PUBLICFUNCTIONS_H
#define H_MAGNETORQUER_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_ParamsStruct.h"
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Function which will initialize the magnetorquer model.
 *
 * @param[in]     p_magnetorquerParamFilename_in
 *                String to parameters ini file containing the parameters for
 *                magnetorquer.
 *
 * @param[out]    p_magnetorquer_params_out
 *                Pointer containing address of pointer params struct for
 *                magnetorquer.
 *
 * @param[out]    p_magnetorquer_state_out
 *                Pointer containing address of pointer state struct for
 *                magnetorquer.
 *
 * @param[in]     p_actuatorBody_in
 *                String of the name of the body the magnetorquer belongs to.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Magnetorquer_init(const char *p_magnetorquerParamFilename_in,
                             Magnetorquer_Params *p_magnetorquer_params_out,
                             Magnetorquer_State  *p_magnetorquer_state_out,
                             const char          *p_actuatorBody_in);

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETORQUER_PUBLICFUNCTIONS_H */