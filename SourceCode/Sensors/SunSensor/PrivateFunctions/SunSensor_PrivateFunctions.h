/*
 *    @File:         SunSensor_PrivateFunctions.h
 *
 *    @Brief:        Header file which contains the private functions for the
 *                   sun sensor.
 *
 *    @Date:         11/11/2024
 *
 */

#ifndef H_SUNSENSOR_PRIVATEFUNCTIONS_H
#define H_SUNSENSOR_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "SunSensor/DataStructs/SunSensor_ParamsStruct.h"
#include "SunSensor/DataStructs/SunSensor_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Private function which will write the data for the time step
 *              to the archive folder.
 *
 * @param[in]   p_sunSensor_state_in
 *              Pointer containing the address of the Sun Sensor state struct
 *              with the data to be archived.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE.
 */
extern int SunSensor_archiveData(SunSensor_State *p_sunSensor_state_in);

/*!
 * @brief       Private function which will create the archives for the sun
 *              sensor.
 *
 * @param[in]   p_sunSensor_params_in
 *              Pointer containing the address of params struct for sun sensor.
 *
 * @param[in]   p_sunSesor_state_in
 *              Pointer containing the address of state struct of sensor.
 *
 * @param[in]   p_sensorBody_in
 *              String with the name of the body which.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE.
 */
extern int SunSensor_createArchives(SunSensor_Params *p_sunSensor_params_in,
                                    SunSensor_State  *p_sunSesor_state_in,
                                    const char       *p_sensorBody_in);

#ifdef __cplusplus
}
#endif
#endif /* H_SUNSENSOR_PRIVATEFUNCTIONS_H */