/*
 *    @File:         GMath_PublicFunctions.h
 *
 *    @ Brief:       Contains the public functions for GMath module
 *
 *    @ Date:        29/01/2024
 *
 */

#ifndef H_GMATH_PUBLICFUNCTIONS_H
#define H_GMATH_PUBLICFUNCTIONS_H

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
 * @brief       Function which finds the inverse of a column vector. First,
 *              decomposes the input matrix A and then does backward and
 *              forward propogation to find the column vector.
 *
 *              [A]{x} = {b}
 *
 *              Finds x.
 *
 * @param[in]   p_inputMatrix_in
 *              Pointer containing address of first element of matrix A.
 *
 * @param[in]   p_resultCol_in
 *              Pointer containing address of result column (b).
 *
 * @param[out]  p_initialCol_out
 *              Pointer containing address of initial column (x), which
 *              resuls will be outputted to.
 *
 * @param[in]   sideN_in
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_invCol(
    double *p_inputMatrix_in,
    double *p_resultCol_in,
    double *p_initialCol_out,
    int     sideN_in);

/*!
 * @brief       Function which inverts a matrix. Takes input matrix, finds the
 *              LU decomposition and sovles for each column building up an
 *              inverted matrix.
 *
 *              [A][invA] = [I]
 *
 * @param[in]   p_inputMat_in
 *              Pointer containing adderss of first element of matrix A which
 *              inverted matrix will be found from.
 *
 * @param[out]  p_outputMat_out
 *              Pointer containing address of first element of matrix invA
 *              which results will be saved to.
 *
 * @param[in]   sideN_in
 *              Integer containing the number of columns/rows in the matrix.
 *              It is assumed that matrix A and invA are of dimension
 *              NxN
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int
    GMath_invMat(double *p_inputMat_in, double *p_outputMat_out, int sideN_in);

/*!
 * @brief       Finds the derivitive of the quaternion from the angular
 *              velocities. The quaternions take the forum:
 *
 *                   q[0] = qx
 *                   q[1] = qy
 *                   q[2] = qz
 *                   q[3] = qs
 *
 *              With a 321 rotation sequence.
 *
 * @param[out]  p_quaternionRate_out
 *              Pointer to the output quaternion rate
 *
 * @param[in]   p_quaternion_in
 *              pointer to the quaternion being inputted
 *
 * @param[in]   p_angularVelocity_in
 *              Pointer to angular velocity vector
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_quaternionRateCalc(
    double *p_quaternionRate_out,
    double *p_quaternion_in,
    double *p_angularVelocity_in);

/*!
 * @brief       Function which finds the magnitude of a vector. The vectos can
 *              be any size of a column vector.
 *
 * @param[out]  outputValue_out
 *              Address of variable result should be outputted to
 *
 * @param[in]   vector_in
 *              Address of input double array to find the magnitude of
 *
 * @param[in]   vectorSize_in
 *              Integer of the size of the vector finding the norm of.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 * function will return a GCONST_FALSE
 */
extern int GMath_vectorMag(
    double *outputValue_out,
    double *vector_in,
    int     vectorSize_in);

/*!
 * @brief       Finds the unit vector from an input vector. Output should be
 *              the same size as the input vector.
 *
 * @param[out]  outputVector_out
 *              Address to double array where norm vector will be stored
 *
 * @param[in]   vector_in
 *              Address to double vector which norm vector will be found from.
 *
 * @param[in]   vectorSize_in
 *              Integer holding the size of the input and output vector
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_vectorNorm(
    double *outputVector_out,
    double *vector_in,
    int     vectorSize_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GMATH_PUBLICFUNCTIONS_H */
