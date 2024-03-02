/*
 *    @File:         GMath_invCol.c
 *
 *    @ Brief:       Finds the column x for the equation [A]{x} = {b}
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

int GMath_invCol(
    double *p_inputMat_in,
    double *p_resultCol_in,
    double *p_initialCol_out,
    int     sideN_in)
{
  /* Defining local variables */
  double lowerMatrixBuffer[GMATH_COLUMNINV_BUFFER][GMATH_COLUMNINV_BUFFER];
  double upperMatrixBuffer[GMATH_COLUMNINV_BUFFER][GMATH_COLUMNINV_BUFFER];
  double intermediateColumn[GMATH_COLUMNINV_BUFFER];

  /* Clearing Buffers */
  GZero(
      &lowerMatrixBuffer[0][0],
      double[GMATH_COLUMNINV_BUFFER][GMATH_COLUMNINV_BUFFER]);
  GZero(
      &upperMatrixBuffer[0][0],
      double[GMATH_COLUMNINV_BUFFER][GMATH_COLUMNINV_BUFFER]);
  GZero(&intermediateColumn[0], double[GMATH_COLUMNINV_BUFFER]);

  /* Find LU decomposition matricies */
  GMath_luDecomp(
      p_inputMat_in,
      &lowerMatrixBuffer[0][0],
      &upperMatrixBuffer[0][0],
      sideN_in);

  /* Forward propogate to find the solution for the intermediate column */
  GMath_forwardPropogation(
      &lowerMatrixBuffer[0][0],
      p_resultCol_in,
      &intermediateColumn[0],
      sideN_in);

  /* Backward propogate to find the initial Column x */
  GMath_backwardPropogation(
      &upperMatrixBuffer[0][0],
      &intermediateColumn[0],
      p_initialCol_out,
      sideN_in);

  return GCONST_TRUE;
}
