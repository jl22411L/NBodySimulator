/*
 *    @File:         Igrf_PublicFunctions.h
 *
 *    @Brief:        Contains the public functions for the Igrf library
 *
 *    @Date:         11/09/2024
 *
 */

#ifndef H_IGRF_PUBLICFUNCTIONS_H
#define H_IGRF_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which will load the IGRF model from the params .ini
 *              file. This will load the parameter to find the epoch data and
 *              the degree of freedom which to load the parameters for. The
 *              struct which is inputted into the function will be loaded with
 *              the coefficients for the epoch time.
 *
 * @param[in]   p_igrfParams_in
 *              Pointer containing the adress of an IGRF params struct. This
 *              struct will have its params loaded into.
 *
 * @param[in]   p_paramsFilePath_in
 *              Pointer to a string containing the name of .ini file which
 *              contains the parameters for the IGRF model.
 *
 * @return      GCONST_TRUE is returned upon the successful completion of the
 *              function. GCONST_FALSE is returned to indicate that an error has
 *              occured which prohibits the software from going further.
 */
extern int
    Igrf_init(Igrf_Params *p_igrfParams_in, const char *p_paramsFilePath_in);

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_PUBLICFUNCTIONS_H */
