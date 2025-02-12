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
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

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

/*!
 * @brief         Function which will step the actuator and find the resultant
 *                torque on the body.
 *
 * @param[out]    p_magnetorquer_state_out
 *                Pointer containing the address of a magnetorquer state struct.
 *
 * @param[in]     p_magnetorquer_params_in
 *                Pointer containing the address of a magnetorquer params
 * struct.
 *
 * @param[in]     p_igrf_params_in
 *                Pointer containing the address of an IGRF params struct.
 *
 * @param[in]     p_magneticFieldCelestialBody_in
 *                Pointer containing the address of celestial body state struct
 *                which represents the celestial body producing magnetic field.
 *                This should correspond to the IGRF params struct.
 *
 * @param[in]     p_bodyPosition_Fix_m_in
 *                Pointer containing address of array which represents the
 *                position of the body in the fix frame.
 *
 * @param[in]     p_quaternionToBody_FixToBod_in
 *                Pointer containing address of array which represents the
 *                quaternion indicating the attitude rotation from the fix frame
 *                to the body frame.
 *
 * @param[in]     simTime_s_in
 *                Double which indicates the simulation time in UNIX time.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int
    Magnetorquer_step(Magnetorquer_State  *p_magnetorquer_state_out,
                      Magnetorquer_Params *p_magnetorquer_params_in,
                      Igrf_Params         *p_igrf_params_in,
                      CelestialBody_State *p_magneticFieldCelestialBody_in,
                      double              *p_bodyPosition_Fix_m_in,
                      double              *p_quaternionToBody_FixToBod_in,
                      double               simTime_s_in);

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETORQUER_PUBLICFUNCTIONS_H */