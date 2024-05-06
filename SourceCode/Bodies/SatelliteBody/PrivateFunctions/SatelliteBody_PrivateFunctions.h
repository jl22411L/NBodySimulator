/*
 *    @File:         SatelliteBody_PrivateFunctions.h
 *
 *    @ Brief:       Contains the private functions for the satellite body.
 *
 *    @ Date:        09/03/2024
 *
 */

#ifndef H_SATELLITEBODY_PRIVATEFUNCTIONS_H
#define H_SATELLITEBODY_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Generic Libraries */
/* None */

/*!
 * @brief       Creates the archive for the Satellite Body
 *
 * @param[in]   p_satelliteBody_state_in
 *              Pointer containing the address to the satellite body which the
 *              archive will be created.
 *
 * @param[in]   p_bodyName_in
 *              String containing the name of the body
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the
 *              execution of the script.
 */
extern int SatelliteBody_createArchives(
    SatelliteBody_State *p_satelliteBody_state_in,
    const char          *p_bodyName_in);

/*!
 * @brief       Function which takes all the forces from a Satellite body and
 *              finds the resultant force on the body.
 *
 * @param[in]   p_satelliteBody_state_in
 *              Pointer to the Satellite body struct which the resultant force
 *              will be applied to.
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the
 *              execution of the script.
 */
extern int
    UavBody_findResultantForce(SatelliteBody_State *p_satelliteBody_state_in);

#ifdef __cplusplus
}
#endif

#endif /* H_SATELLITEBODY_PRIVATEFUNCTIONS_H */
