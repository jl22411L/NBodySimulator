/*
 *    @File:         SunSensor_PublicFunctions.h
 *
 *    @Brief:        Header file which contains the public functions definitions
 *                   for sun sensor.
 *
 *    @Date:         11/11/2024
 *
 */

#ifndef H_SUNSENSOR_PUBLICFUNCTIONS_H
#define H_SUNSENSOR_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "SunSensor/DataStructs/SunSensor_Params.h"
#include "SunSensor/DataStructs/SunSensor_State.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which will load parameters into params struct and
 *              initialise the archive in the state struct.
 *
 * @param[in]   p_sunSensorParamFilename_in
 *              String containing the filename of the parameters ini file. These
 *              parameters will be loaded into the SunSensor.
 *
 * @param[in]   p_sunSensor_params_out
 *              Pointer containing address of the params struct for the sun
 *              sensor.
 *
 * @param[in]   p_sunSesor_state_out
 *              Pointer containing the address for the state struct of the sun
 *              sensor.
 *
 * @param[in]   p_sensorBody_in
 *              String for the body which the sensor belongs to. This is so
 *              the sensor can archived with the appropriate body.
 *
 *              Note: If the sensor does not belong to a body, passing an empty
 *                    string as an input "", will cause the archive to be
 *                    initialised in the root Archive directory.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE.
 */
extern int SunSensor_init(const char       *p_sunSensorParamFilename_in,
                          SunSensor_Params *p_sunSensor_params_out,
                          SunSensor_State  *p_sunSesor_state_out,
                          const char       *p_sensorBody_in);

#ifdef __cplusplus
}
#endif
#endif /* H_SUNSENSOR_PUBLICFUNCTIONS_H */