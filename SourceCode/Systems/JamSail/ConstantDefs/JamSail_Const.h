/*!
 *    @File:         JamSail_Const.h
 *
 *    @Brief:        Header file containing the constants for JamSail
 *
 *    @Date:         08/03/2025
 *
 */

#ifndef H_JAMSAIL_CONST_H
#define H_JAMSAIL_CONST_H

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
 * @brief     Constant used to define the EKF order for JamSail. This
 *            essentially describes the number of states being modelled by the
 *            EKF.
 *
 * @frame     N/A
 * @units     N/A
 */
#define JAMSAIL_EKF_ORDER_N                       (7)

/*!
 * @brief     Constant used to define the EKF degree for JamSail. This
 *            essentially describes the number of measurements being measured by
 *            the EKF.
 *
 * @frame     N/A
 * @units     N/A
 */
#define JAMSAIL_EKF_DEGREE_M                      (9)

/*!
 * @brief     Constant used to define the semi major axis of the earth sun pair.
 *
 * @frame     N/A
 * @units
 */
#define JAMSAIL_EARTH_SUN_SEMI_MAJOR_AXIS_M       (149598000000)

/*!
 * @brief     Constant used to define the eccentricity of the earth sun pair.
 *
 * @frame     N/A
 * @units
 */
#define JAMSAIL_EARTH_SUN_ECCENTRICITY            (0.01670)

/*!
 * @brief     Constant used to define the inclination of the earth sun pair.
 *
 * @frame     N/A
 * @units
 */
#define JAMSAIL_EARTH_SUN_INCLINATION             (0)

/*!
 * @brief     Constant used to define the argument of perigee of the earth sun
 *            pair.
 *
 * @frame     N/A
 * @units
 */
#define JAMSAIL_EARTH_SUN_ARGUMENT_OF_PERIGEE_RAD (1.796764105)

/*!
 * @brief     Constant used to define the RAANS of the earth sun pair.
 *
 * @frame     N/A
 * @units
 */
#define JAMSAIL_EARTH_SUN_RAANS_RAD               (-0.1965310551)

/*!
 * @brief     Constant used to define the semi major axis of the earth sun pair.
 *
 * @frame     N/A
 * @units     Seconds
 */
#define JAMSAIL_EARTH_SUN_TIME_SINCE_PERIAPSIS_S  (931362709)

/*!
 * @brief     Time in seconds from start of simulation before JamSail's ADCS is
 *            turned on.
 *
 * @frame     N/A
 * @units     Seconds
 */
#define JAMSAIL_STARTUP_PROCESS_TIME_S            (120)

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_CONST_H */