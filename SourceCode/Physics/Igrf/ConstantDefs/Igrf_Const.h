/*
 *    @File:         Igrf_Const.h
 *
 *    @Brief:        Header file containing the constants for the Igrf library
 *
 *    @Date:         11/09/2024
 *
 */

#ifndef H_IGRF_CONST_H
#define H_IGRF_CONST_H

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
 * @brief       Constant which indicates the maximum number of coefficients that
 *              can be loaded from the IGRF.
 *
 *              NOTE: The IGRF parameters go from 1 to 13, inclusive. This is to
 *                    keep it in line with the literature as well as keep it in
 *                    line with the parameters released in the IGRF model.
 *
 *              NOTE: While their can be a legendre polynomial for P[0][0], it
 *                    is not actually used within the IGRF model, with the
 *                    spherical harmonics starting from degree of n=1. Hence,
 *                    care should be taken with the for loops.
 *
 *
 * @frame       N/A
 * @unit        N/A
 */
#define IGRF_MAX_DEGREE             (13)

/*!
 * @brief       Constant used to define the size of the buffer which will be
 * used to load the parameters in.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define IGRF_MAX_STRING_BUFFER_SIZE (50)

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_CONST_H */
