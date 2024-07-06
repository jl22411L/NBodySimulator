/*
 *    @File:         Triad_PublicFunctions.h
 *
 *    @Brief:        Contains the public functions for the Triad Algorithm
 *
 *    @Date:         03/07/2024
 *
 */

#ifndef H_TRIAD_PUBLIC_FUNCTIONS_H
#define H_TRIAD_PUBLIC_FUNCTIONS_H

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
 * @brief       Triad algorithm which finds the dcm from the inertial frame to
 *              the body frame. It takes 2 vectors which have been both measured
 *              in the body frame as well as the fixed frame. The first vector
 *              should be the one which is more accurate and has less noise
 *              for better performance.
 *
 * @param[in]   p_vector1_bod_in
 *              Pointer to vector 1 measured in the body frame.
 *
 * @param[in]   p_vector1_fix_in
 *              Pointer to vector 1 measured in the fixed frame.
 *
 * @param[in]   p_vector2_bod_in
 *              Pointer to vector 2 measured in the body frame.
 *
 * @param[in]   p_vector2_fix_in
 *              Pointer to vector 1 measured in the fixed frame.
 *
 * @param[out]  p_dcm_fixToBod_out
 *              Pointer to 3x3 array of doubles which the resutls of the dcm
 *              that represents the transformation from fixed frame to body
 *              frame.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int TriadAlgorithm_getDcm(
    double *p_vector1_bod_in,
    double *p_vector1_fix_in,
    double *p_vector2_bod_in,
    double *p_vector2_fix_in,
    double *p_dcm_fixToBod_out);

/*!
 * @brief       Triad algorithm which finds the quaternion from the inertial
 *              frame to the body frame. It takes 2 vectors which have been both
 *              measured in the body frame as well as the fixed frame. The first
 *              vector should be the one which is more accurate and has less
 *              noise for better performance.
 *
 * @param[in]   p_vector1_bod_in
 *              Pointer to vector 1 measured in the body frame.
 *
 * @param[in]   p_vector1_fix_in
 *              Pointer to vector 1 measured in the fixed frame.
 *
 * @param[in]   p_vector2_bod_in
 *              Pointer to vector 2 measured in the body frame.
 *
 * @param[in]   p_vector2_fix_in
 *              Pointer to vector 1 measured in the fixed frame.
 *
 * @param[out]  p_quat_fixToBod_out
 *              Pointer containing address of quaternion which contains the
 *              transformation from fixed frame to body frame.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int TriadAlgorithm_getQuat(
    double *p_vector1_bod_in,
    double *p_vector1_fix_in,
    double *p_vector2_bod_in,
    double *p_vector2_fix_in,
    double *p_quat_fixToBod_out);

#ifdef __cplusplus
}
#endif
#endif /* H_TRIAD_PUBLIC_FUNCTIONS_H */
