/*!
 *    @File:         KeplarianPropogation_PrivateFunctions.h
 *
 *    @Brief:        Header file containing the private functions for Keplarian
 *                   propogation.
 *
 *    @Date:         09/03/2025
 *
 */

#ifndef H_KEPLARIANPROPOGATION_PRIVATEFUNCTIONS_H
#define H_KEPLARIANPROPOGATION_PRIVATEFUNCTIONS_H

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
 * @brief         Functinon which will find the ecentric anomoly using the
 *                Newton Raphson method. This function can be configured using
 *                constants to change the max number of iterations used and the
 *                tolerance of the ecentric anomoly.
 *
 * @param[in]     meanAnomoly_rad_in
 *                Mean anomoly of orbit in radians.
 *
 * @param[in]     eccentricity_in
 *                Eccentricity of the orbit
 *
 * @param[out]    p_eccentricAnomoly_rad_out
 *                Pointer containing the address of the variable which the
 *                output of the ecentric anomoly will be stored.
 *
 * @return        Upon a successful completion the function will return a
 *                GCONST_TRUE. Upon an unsuccessful completion the function will
 *                return a GCONST_FALSE.
 */
extern int KeplarianPropogation_findEccentricAnomoly(
    double  meanAnomoly_rad_in,
    double  eccentricity_in,
    double *p_eccentricAnomoly_rad_out);

/*!
 * @brief         Function which rotates the position of the orbiting body from
 *                the Periapsis framt to the inertial centric frame.
 *
 * @param[in]     p_orbitalPosition_Per_in
 *                Pointer to orbital position vector in the perificol frame
 *
 * @param[in]     inclintaion_rad_in
 *                Inclination of the orbit in radians.
 *
 * @param[in]     argOfPeriapsis_rad_in
 *                Argument of periapsis of the orbit in radians
 *
 * @param[in]     raans_rad_in
 *                Right Acension of Acending Nodes of the orbit in radians
 *
 * @param[out]    p_orbitalPosition_InertCen_out
 *                Pointer to vector which the result of the position of the
 *                orbiting body in the inertial centric frame will be stored.
 *
 * @return        Upon a successful completion the function will return a
 *                GCONST_TRUE. Upon an unsuccessful completion the function will
 *                return a GCONST_FALSE.
 */
extern int KeplarianPropogation_findPositionInInertCen(
    double *p_orbitalPosition_Per_in,
    double  inclintaion_rad_in,
    double  argOfPeriapsis_rad_in,
    double  raans_rad_in,
    double *p_orbitalPosition_InertCen_out);

#ifdef __cplusplus
}
#endif
#endif /* H_KEPLARIANPROPOGATION_PRIVATEFUNCTIONS_H */