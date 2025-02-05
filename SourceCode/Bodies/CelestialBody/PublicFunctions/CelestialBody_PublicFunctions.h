/*
 *    @File:         CelestialBody_PublicFunctions.h
 *
 *    @ Brief:       Contains public functions for the CelestialBody module
 *
 *    @ Date:        17/03/2024
 *
 */

#ifndef H_CELESTIALBODY_PUBLICFUNCTIONS_H
#define H_CELESTIALBODY_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Writes to archive csv file data from CelestialBody Struct
 *
 * @param[in]   p_celestialBody_state_in
 *              Pointer containing the address of the celestial body struct.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int
    CelestialBody_archiveData(CelestialBody_State *p_celestialBody_state_in);

/*!
 * @brief       Function which will find the simulated rotated angle of the body
 *              alng with the theoretical angle. This should be used in specific
 *              situations where you want to make sure that the rotation of the
 *              Geo-Centric frame from the Inertical Centric frame is within a
 *              tolerance.
 *
 *              To find the theoretical rotation, the amount of time since J2000
 *              is found which is then used to find the angle rotated by the
 *              body. Hence, the simTime_s_in must be in UNIX time.
 *
 * @param[in]   p_quaternion_InertCenToGeoCen_in
 *              Pointer containing address of quaternion which represents the
 *              rotation from inertial centrc frame to geo centric frame.
 *
 * @param[in]   celestialBodySideRealTime_s_in
 *              Sidereal time of body in seconds. This is the time it takes for
 *              the body to perform a full 360 degree rotation.
 *
 * @param[in]   simTime_s_in
 *              Unix time of simulation.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int
    CelestialBody_checkRotationAngle(double *p_quaternion_InertCenToGeoCen_in,
                                     double  celestialBodySideRealTime_s_in,
                                     double  simTime_s_in);

/*!
 * @brief       Initialises the satellite body, loading parameters and creating
 *              archives.
 *
 * @param[in]   p_celestialBody_state_in
 *              Pointer containing the address of the Celestial Body Struct
 *
 * @param[in]   p_paramFilename_in
 *              Pointer containing the address of the Celestial Body Struct
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int CelestialBody_init(CelestialBody_State *p_celestialBody_state_in,
                              const char          *p_paramFilename_in);

/*!
 * @brief       Steps the satellite body during simulation.
 *
 * @param[in]   p_celestialBody_state_in
 *              Pointer containing the address of the satellite body.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int CelestialBody_step(CelestialBody_State *p_celestialBody_state_in);

/*!
 * @brief       Closes archives related to satellite body.
 *
 * @param[in]   p_celestialBody_state_in
 *              Pointer containing the address of satellite body struct
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int
    CelestialBody_terminate(CelestialBody_State *p_celestialBody_state_in);

#ifdef __cplusplus
}
#endif

#endif /* H_CELESTIALBODY_PUBLICFUNCTIONS_H */
