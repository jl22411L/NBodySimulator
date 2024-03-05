/*
 *    @File:         GUtilities_PublicFunctions.h
 *
 *    @ Brief:       Header files that contains the declaration for GUtilities
 *
 *    @ Date:        28/01/2024
 *
 */

#ifndef H_GUTILITIES_PUBLICFUNCTIONS_H
#define H_GUTILITIES_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "GUtilities/DataStructs/GUtilities_StateStructs.h"

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which initilises the Utilities structure and loads
 *              parameters into the Utilities structure to be used by the
 *              simulation.
 *
 * @param[in]   p_paramsFilePath
 *              File path to ini file which contains utility parameters for the
 *              simulation
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
 */
extern int GUtilities_init(const char *p_paramsFilePath);

#ifdef __cplusplus
}
#endif

#endif /*  H_GUTILITIES_PUBLICFUNCTIONS_H */
