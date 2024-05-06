/*
 *    @File:         CelestialBody_PrivateFunctions.h
 *
 *    @ Brief:       Contains the private functions for the satellite body.
 *
 *    @ Date:        17/03/2024
 *
 */

#ifndef H_CELESTIALBODY_PRIVATEFUNCTIONS_H
#define H_CELESTIALBODY_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Generic Libraries */
/* None */

/*!
 * @brief       Creates the archive for the Celestial Body
 *
 * @param[in]   p_celestialBody_state_in
 *              Pointer containing the address to the satellite body which the
 *              archive will be created.
 *
 * @param[in]   p_bodyName_in
 *              String containing the name of the body
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the
 *              execution of the script.
 */
extern int CelestialBody_createArchives(
    CelestialBody_State *p_celestialBody_state_in,
    const char          *p_bodyName_in);

/*!
 * @brief       Function which takes all the forces from a Celestial body and
 *              finds the resultant force on the body.
 *
 * @param[in]   p_celestialBody_state_in
 *              Pointer to the UAV body struct which the resultant force will
 *              be applied to.
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the
 *              execution of the script.
 */
extern int CelestialBody_findResultantForce(
    CelestialBody_State *p_celestialBody_state_in);

#ifdef __cplusplus
}
#endif

#endif /* H_CELESTIALBODY_PRIVATEFUNCTIONS_H */
