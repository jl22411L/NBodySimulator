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

#ifdef __cplusplus
}
#endif

#endif /* H_GMATH_PUBLICFUNCTIONS_H */