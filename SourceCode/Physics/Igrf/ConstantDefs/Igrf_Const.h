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
 *              can be loaded from the IGRF. Is 14, because it is inlusive of 0
 *              and 13.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define IGRF_MAX_COEFFICIENTS       (14)

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
