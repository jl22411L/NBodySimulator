/*
 *    @File:         GLegendrePoly_PublicFunctions.h
 *
 *    @Brief:        Header file which contains public functions for
 *                   GLegendrePoly module.
 *
 *    @Date:         19/09/2024
 *
 */

#ifndef H_GLEGPOLY_PUBLICFUNCTIONS_H
#define H_GLEGPOLY_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Fills an array of assocaited legendre polynomial coefficients
 *              for a particular input.
 *
 *              NOTE: Function was verified using MATLAB's legendre() function
 *                    and comparing outputs
 *
 * @param[out]  p_assocatedLegPolyArray_out
 *              Pointer containing the address of the array which the associated
 *              legendre pollynomial coefficients.
 *
 * @param[in]   inputValue_in
 *              Input value to find the legendre polynomial coefficients.
 *
 * @param[in]   maxDegreeN_in
 *              Maximum degree to fill out to.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GLegPoly_associatedLegendreArrayPolynomials(
    double *p_assocatedLegPolyArray_out,
    double  inputValue_in,
    uint8_t maxDegreeN_in);

/*!
 * @brief       Finds the derivitive associated legendre polynomial and fills
 *              out the coefficients of an array.
 *
 *              NOTE: There is a singularity where the input squared equals 1.
 *
 *              NOTE: Function was verified by numerically differntiating
 *                    the outputs from GLegendrePoly_findAssociatedArrayOutput.
 *
 * @param[out]  p_legPolyDerivitiveArray_out
 *              Pointer containing the address of the output derivitive array.
 *
 * @param[in]   p_legPolyArray_in
 *              Pointer containing the address of the legendre array
 *
 * @param[in]   inputValue_in
 *              Input value which the coefficients are found.
 *
 * @param[in]   maxDegreeN_in
 *              Maximum degree to fill out to.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GLegPoly_associatedLegendreArrayPolynomialsDerivitive(
    double *p_legPolyDerivitiveArray_out,
    double *p_legPolyArray_in,
    double  inputValue_in,
    uint8_t maxDegreeN_in);

/*!
 * @brief       Finds the coefficients to apply to the schmidt quasi
 *              normalisation.
 *
 *              [Ref:https://academic.oup.com/gji/article/160/2/487/659348?login=false]
 *
 *              NOTE: Function was verified using MATLAB's legendre() function
 *                    and comparing outputs
 *
 *              NOTE: In the reference it does not mention a factor of (-1.0)^m
 *                    however this is mentioned in other texts. To match up with
 *                    the matlab version this was implemented but may need to be
 *                    removed.
 *
 * @param[out]  p_schmidtQuasiNormFactors_out
 *              Pointer containing the address of the array for which the
 *              coefficients will be stored. The array will be cleared within
 *              the function.
 *
 *              NOTE: The array should be of size, maxDegreeN_in + 1, as the
 *                    process is inclusive of the final degree.
 *
 *                    (Done this way to match with the maths better)
 *
 * @param[in]   maxDegreeN_in
 *              The maximum degree to which the array will be filled.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int
    GLegPoly_findSchmidtQuasiNormFactors(double *p_schmidtQuasiNormFactors_out,
                                         uint8_t maxDegreeN_in);

/*!
 * @brief       Function which fills an array with coefficients for the
 *              legendre polynomials for order 0.
 *
 * @param[out]  p_outputArray_out
 *              Pointer containing the address for array which will be filled
 *              with legendre polynomial coefficients.
 *
 * @param[in]   inputValue_in
 *              Input value to find the coefficients of the polynomials for.
 *
 * @param[in]   degreeN_in
 *              Degree to which the polynomial will be filled with.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GLegPoly_legendreArrayPolynomials(double *p_outputArray_out,
                                             double  inputValue_in,
                                             uint8_t degreeN_in);

/*!
 * @brief       Function which finds the output a single output for the Legendre
 *              polynomial. This is for a legendre polynomial of order 0.
 *
 * @param[out]  p_outputValue_out
 *              Pointer containing the address to store the output value.
 *
 * @param[in]   inputValue_in
 *              Input value into legendre polynomial
 *
 * @param[in]   degreeN_in
 *              Integer representing the degree of the legendre polynomial.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GLegPoly_legendrePolynomial(double *p_outputValue_out,
                                       double  inputValue_in,
                                       uint8_t degreeN_in);

#ifdef __cplusplus
}
#endif
#endif /* H_GLEGPOLY_PUBLICFUNCTIONS_H */
