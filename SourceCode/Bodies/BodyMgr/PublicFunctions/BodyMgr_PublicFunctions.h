/*
 *    @File:         BodyMgr_PublicFunctions.h
 *
 *    @Brief:        Public Functions for BodyMgr
 *
 *    @Date:         31/05/2024
 *
 */

#ifndef H_BODYMGR_PUBLIC_FUNCTIONS_H
#define H_BODYMGR_PUBLIC_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which will return the address of the struct of a
 *              celestial body from bodyMgr_state struct with the same name
 *              as the inputted string.
 *
 * @param[in]   p_bodyMgr_state_in
 *              Pointer containing the address of bodyMgr_state struct with the
 *              bodies loaded into it.
 *
 * @param[out]  p_celestialBody_state_out
 *              Pointer which will contain the address of a pointer which
 *              contains the address of the body will be stored once found. The
 *              reason it has to be a pointer of a pointer is if it is just a
 *              pointer the output will not be stored.
 *
 * @param[in]   p_bodyName
 *              String with the name of the body.
 *
 * @return      If GCONST_TRUE is returned, a body was found successfully with
 *              the corresponding name. If GCONST_FALSE was returned, no body
 *              with the coresponding name was found.
 */
extern int
    BodyMgr_findCelestialBody(BodyMgr_State        *p_bodyMgr_state_in,
                              CelestialBody_State **p_celestialBody_state_out,
                              const char           *p_bodyName);

/*!
 * @brief       Function which will return the address of the struct of a
 *              satellite body from bodyMgr_state struct with the same name
 *              as the inputted string.
 *
 * @param[in]   p_bodyMgr_state_in
 *              Pointer containing the address of bodyMgr_state struct with the
 *              bodies loaded into it.
 *
 * @param[out]  p_satelliteBody_state_out
 *              Pointer which will contain the address of a pointer which
 *              contains the address of the body will be stored once found. The
 *              reason it has to be a pointer of a pointer is if it is just a
 *              pointer the output will not be stored.
 *
 * @param[in]   p_bodyName
 *              String with the name of the body.
 *
 * @return      If GCONST_TRUE is returned, a body was found successfully with
 *              the corresponding name. If GCONST_FALSE was returned, no body
 *              with the coresponding name was found.
 */
int BodyMgr_findSatelliteBody(BodyMgr_State        *p_bodyMgr_state_in,
                              SatelliteBody_State **p_satelliteBody_state_out,
                              const char           *p_bodyName);

/*!
 * @brief       This inits the BogyMgr state struct. It will open the parameter
 *              file which contains the names of the bodies and the type of body
 *              that is is. From this it will then initialize the bodies and
 *              save the addresses of the bodies to an array of pointers. These
 *              array's are assigned memory on the heap.
 *
 * @param[out]  p_bodyMgr_state_out
 *              Pointer to BodyMgr state struct to initialize
 *
 * @param[in]   p_bodyMgrFilename
 *              String containing the dircetory to ini file which contains the
 *              parameters for BodyMgr.
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int BodyMgr_init(BodyMgr_State *p_bodyMgr_state_out,
                        const char    *p_bodyMgrFilename);

/*!
 * @brief       Function which will step all the bodies during the simulation.
 *
 * @param[in]   p_bodyMgr_state_in
 *              Pointer containing the address of the body manager state struct
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int BodyMgr_step(BodyMgr_State *p_bodyMgr_state_in);

/*!
 * @brief       Function which terminates all the bodies and releases memory
 *              assigned on the heap.
 *
 * @param[in]   p_bodyMgr_state_in
 *              Pointer to BodyMgr state struct to initialize
 *
 * @return      On a successful completion, will return a GCONST_TRUE. If
 *              execution of function fails, will return a GCONST_FALSE.
 */
extern int BodyMgr_terminate(BodyMgr_State *p_bodyMgr_state_in);

#ifdef __cplusplus
}
#endif
#endif /* H_BODYMGR_PUBLIC_FUNCTIONS_H */
