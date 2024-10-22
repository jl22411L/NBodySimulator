/*
 *    @File:         Igrf_PrivateFunctions.h
 *
 *    @Brief:        Header file containing the private functions for IGRF
 *                   module.
 *
 *    @Date:         21/10/2024
 *
 */

#ifndef H_IGRF_PRIVATEFUNCTIONS_H
#define H_IGRF_PRIVATEFUNCTIONS_H

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
 * @brief       Function which will apply the quasi-schmidt normalisation to the
 *              gaussian coefficients and their linear rate. This is to reduce
 *              the amount of computation required when finding the magnetic
 *              field vector in the loop. This way, only the associated legendre
 *              polynomial needs to be calucalted in the loop without
 *              normalising them at each time step.
 *
 * @param[out]  p_igrf_params_out
 *              Pointer to an Igrf_Params struct which has the gaussian
 *              coefficients and linear rates loaded in.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int Igrf_applyNormalisation(Igrf_Params *p_igrf_params_out);

/*!
 * @brief       Function which loads the gaussian coefficients and linear rates,
 *              for a particular iteration of the IGRF model, into a Igrf_Params
 *              struct.
 *
 * @param[out]  p_igrf_params_out
 *              Pointer to an Igrf_Params struct which will have the gaussian
 *              coefficients and linear rates loaded into.
 *
 * @param[in]   p_paramsFilePath_in
 *              String which containst the filepath to the Igrf.ini params file.
 *
 * @param[in]   nMaxDegree_in
 *              Integer representing the maximum degree of the IGRF model which
 *              will be laoded.
 *
 * @param[in]   igrfIteration_in
 *              Integer representing the iteration of the IGRF model to be
 *              loaded.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int Igrf_loadParams(Igrf_Params *p_igrf_params_out,
                           const char  *p_paramsFilePath_in,
                           uint8_t      nMaxDegree_in,
                           uint8_t      igrfIteration_in);

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_PRIVATEFUNCTIONS_H */
