/*
 *    @File:         GMath_PrivateFunctions.h
 *
 *    @ Brief:       Private functions for GMath module
 *
 *    @ Date:        29/02/2024
 *
 */

#ifndef H_GMATH_PRIVATEFUNCTIONS_H
#define H_GMATH_PRIVATEFUNCTIONS_H

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

// TODO
extern int GMath_backwardPropogation(
    double *p_upperMat_in,
    double *p_inputCol_in,
    double *p_outputCol_out,
    int     sideN_in);

// TODO
extern int GMath_forwardPropogation(
    double *p_lowerMat_in,
    double *p_inputCol_in,
    double *p_outputCol_out,
    int     sideN_in);

// TODO
extern int GMath_invColOptimised(
    double *p_inputMatrix_in,
    double *p_resultCol_in,
    double *p_lowerMatrix,
    double *p_upperMatrix,
    double *p_initialCol_out,
    int     sideN_in);

// TODO
extern int GMath_luDecomp(
    double *p_array_in,
    double *p_upperMat_out,
    double *p_lowerMat_out,
    int     sideN_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GMATH_PRIVATEFUNCTIONS_H */
