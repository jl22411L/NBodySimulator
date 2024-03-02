/*
 *    @File:         GMath_PrivateFunctions.h
 *
 *    @ Brief:       Private functions for GMath module
 *
 *    @ Date:        29/02/2024
 *
 */

#ifndef H_GMATH_PRIVATEFUNCTIONS_H
#define H_GMATH_PRIVATEFUNCTIONS_H

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
 * @brief       Performs backward propogation to a upper matrix, finding a
 *              column vector p_outputCol_out for a given p_inputCol_in.
 *
 *              [U]{x} = {d}
 *
 * @param[in]   p_upperMat_in (U)
 *              Matrix (U) used for backward propogation. Must be an upper
 *              filled matrix, meaning that any element that satisifies i>j
 *              should be equal to 0.
 *
 * @param[in]   p_inputCol_in (d)
 *              Column vector (d) which used to find what column vector x
 *              must be to result in when it is matrix multiplied by U.
 *
 * @param[out]  p_outputCol_out (x)
 *              Column vector (x) which when matricies multiplied by the
 *              matrix U, should result in column vector d.
 *
 * @param[in]   sideN_in
 *              Represents the side of the square matrix U, and the length of
 *              p_outputCol_out and p_inputCol_in.
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the code.
 *              GCONST_FALSE indicates that an error has ocuured which should
 *              stop the running of the software.
 */
extern int GMath_backwardPropogation(
    double *p_upperMat_in,
    double *p_inputCol_in,
    double *p_outputCol_out,
    int     sideN_in);

/*!
 * @brief       Function which applies a forward propogation to a lower matrix,
 *              finding column vector p_outputCol_out.
 *
 *              [L]{d} = {b}
 *
 * @param[in]   p_lowerMat_in (L)
 *              Matrix (L) used for forward propogation. Must be a lower
 *              filled matrix, meaning that any element that satisifies i<j
 *              should be equal to 0. Should also have elements i=j equal to 1.
 *
 * @param[in]   p_inputCol_in (b)
 *              Column vector (b) which used to find what column vector x
 *              must be to result in when it is matrix multiplied by U.
 *
 * @param[out]  p_outputCol_out (d)
 *              Column vector (d) which when matricies multiplied by the
 *              matrix L, should result in column vector d.
 *
 * @param[in]   sideN_in
 *              Represents the side of the square matrix U, and the length of
 *              p_outputCol_out and p_inputCol_in.
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the code.
 *              GCONST_FALSE indicates that an error has ocuured which should
 *              stop the running of the software.
 */
extern int GMath_forwardPropogation(
    double *p_lowerMat_in,
    double *p_inputCol_in,
    double *p_outputCol_out,
    int     sideN_in);

/*!
 * @brief       Finds the column vector x which will satisy: [L][U]{x} = {b}
 *              It is assumed that L and U are square matricies NxN with x and b
 *              being a column vector of dimensions Nx1.
 *
 *              Works similar to GMath_invCol() but instead takes input of
 *              L and U matrix, meaning they only need to be calculated once.
 *
 *              Note: [A]{x} = {b}, Hence, [L][U] = [A]
 *
 * @param[in]   p_resultCol_in (b)
 *              Result column vector which will be used to find vector x.
 *
 * @param[in]   p_lowerMatrix_in (L)
 *              Lower matrix
 *
 * @param[in]   p_upperMatrix_in (U)
 *              Upper matrix
 *
 * @param[out]  p_initialCol_out (x)
 *              Input column which.
 *
 * @param[in]   sideN_in
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the code.
 *              GCONST_FALSE indicates that an error has ocuured which should
 *              stop the running of the software.
 */
extern int GMath_invColOptimised(
    double *p_lowerMatrix_in,
    double *p_upperMatrix_in,
    double *p_resultCol_in,
    double *p_initialCol_out,
    int     sideN_in);

/*!
 * @brief       Finds the Lower and Upper matrix by decomposing a matrix.
 *              Follows convention that:
 *
 *              [A] = [L][U]
 *
 * @param[in]   p_array_in
 *              Pointer to matrix A which will find decomposed matricies L and
 *              U.
 *
 * @param[out]  p_lowerMat_out
 *              Pointer containing address to store elements of lower matrix
 *
 * @param[out]  p_upperMat_out
 *              Pointer containing address to store elements of upper matrix.
 *
 * @param[in]   sideN_in
 *              Integer containing the number of rows/columns of matrix A.
 *
 * @return      Returns GCONST_TRUE upon a successful completion of the code.
 *              GCONST_FALSE indicates that an error has ocuured which should
 *              stop the running of the software.
 */
extern int GMath_luDecomp(
    double *p_array_in,
    double *p_lowerMat_out,
    double *p_upperMat_out,
    int     sideN_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GMATH_PRIVATEFUNCTIONS_H */
