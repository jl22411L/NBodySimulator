/*!
 *    @File:         Magnetometer_PrivateFunction.h
 *
 *    @Brief:        Header file containing the private functions for
 *                   magnetometer sensor.alignas
 *
 *    @Date:         30/01/2025
 *
 */

#ifndef H_MAGNETOMETER_PRIVATEFUNCTION_H
#define H_MAGNETOMETER_PRIVATEFUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Magnetometer/DataStructs/Magnetometer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Function which will create archives for magnetometer sensor.
 *                Will create the archive wihtin the body that the sensor
 *                belongs to.
 *
 * @param[in]     p_magnetometer_params_in
 *                Pointer containing the address of params struct for
 *                magnetometer.
 *
 * @param[in]     p_magnetometer_state_in
 *                Pointer containing the address of state struct of
 *                magnetometer.
 *
 * @param[in]     p_sensorBody_in
 *                String with the name of the body which.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int
    Magnetometer_createArchives(Magnetometer_Params *p_magnetometer_params_in,
                                Magnetometer_State  *p_magnetometer_state_in,
                                const char          *p_sensorBody_in);

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETOMETER_PRIVATEFUNCTION_H */