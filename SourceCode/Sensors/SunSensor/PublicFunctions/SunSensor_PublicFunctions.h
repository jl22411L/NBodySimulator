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
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "SunSensor/DataStructs/SunSensor_ParamsStruct.h"
#include "SunSensor/DataStructs/SunSensor_StateStruct.h"

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

/*!
 * @brief       Function which will step the sun sensor, filling up the
 *              SunSensor_State struct with masurement values.
 *
 * @param[in]   p_bodyPosition_Fix_m_in
 *              Pointer containing the address of the vector representing the
 *              position of the satellite in the fixed frame.
 *
 * @param[in]   p_quaternion_FixToBod_in
 *              Pointer containing the address of quaterion which represents the
 *              attitude of satellite from fixed frame to body frame.
 *
 * @param[in]   p_sunCelestialBody_in
 *              Pointer containing address to celestial body of the sun.
 *
 * @param[in]   p_bodyMgr_state
 *              Pointer contaiing the address of BodyMgr state struct.
 *
 * @param[in]   p_sunSensor_params_in
 *              Pointer containing the address to SunSensor Params struct.
 *
 * @param[out]  p_sunSensor_state_out
 *              Pointer containing the address to SunSensor State struct.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE.
 */
extern int SunSensor_step(double              *p_bodyPosition_Fix_m_in,
                          double              *p_quaternion_FixToBod_in,
                          CelestialBody_State *p_sunCelestialBody_in,
                          BodyMgr_State       *p_bodyMgr_state,
                          SunSensor_Params    *p_sunSensor_params_in,
                          SunSensor_State     *p_sunSensor_state_out);

#ifdef __cplusplus
}
#endif
#endif /* H_SUNSENSOR_PUBLICFUNCTIONS_H */