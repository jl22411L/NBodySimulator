/*
 *    @File:         SatelliteBody_PublicFunctions.h
 *
 *    @ Brief:       Contains public functions for the SatelliteBody module
 *
 *    @ Date:        22/02/2024
 *
 */

#ifndef H_SATELLITEBODY_PUBLICFUNCTIONS_H
#define H_SATELLITEBODY_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Writes to archive csv file data from SatelliteBody Struct
 *
 * @param[in]   p_satelliteBody_state_in
 *              Pointer containing the address of the satellite body struct.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int
    SatelliteBody_archiveData(SatelliteBody_State *p_satelliteBody_state_in);

/*!
 * @brief       Initialises the satellite body, loading parameters and creating
 *              archives.
 *
 * @param[in]   p_satelliteBody_state_in
 *              Pointer containing the address of the Satellite Body Struct
 *
 * @param[in]   p_paramFilename_in
 *              Pointer containing the address of the Satellite Body Struct
 *
 * @param[in]   p_bodyName_in
 *              Pointer containing the address of the Satellite Body Struct
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int SatelliteBody_init(
    SatelliteBody_State *p_satelliteBody_state_in,
    const char          *p_paramFilename_in,
    const char          *p_bodyName_in);

/*!
 * @brief       Steps the satellite body during simulation.
 *
 * @param[in]   p_satelliteBody_state_in
 *              Pointer containing the address of the satellite body.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int SatelliteBody_step(SatelliteBody_State *p_satelliteBody_state_in);

/*!
 * @brief       Closes archives related to satellite body.
 *
 * @param[in]   p_satelliteBody_state_in
 *              Pointer containing the address of satellite body struct
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int
    SatelliteBody_terminate(SatelliteBody_State *p_satelliteBody_state_in);

#ifdef __cplusplus
}
#endif

#endif /* H_SATELLITEBODY_PUBLICFUNCTIONS_H */
