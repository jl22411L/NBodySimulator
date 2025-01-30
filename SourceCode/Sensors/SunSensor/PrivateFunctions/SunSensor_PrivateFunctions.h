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
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "SunSensor/DataStructs/SunSensor_ParamsStruct.h"
#include "SunSensor/DataStructs/SunSensor_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Private function which will write the data for the time step
 *                to the archive folder.
 *
 * @param[in]     p_sunSensor_state_in
 *                Pointer containing the address of the Sun Sensor state struct
 *                with the data to be archived.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int SunSensor_archiveData(SunSensor_State *p_sunSensor_state_in);

/*!
 * @brief         Function which checks to see if the sun sensor is blocked by
 *                any of the celestial bodies.
 *
 * @param[in]     p_sunPosition_Fix_m_in
 *                Pointer containing address of vector which contains the sun
 *                position in the fixed frame.
 *
 * @param[in]     p_bodyPosition_Fix_m_in
 *                Pointer containing the address of vector which contains the
 *                position of the satellite in the fixed frame.
 *
 * @param[in]     p_celestialBodyList_in
 *                Pointer containing the address of the list of celestial bodies
 *                which will be checked to see if blocking the sun.
 *
 * @param[in]     nCelestialBodies_in
 *                Integer containing the number of celestial bodies in list.
 *
 * @param[out]    p_isSensorBlockedFlag_out
 *                Pointer to flag which will be set to true if the sensor if
 *                being blocked by a celestial body or false if it is not.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int
    SunSensor_checkForBlocking(double               *p_sunPosition_Fix_m_in,
                               double               *p_bodyPosition_Fix_m_in,
                               CelestialBody_State **p_celestialBodyList_in,
                               int                   nCelestialBodies_in,
                               uint8_t              *p_isSensorBlockedFlag_out);

/*!
 * @brief         Function which checks if the sun vector is within the FOV of
 *                the sensor. This looks at the true sun vector in the sensor
 *                frame and sees the angle between the vector and the x axis is
 *                less than the FOV of the sensor. If it is, then he invalid
 *                flag does not change, otherwise it gets set to GCONST_TRUE.
 *
 * @param[inout]  p_sunSensor_state_inout
 *                Pointer containing the address of the SunSensor State struct.
 *
 * @param[in]     p_sunSensor_params_in
 *                Pointer containing the address of the SunSensor Params struct.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int SunSensor_checkWithinFov(SunSensor_State  *p_sunSensor_state_inout,
                                    SunSensor_Params *p_sunSensor_params_in);

/*!
 * @brief         Private function which will create the archives for the sun
 *                sensor. Will create the archive wihtin the body that the
 *                sensor belongs to.
 *
 * @param[in]     p_sunSensor_params_in
 *                Pointer containing the address of params struct for sun
 * sensor.
 *
 * @param[in]     p_sunSesor_state_in
 *                Pointer containing the address of state struct of sensor.
 *
 * @param[in]     p_sensorBody_in
 *                String with the name of the body which.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int SunSensor_createArchives(SunSensor_Params *p_sunSensor_params_in,
                                    SunSensor_State  *p_sunSesor_state_in,
                                    const char       *p_sensorBody_in);

#ifdef __cplusplus
}
#endif
#endif /* H_SUNSENSOR_PRIVATEFUNCTIONS_H */