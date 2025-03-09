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
#define JAMSAIL_EKF_ORDER_N             (7)

/*!
 * @brief     Constant used to define the EKF degree for JamSail. This
 *            essentially describes the number of measurements being measured by
 *            the EKF.
 *
 *            When JamSail is in estimation mode, its measurement vector is:
 *
 *            measurementVector = [
 *              angularVelocity_Bod_rads[0],
 *              angularVelocity_Bod_rads[1],
 *              angularVelocity_Bod_rads[2]
 *            ]
 *
 * @frame     N/A
 * @units     N/A
 */
#define JAMSAIL_ESTIMATION_EKF_DEGREE_M (3)

/*!
 * @brief     Constant used to define the EKF degree for JamSail. This
 *            essentially describes the number of measurements being measured by
 *            the EKF.
 *
 *            When JamSail is in measurement mode, its measurement vector is:
 *
 *            measurementVector = [
 *              quaternion_InertCentToBod[0],
 *              quaternion_InertCentToBod[1],
 *              quaternion_InertCentToBod[2],
 *              quaternion_InertCentToBod[3],
 *              angularVelocity_Bod_rads[0],
 *              angularVelocity_Bod_rads[1],
 *              angularVelocity_Bod_rads[2]
 *            ]
 *
 * @frame     N/A
 * @units     N/A
 */
#define JAMSAIL_MEASURING_EKF_DEGREE_M  (7)

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_CONST_H */