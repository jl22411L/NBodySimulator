/*!
 *    @File:         KeplarianPropogation_Const.h
 *
 *    @Brief:        Header file containing the constants for keplarian
 *                   propogation.
 *
 *    @Date:         09/03/2025
 *
 */

#ifndef H_KEPLARIANPROPOGATION_CONST_H
#define H_KEPLARIANPROPOGATION_CONST_H

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
 * @brief       Constant used to define the maximum number of iterations that
 *              can be used to find the eccentric anomoly
 *
 * @frame       N/A
 * @units       N/A
 */
#define KEPLARIAN_PROPOGATION_ECCENTRIC_ANOMOLY_MAX_ITERATIONS (1000)

/*!
 * @brief       Constant used to define the tolerance of the eccentric anomoly
 *
 * @frame       N/A
 * @units       Radians
 */
#define KEPLARIAN_PROPOGATION_ECCENTRIC_ANOMOLY_TOLERANCE_RAD  (1e-8)

#ifdef __cplusplus
}
#endif
#endif /* H_KEPLARIANPROPOGATION_CONST_H */