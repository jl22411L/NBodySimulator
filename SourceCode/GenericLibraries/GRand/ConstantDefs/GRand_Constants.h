/*!
 *    @File:         GRand_Constants.h
 *
 *    @Brief:        Header file containing constants for GRand module
 *
 *    @Date:         09/02/2025
 *
 */

#ifndef H_GRAND_CONSTANTS_H
#define H_GRAND_CONSTANTS_H

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
 * @brief         Constant used to define the multiplier in the linear
 *                congrutenial generator. This is the a constant in the formula:
 *
 *                I_i+1 = a*I+i + c
 *
 * @unit          N/A
 * @frame         N/A
 */
#define GRAND_LINEAR_CONGRUENTIAL_GENERATORS_MULTIPLIER (16807)

/*!
 * @brief         Constant used to define the incriment in the linear
 *                congrutenial generator. This is the c constant in the formula:
 *
 *                I_i+1 = a*I+i + c
 *
 * @unit          N/A
 * @frame         N/A
 */
#define GRAND_LINEAR_CONGRUENTIAL_GENERATORS_INCRIMENT  (0)

/*!
 * @brief         Constant used to define the modulus in the linear
 *                congrutenial generator. This is the m constant in the formula:
 *
 *                I_i+1 = a*I+i + c
 *
 * @unit          N/A
 * @frame         N/A
 */
#define GRAND_LINEAR_CONGRUENTIAL_GENERATORS_MODULUS    (2147843647)

#ifdef __cplusplus
}
#endif
#endif /* H_GRAND_CONSTANTS_H */