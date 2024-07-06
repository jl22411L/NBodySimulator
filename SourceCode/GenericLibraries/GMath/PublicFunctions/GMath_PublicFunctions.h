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
 * @brief       Finds the cross product of vectors A and B, outputting results
 *              to vector C. This does not clear the output vector in operation,
 *              and hence it is down to the user to do so at there own
 *              discression.
 *
 *              The algorithm allows for 1 vector input to be the output as
 *              well, which should allow for easier management when doing
 *              complex mathematical operations which requrie multi layer cross
 *              products.
 *
 *              {a}x{b} = {c}
 *
 * @param[in]   p_vectorA_in
 *              Pointer containing address of first element of vector A.
 *
 * @param[in]   p_vectorB_in
 *              Pointer containing address of first element of vector B.
 *
 * @param[out]  p_vectrocC_out
 *              Pointer containing address of first element of vector C.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_crossProduct(
    double *p_vectorA_in,
    double *p_vectorB_in,
    double *p_vectrocC_out);

/*!
 * @brief       Function which takes in a DCM to then output Euler Angle 123
 *              vector.
 *
 * @param[in]   p_dcmMatrix_in
 *              Pointer to a 2D double array which contains a DCM matrix.
 *
 * @param[out]  p_eulerAngleVector_rad_out
 *              Pointer to double vector which contains Euler Anlges (123)
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int
    GMath_dcm2Eul(double *p_dcmMatrix_in, double *p_eulerAngleVector_rad_out);

/*!
 * @brief       Function which converts a DCM to a quaternion.
 *
 * @param[in]   p_dcmMatrix_in
 *              Pointer to a 2D double array which contains a DCM matrix
 *
 * @param[out]  p_quaternionVector_out
 *              Pointer to a double vector which contains a quaternion.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int
    GMath_dcm2Quat(double *p_dcmMatrix_in, double *p_quaternionVector_out);

/*!
 * @brief       Function which converts a 123 Euler Vector to a DCM.
 *
 * @param[in]   p_eulerAngleVector_rad_in
 *              Pointer to double vector which contains Euler Angles (123)
 *
 * @param[out]  p_dcmMatrix_out
 *              Pointer to double 2D array which contains a DCM matrix.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int
    GMath_eul2Dcm(double *p_eulerAngleVector_rad_in, double *p_dcmMatrix_out);
/*!
 * @brief       GMath function which takes euler angles and converts them to
 *              a quaternion.
 *
 * @param[in]   p_eulerAnglevector_rad_in
 *              Pointer to double array containing euler angles vector.
 *              Vector should be of format 123 (XYZ) meaning:
 *
 *              eulerAngles = [
 *                          ROLL,
 *                          PITCH,
 *                          YAW]
 *
 * @param[out]  p_quaternionVector_out
 *              Pointer to double array containing quaternion vector.
 *              Quaternion should be of form:
 *
 *              quaternion = [
 *                         quaternion_x,
 *                         quaternion_y,
 *                         quaternion_z,
 *                         quaternion_s]
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_eul2Quat(
    double *p_eulerAnglevector_rad_in,
    double *p_quaternionVector_out);

/*!
 * @brief       GMath function which finds the unit quaternion of an inputted
 *              quaternion.
 *
 * @param[in]   p_inputQuaternion_in
 *              Pointer to double array containnig quaternion to get unit
 *              quaternion of.
 *
 * @param[out]  p_outputQuaternion_out
 *              Pointer to double array where output unit quaternion will be
 *              stored.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_findUnitQuaternion(
    double *p_inputQuaternion_in,
    double *p_outputQuaternion_out);

/*!
 * @brief       Finds the unit vector. Finds the square of each element and sums
 *              them together then square roots the final result. Then, divides
 *              all the elements of the vector by the magnitude. It should be
 *              noted that the output unit vecotr is not cleared within this
 *              function and it is down to the user to decide if this operation
 *              is appropraite outside the function.
 *
 * @param[in]   p_vector_in
 *              Input vector which the output vector will be found from.
 *
 * @param[out]  p_vector_out
 *              Unit vector which is outputted.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_findUnitVector(double *p_vector_in, double *p_vector_out);

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
 *
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
 * @brief       Finds the sum of two matricies A and B and saves
 *              output to matrix C.
 *
 *              [C] = [A] + [B]
 *
 * @param[in]   p_matrixA_in
 *              Pointer containing address of first element in matrix A.
 *
 * @param[in]   rowsA_in
 *              Integer containing the number of rows in matrix A.
 *
 * @param[in]   colsA_in
 *              Integer containing the number of columns in matrix A.
 *
 * @param[in]   p_matrixB_in
 *              Pointer containing address of first element in matrix B.
 *
 * @param[in]   rowsB_in
 *              Integet containing the number of rows in Matrix B.
 *
 * @param[in]   colsB_in
 *              Integer containg the number of columns in Matrix B.
 *
 * @param[out]  p_matrixC_out
 *              Pointer containing address of the first element in Matrix C.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_matAdd(
    double *p_matrixA_in,
    int     rowsA_in,
    int     colsA_in,
    double *p_matrixB_in,
    int     rowsB_in,
    int     colsB_in,
    double *p_matrixC_out);

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
 * @brief       A function that will multiply matrix A and B to get matrix C
 *
 *                          [A][B] = [C]
 *
 *              Matrix A must have a number of columns equal to the number of
 *              rows that matrix B has.
 *
 *              [rowsA_in * colsA_in][rowsB_in * colsB_in]
 *                                   = [rowsA_in * colsB_in]
 *
 * @param[in]   p_matrixA_in
 *              Pointer with address to double array contining matrix A.
 *
 * @param[in]   rowsA_in
 *              Integer containing the number of rows in matrix A.
 *
 * @param[in]   colsA_in
 *              Integer containing the number of cols in matrix A.
 *
 * @param[in]   p_matrixB_in
 *              Pointer with address to double array contining matrix B.
 *
 * @param[in]   rowsB_in
 *              Integer containing the number of rows in matrix A.
 *
 * @param[in]   colsB_in
 *              Integer containing the number of cols in matrix A.
 *
 * @param[out]  p_matrixC_out
 *              Pointer with address for output of double array to matrix C.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_matMul(
    double *p_matrixA_in,
    int     rowsA_in,
    int     colsA_in,
    double *p_matrixB_in,
    int     rowsB_in,
    int     colsB_in,
    double *p_matrixC_out);

/*!
 * @brief       A function that will multiply matrix A (3x3) and B (3x3) to get
 *              matrix C.
 *
 *                          [A][B] = [C]
 *
 *              Matrix A must have a number of columns equal to the number of
 *              rows that matrix B has.
 *
 *              [rowsA_in * colsA_in][rowsB_in * colsB_in]
 *                                   = [rowsA_in * colsB_in]
 *
 * @param       p_matrixA_in
 *              Pointer with address to double array contining matrix A.
 *
 * @param       p_matrixB_in
 *              Pointer with address to double array contining matrix B.
 *
 * @param       p_matrixC_out
 *              Pointer with address for output of double array to matrix C.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_matMul3x3by3x3(
    double *p_matrixA_in,
    double *p_matrixB_in,
    double *p_matrixC_out);

/*!
 * @brief       Finds the difference of two matricies A and B and saves
 *              output to matrix C.
 *
 *              [C] = [A] - [B]
 *
 * @param[in]   p_matrixA_in
 *              Pointer containing address of first element in matrix A.
 *
 * @param[in]   rowsA_in
 *              Integer containing the number of rows in matrix A.
 *
 * @param[in]   colsA_in
 *              Integer containing the number of columns in matrix A.
 *
 * @param[in]   p_matrixB_in
 *              Pointer containing address of first element in matrix B.
 *
 * @param[in]   rowsB_in
 *              Integet containing the number of rows in Matrix B.
 *
 * @param[in]   colsB_in
 *              Integer containg the number of columns in Matrix B.
 *
 * @param[out]  p_matrixC_out
 *              Pointer containing address of the first element in Matrix C.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_matSub(
    double *p_matrixA_in,
    int     rowsA_in,
    int     colsA_in,
    double *p_matrixB_in,
    int     rowsB_in,
    int     colsB_in,
    double *p_matrixC_out);

/*!
 * @brief       GMath function which converts a quaternion into a DCM.
 *
 * @param[in]   p_quaternionVector_in
 *              Pointer to a double vector which contains a quaternion.
 *
 * @param[out]  p_dcmMatrix_out
 *              Pointer to a double 2D array which contains a DCM matrix.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_quaternionToDcm(
    double *p_quaternionVector_in,
    double *p_dcmMatrix_out);

/*!
 * @brief       GMath function which converts quaterniond to euler angles
 *
 * @param[in]   p_quaternionVector_in
 *              Pointer to double array containing quaternion vector.
 *              Quaternion should be of form:
 *
 *              quaternion = [
 *                         quaternion_x,
 *                         quaternion_y,
 *                         quaternion_z,
 *                         quaternion_s]
 *
 * @param[out]  p_eulerAnglesVector_rad_out
 *              Pointer to double array containing euler angles vector.
 *              Vector should be of format 123 (XYZ) meaning:
 *
 *              eulerAngles = [
 *                          ROLL,
 *                          PITCH,
 *                          YAW]
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_quaternion2Eul(
    double *p_quaternionVector_in,
    double *p_eulerAnglesVector_rad_out);

/*!
 * @brief       GMath function which finds the conjugate of a quaternion.
 *
 * @param[out]  p_outputQuaternion_out
 *              Pointer to double array containing a quaternion vector.
 *
 * @param[in]   p_inputQuaternion_in
 *              Pointer to a double array containing a quaternion vector.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_quaternionConjugate(
    double *p_outputQuaternion_out,
    double *p_inputQuaternion_in);

/*!
 * @brief       GMath function which rotates a frame around its origin, leaving
 *              the inputted point where it in the fixed frame. This is useful
 *              for seeing how the perspective of a point shifts in a rotating
 *              frame.
 *
 *              The operation can be represented as:
 *              outputVector = quaternionConjugate * inputVector * quaternion
 *
 *              where * is quaternion multiplication.
 *
 * @param[out]  p_rotatedVector_out
 *              Pointer to double array where the outputted vector will be
 *              stored.
 *
 * @param[in]   p_vectorToRotate_in
 *              Pointer to double array containing the vector with the point
 *              which the frame will keep track of during the rotation
 *
 * @param[in]   p_quaternion_in
 *              Pointer to double array containing the quaternion vector
 *              which the frame will rotate by.
 */
extern int GMath_quaternionFrameRotation(
    double *p_rotatedVector_out,
    double *p_vectorToRotate_in,
    double *p_quaternion_in);

/*!
 * @brief       GMath function to multiply two quaternions together.
 *
 *              Order of quaternion multiplication
 *              outputQuaternion = quaternionP * quaternionQ
 *
 * @param[out]  p_outputQuaternion_out
 *              Pointer to vector which output of the quaternion
 *              multiplication will be stored.
 *
 * @param[in]   p_quaternionP_in
 *              Pointer to vector quaternion P.
 * @param[in]   p_quaternionQ_in
 *              Pointer to vector quaternion Q.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int GMath_quaternionMul(
    double *p_outputQuaternion_out,
    double *p_quaternionP_in,
    double *p_quaternionQ_in);

/*!
 * @brief       GMath function which applies a rotation to a point around the
 *              origin of the frame it is represented in, by the input
 *              quaternion.
 *
 *              The operation can be represented as:
 *              outputVector = quaternion * inputVector * quaternionConjugate
 *
 *              where * is quaternion multiplication.
 *
 * @param[out]  p_rotatedVector_out
 *              Pointer to double array where the outputted vector will be
 *              stored.
 *
 * @param[in]   p_vectorToRotate_in
 *              Pointer to double array containing the vector with the point
 *              which the frame will keep track of during the rotation
 *
 * @param[in]   p_quaternion_in
 *              Pointer to double array containing the quaternion vector
 *              which the frame will rotate by.
 */
extern int GMath_quaternionPointRotation(
    double *p_rotatedVector_out,
    double *p_vectorToRotate_in,
    double *p_quaternion_in);

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
