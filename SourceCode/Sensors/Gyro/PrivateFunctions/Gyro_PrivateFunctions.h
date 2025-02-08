/*!
 *    @File:         Gyro_PrivateFunctions.h
 *
 *    @Brief:        Header file containing private functions for Gyro model.
 *
 *    @Date:         05/02/2025
 *
 */

#ifndef H_GYRO_PRIVATEFUNCTIONS_H
#define H_GYRO_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Gyro/DataStructs/Gyro_ParamsStruct.h"
#include "Gyro/DataStructs/Gyro_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Private function which will write the data for the time step
 *                to the archive folder.
 *
 * @param[in]     p_gyro_state_in
 *                Pointer containing the address of the Gyro state struct
 *                with the data to be archived.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Gyro_archiveData(Gyro_State *p_gyro_state_in);

/*!
 * @brief         Private functions which creates the archives for Gyro model.
 *                Will create the archive wihtin the body that the sensor
 *                belongs to.
 *
 * @param[in]     p_gyro_params_in
 *                Pointer containing the address of params struct for sun.
 *
 * @param[in]     p_gyro_state_in
 *                Pointer containing the address of state struct of sensor.
 *
 * @param[in]     p_sensorBody_in
 *                String with the name of the body which.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Gyro_createArchives(Gyro_Params *p_gyro_params_in,
                               Gyro_State  *p_gyro_state_in,
                               const char  *p_sensorBody_in);

#ifdef __cplusplus
}
#endif
#endif /* H_GYRO_PRIVATEFUNCTIONS_H */