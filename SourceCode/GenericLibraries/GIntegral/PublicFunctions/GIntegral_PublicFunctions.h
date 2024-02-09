/*
 *    @File:         GIntegral_PublicFunctions.h
 *
 *    @ Brief:       Contains public functions for GIntegral module
 *
 *    @ Date:        29/01/2024
 *
 */

#ifndef H_GINTEGRAL_PUBLICFUNCTIONS_H
#define H_GINTEGRAL_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief Function which integrates an array of size 3x1. It applied Euler
 *        method to integrate.
 *
 * @param[inout]    p_array_inout
 *                  Array which is integrated
 *
 * @param[in]       p_arrayDerivitive_in
 *                  Array containing the derivitive of of the array.
 *
 * @param           timeStep_in
 *                  Time step to integrate the value
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GIntegral_3x1Double(
    double *p_array_inout,
    double *p_arrayDerivitive_in,
    double  timeStep_in);

/*!
 * @brief Function which integrates an array of size 3x1. It applied Euler
 *        method to integrate.
 *
 * @param[inout]    p_array_inout
 *                  Array which is integrated
 *
 * @param[in]       p_arrayDerivitive_in
 *                  Array containing the derivitive of of the array.
 *
 * @param           timeStep_in
 *                  Time step to integrate the value
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GIntegral_4x1Double(
    double *p_array_inout,
    double *p_arrayDerivitive_in,
    double  timeStep_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GINTEGRAL_PUBLICFUNCTIONS_H */