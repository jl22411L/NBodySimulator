/*
 *    @File:         GMath_invColOptimised.c
 *
 *    @ Brief:       Finds the column x for the equation [A]{x} = {b}. Works
 *                   the same to GMath_invCol() however is setup so that you
 *                   only need to compute LU decomposite of matrix A once,
 *                   reducing a lot of foating point calcaultions and improving
 *                   performance.
 *
 *    @ Date:        02/03/2024
 *
 */

#include <stdlib.h>

/* Function Includes */
#include "GMath/PrivateFunctions/GMath_PrivateFunctions.h"

/* Structure Include */
/* None */

/* Data include */
#include "GMath/ConstantDefs/GMath_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GMath_invColOptimised(
    double *p_lowerMatrix_in,
    double *p_upperMatrix_in,
    double *p_resultCol_in,
    double *p_initialCol_out,
    int     sideN_in)
{
  /* Defining local variables */
  double
      intermediateColumn[GMATH_OPTIMISED_INV_MATRIX_INTERMEDIATE_COLUMN_BUFFER];

  /* Clearing Buffers */
  GZero(
      &intermediateColumn[0],
      double[GMATH_OPTIMISED_INV_MATRIX_INTERMEDIATE_COLUMN_BUFFER]);

  /* Forward propogate to find the solution for the intermediate column */
  GMath_forwardPropogation(
      p_lowerMatrix_in,
      p_resultCol_in,
      &intermediateColumn[0],
      sideN_in);

  /* Backward propogate to find the initial Column x */
  GMath_backwardPropogation(
      p_upperMatrix_in,
      &intermediateColumn[0],
      p_initialCol_out,
      sideN_in);

  return GCONST_TRUE;
}
