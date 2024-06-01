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
extern int BodyMgr_init(
    BodyMgr_State *p_bodyMgr_state_out,
    const char    *p_bodyMgrFilename);

#ifdef __cplusplus
}
#endif
#endif /* H_BODYMGR_PUBLIC_FUNCTIONS_H */
