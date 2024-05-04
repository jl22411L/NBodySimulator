/*
 *    @File:         UavBody_PrivateFunctions.h
 *
 *    @ Brief:       Contains the private functions for the uav body.
 *
 *    @ Date:        02/05/2024
 *
 */

#ifndef H_UAVBODY_PRIVATEFUNCTIONS_H
#define H_UAVBODY_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which takes all the forces from a UAV body and finds
 *              the resultant force on the body.
 *
 * @param[in]   p_uavBody_state_in
 *              Pointer to the UAV body struct which the resultant force will
 *              be applied to.
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the
 *              execution of the script.
 */
extern int UavBody_findResultantForce(UavBody_State *p_uavBody_state_in);

/*!
 * @brief       Creates the archive for the UAV Body
 *
 * @param[in]   p_uavBody_state_in
 *              Pointer containing the address to the uav body which the
 *              archive will be created.
 *
 * @param[in]   p_bodyName_in
 *              String containing the name of the body
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the
 *              execution of the script.
 */
extern int UavBody_createArchives(
    UavBody_State *p_uavBody_state_in,
    const char    *p_bodyName_in);

#ifdef __cplusplus
}
#endif

#endif /* H_UAVBODY_PRIVATEFUNCTIONS_H */
