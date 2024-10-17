/*
 *    @File:         GLegendrePoly_Const.h
 *
 *    @Brief:        Contains the constants for GLegeendrePoly library.
 *
 *    @Date:         23/09/2024
 *
 */

#ifndef H_GLEGPOLY_CONST_H
#define H_GLEGPOLY_CONST_H

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
 * @brief       Constant which is used for checking how close to a singularity
 *              the input for the differential legendre polynomial. If the
 *              absolute value of inputValue*inputValue - 1 is less then the
 *              tolerance value then an error will be thrown to indicate that
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GLEGPOLY_SINGULARITY_TOLERANCE (1e-10)

#ifdef __cplusplus
}
#endif
#endif /* H_GLEGPOLY_CONST_H */
