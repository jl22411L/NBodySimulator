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
#define JAMSAIL_EKF_ORDER_N  (7)

/*!
 * @brief     Constant used to define the EKF degree for JamSail. This
 *            essentially describes the number of measurements being measured by
 *            the EKF.
 *
 * @frame     N/A
 * @units     N/A
 */
#define JAMSAIL_EKF_DEGREE_M (6)

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_CONST_H */