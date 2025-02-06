/*!
 *    @File:         Gyro_PublicFunctions.h
 *
 *    @Brief:        Header file which contains the public functions definitions
 *                   for sun sensor.
 *
 *    @Date:         05/02/2025
 *
 */

#ifndef H_GYRO_PUBLICFUNCTIONS_H
#define H_GYRO_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "Gyro/DataStructs/Gyro_ParamsStruct.h"
#include "Gyro/DataStructs/Gyro_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which will load parameters into params struct and
 *              initialise the archive in the state struct.
 *
 * @param[in]   p_gyroParamFilename_in
 *              String containing the filename of the parameters ini file. These
 *              parameters will be loaded into the Gyro.
 *
 * @param[in]   p_gyro_params_out
 *              Pointer containing address of the params struct for the gyro
 *              sensor.
 *
 * @param[in]   p_gyro_state_out
 *              Pointer containing the address for the state struct of the gyro
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
extern int Gyro_init(const char  *p_gyroParamFilename_in,
                     Gyro_Params *p_gyro_params_out,
                     Gyro_State  *p_gyro_state_out,
                     const char  *p_sensorBody_in);

/*!
 * @brief       Function which will step the sun sensor, filling up the
 *              Gyro_State struct with masurement values.
 *
 * @param[in]   p_gyro_params_in
 *              Pointer containing the address of a gyro params struct.
 *
 * @param[out]  p_gyro_state_out
 *              Pointer containing the address of a gyro state struct.
 *
 * @param[in]   p_angularVelocity_Fix_rads_in
 *              Pointer containing the address of angular velocity vector
 *              in the fix frame.
 *
 * @param[in]   p_quaternion_FixToBod_in
 *              Pointer containing the address of quaternion representing the
 *              rotation from fix to body frame.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE.
 */
extern int Gyro_step(Gyro_Params *p_gyro_params_in,
                     Gyro_State  *p_gyro_state_out,
                     double      *p_angularVelocity_Fix_rads_in,
                     double      *p_quaternion_FixToBod_in);

#ifdef __cplusplus
}
#endif
#endif /* H_GYRO_PUBLICFUNCTIONS_H */