/*
 *    @File:         JamSail_PublicFunctions.h
 *
 *    @Brief:        Header file containing the public functions for JamSail.
 *
 *    @Date:         02/08/2024
 *
 */

#ifndef H_JAMSAIL_PUBLICFUNCTIONS_H
#define H_JAMSAIL_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       This function will init the JamSail body, loading all the
 *              parameters it will need to run its operation.
 *
 * @param[in]   p_jamSail_state_in
 *              Pointer containing the address of the struct which contains
 *              JamSail. This will be used to init JamSail
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int JamSail_init(JamSail_State *p_jamSail_state_in);

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_PUBLICFUNCTIONS_H */
