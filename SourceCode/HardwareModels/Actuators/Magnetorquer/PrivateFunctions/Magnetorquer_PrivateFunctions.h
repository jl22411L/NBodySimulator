/*!
 *    @File:         Magnetorquer_PrivateFunctions.h
 *
 *    @Brief:        Header file containing the Private Functions Definitions
 *                   for Magnetorquer model.
 *
 *    @Date:         10/02/2025
 *
 */

#ifndef H_MAGNETORQUER_PRIVATEFUNCTIONS_H
#define H_MAGNETORQUER_PRIVATEFUNCTIONS_H

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
 * @brief         Function which will create the archives for the magnetorquer
 *                model.
 *
 * @param[in]     p_magnetorquer_params_in
 *                Pointer containing the address of params struct for
 *                magnetorquer.
 *
 * @param[in]     p_magnetorquer_state_in
 *                Pointer containing the address of state struct of
 *                magnetorquer.
 *
 * @param[in]     p_sensorBody_in
 *                String with the name of the body which actuator belongs to.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int
    Magnetometer_createArchives(Magnetorquer_Params *p_magnetorquer_params_in,
                                Magnetorquer_State  *p_magnetorquer_state_in,
                                const char          *p_sensorBody_in);

/*!
 * @brief         Function which will archive data of the magnetorquer.
 *
 * @param[in]     p_magnetorquer_state_in
 *                Pointer containing the address of state struct of
 *                magnetorquer.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int
    Magnetorquer_archiveData(Magnetorquer_State *p_magnetorquer_state_in);
#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETORQUER_PRIVATEFUNCTIONS_H */