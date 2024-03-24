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
extern int CelestialBody_init(
    CelestialBody_State *p_celestialBody_state_in,
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
