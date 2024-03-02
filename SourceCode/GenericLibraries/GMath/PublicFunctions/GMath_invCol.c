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
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GMath_invCol(
    double *p_inputMatrix_in,
    double *p_resultCol_in,
    double *p_initialCol_out,
    int     sideN_in)
{
  /* Defining local variables */
  double lowerMatrixBuffer[GCONST_BUFFER_32][GCONST_BUFFER_32];
  double upperMatrixBuffer[GCONST_BUFFER_32][GCONST_BUFFER_32];
  double intermediateColumn[GCONST_BUFFER_32];

  /* Clearing Buffers */
  GZero(&lowerMatrixBuffer[0][0], double[GCONST_BUFFER_32][GCONST_BUFFER_32]);
  GZero(&upperMatrixBuffer[0][0], double[GCONST_BUFFER_32][GCONST_BUFFER_32]);
  GZero(&intermediateColumn[0], double[GCONST_BUFFER_32]);

  /* Find LU decomposition matricies */
  GMath_luDecomp(
      p_inputMatrix_in,
      &upperMatrixBuffer[0][0],
      &lowerMatrixBuffer[0][0],
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
