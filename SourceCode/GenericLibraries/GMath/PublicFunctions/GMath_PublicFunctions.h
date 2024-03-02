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

// TODO
extern int GMath_invCol(
    double *p_inputMatrix_in,
    double *p_resultCol_in,
    double *p_initialCol_out,
    int     sideN_in);

// TODO
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
 *              GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
 */
extern int GMath_quaternionRateCalc(
    double *p_quaternionRate_out,
    double *p_quaternion_in,
    double *p_angularVelocity_in);

/*!
 * @brief       Fucntion which finds the magnitude of a 4x1 vector
 *
 * @param[out]  outputValue_out
 *              Address of variable result should be outputted to
 *
 * @param[in]   xVectorComponent_in
 *              X component of the vector to normalize
 *
 * @param[in]   yVectorComponent_in
 *              Y component of the vector to normalize
 *
 * @param[in]   zVectorComponent_in
 *              Z component of the vector to normalize
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
 */
extern int GMath_vectorNorm3x1(
    double *outputValue_out,
    double  xVectorComponent_in,
    double  yVectorComponent_in,
    double  zVectorComponent_in);

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
 *              GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
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
 *              GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
 */
extern int GMath_vectorNorm(
    double *outputVector_out,
    double *vector_in,
    int     vectorSize_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GMATH_PUBLICFUNCTIONS_H */
