/*
 *    @File:         UavBody_PublicFunctions.h
 *
 *    @ Brief:       Contains public functions for the UavBody module
 *
 *    @ Date:        02/05/2024
 *
 */

#ifndef H_UAVBODY_PUBLICFUNCTIONS_H
#define H_UAVBODY_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Writes to archive csv file data from UavBody Struct
 *
 * @param[in]   p_uavBody_state_in
 *              Pointer containing the address of the uav body struct.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int UavBody_archiveData(UavBody_State *p_uavBody_state_in);

/*!
 * @brief       Initialises the uav body, loading parameters and creating
 *              archives.
 *
 * @param[in]   p_uavBody_state_in
 *              Pointer containing the address of the Uav Body Struct
 *
 * @param[in]   p_paramFilename_in
 *              Pointer containing the address of the Uav Body Struct
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int UavBody_init(
    UavBody_State *p_uavBody_state_in,
    const char    *p_paramFilename_in);

/*!
 * @brief       Steps the satellite body during simulation.
 *
 * @param[in]   p_uavBody_state_in
 *              Pointer containing the address of the satellite body.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int UavBody_step(UavBody_State *p_uavBody_state_in);

/*!
 * @brief       Closes archives related to satellite body.
 *
 * @param[in]   p_uavBody_state_in
 *              Pointer containing the address of uav body struct
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int UavBody_terminate(UavBody_State *p_uavBody_state_in);

#ifdef __cplusplus
}
#endif

#endif /* H_UAVBODY_PUBLICFUNCTIONS_H */
