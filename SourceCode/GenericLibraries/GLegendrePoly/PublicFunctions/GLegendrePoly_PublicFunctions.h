/*
 *    @File:         GLegendrePoly_PublicFunctions.h
 *
 *    @Brief:        Header file which contains public functions for
 *                   GLegendrePoly module.
 *
 *    @Date:         19/09/2024
 *
 */

#ifndef H_GLEGENDREPOLY_PUBLICFUNCTIONS_H
#define H_GLEGENDREPOLY_PUBLICFUNCTIONS_H

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
 * @param[in]   nDegree_in
 *              Degree which the polynomial will be filled with.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GLegendrePoly_findArrayOutput(
    double *p_outputArray_out,
    double  inputValue_in,
    int     nDegree_in);

/*!
 * @brief       Fills an array of assocaited legendre polynomial coefficients
 *              for a particular input.
 *
 * @param[out]  p_assocatedLegendrePolyArray_out
 *              Pointer containing the address of the array which the associated
 *              legendre pollynomial coefficients.
 *
 * @param[in]   inputValue_in
 *              Input value to find the legendre polynomial coefficients.
 *
 * @param[in]   nDegreeMax_in
 *              Maximum degree to fill out to.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GLegendrePoly_findAssociatedArrayOutput(
    double *p_assocatedLegendrePolyArray_out,
    double  inputValue_in,
    int     nDegreeMax_in);

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
 * @param[in]   nDegree_in
 *              Integer representing the degree of the legendre polynomial.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GLegendrePoly_findSingleOutput(
    double *p_outputValue_out,
    double  inputValue_in,
    int     nDegree_in);

#ifdef __cplusplus
}
#endif
#endif /* H_GLEGENDREPOLY_PUBLICFUNCTIONS_H */
