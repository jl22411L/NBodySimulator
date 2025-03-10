/*!
 *    @File:         KeplarianPropogation_PublicFunctions.h
 *
 *    @Brief:        Header file containing the public functions for Keplarian
 *                   propogation
 *
 *    @Date:         09/03/2025
 *
 */

#ifndef H_KEPLARIANPROPOGATION_PUBLICFUNCTIONS_H
#define H_KEPLARIANPROPOGATION_PUBLICFUNCTIONS_H

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
 * @brief         Function which finds the keplarian position of a body in the
 *                inertial fixed frame. Body 1 is the main body while body 2 is
 *                the orbiting body.
 *
 * @param[in]     massBody1_kg_in
 *                Mass of the body being orbited.
 *
 * @param[in]     massBody2_kg_in
 *                Mass of the body orbiting body 1.
 *
 * @param[in]     semiMajorAxis_km_in
 *                Semi major axis of orbit in kilometers.
 *
 * @param[in]     eccentricity_in
 *                Eccentricity of the orbit.
 *
 * @param[in]     inclintaion_rad_in
 *                Inclination of the orbit in radians.
 *
 * @param[in]     argOfPeriapsis_rad_in
 *                Argument of periapsis or orbit in radians.
 *
 * @param[in]     raans_rad_in
 *                Right Acension of Ascending Nodes in radians.
 *
 * @param[in]     timeSincePeriapsis_s_in
 *                Time since periapsis of orbit in unix time.
 *
 * @param[in]     simTime_s_in
 *                Current sim time, in unix time.
 *
 * @param[out]    p_orbitalPosition_InertCen_out
 *                Pointer to vector where the position of body 2 with respect
 *                to the inertical centric frame of body 1 in cartesian form
 *                will be returned.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int KeplarianPropogation_keplarianToCartesian(
    double  massBody1_kg_in,
    double  massBody2_kg_in,
    double  semiMajorAxis_km_in,
    double  eccentricity_in,
    double  inclintaion_rad_in,
    double  argOfPeriapsis_rad_in,
    double  raans_rad_in,
    double  timeSincePeriapsis_s_in,
    double  simTime_s_in,
    double *p_orbitalPosition_InertCen_out);

#ifdef __cplusplus
}
#endif
#endif /* H_KEPLARIANPROPOGATION_PUBLICFUNCTIONS_H */