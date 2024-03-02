/*
 *    @File:         GMath_invMat.c
 *
 *    @ Brief:       Finds the inverse of a matrix
 *
 *    @ Date:
 *
 */

/* Function Includes */
#include "GMath/PrivateFunctions/GMath_PrivateFunctions.h"
#include "GMath/PublicFunctions/GMath_PublicFunctions.h"

/* Structure Include */
/* None */

/* Data include */
#include "GMath/ConstantDefs/GMath_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

int GMath_invMat(double *p_inputMat_in, double *p_outputMat_out, int sideN_in)
{
  /* Defining Local variables */
  double upperMatrixBuffer[GMATH_MATRIXINV_BUFFER];
  double lowerMatrixBuffer[GMATH_MATRIXINV_BUFFER];
  double inputColBuffer[GMATH_MATRIXINV_BUFFER];
  double resultColumnBuffer[GMATH_MATRIXINV_BUFFER];
  int    i;
  int    j;

  /* Clearing buffers */
  GZero(&upperMatrixBuffer[0], double[GMATH_MATRIXINV_BUFFER]);
  GZero(&lowerMatrixBuffer[0], double[GMATH_MATRIXINV_BUFFER]);
  GZero(&inputColBuffer[0], double[GMATH_MATRIXINV_BUFFER]);
  GZero(&resultColumnBuffer[0], double[GMATH_MATRIXINV_BUFFER]);

  /* Check to make sure buffer size is large enough */
  if (sideN_in > GMATH_MATRIXINV_BUFFER)
    GError(
        "Buffer size is not large enough to handle %dX%d array.\nMax Buffer "
        "Size = %d",
        sideN_in,
        sideN_in,
        GMATH_MATRIXINV_BUFFER);

  /* Find LU decomposition matricies */
  GMath_luDecomp(
      p_inputMat_in,
      &lowerMatrixBuffer[0],
      &upperMatrixBuffer[0],
      sideN_in);

  /* For each column of the matrix find the respective inverse column */
  for (i = 0; i < sideN_in; i++)
  {
    /* Find the result column for which to find the inv column of */
    for (j = 0; j < sideN_in; j++)
    {
      /* If j == i then along diagnol hence set to 1. Otherwise set to 0 */
      if (j == i)
      {
        resultColumnBuffer[j] = 1;
      }
      else
      {
        resultColumnBuffer[j] = 0;
      }
    }

    /* Find the column of the inverse matrix */
    GMath_invColOptimised(
        &lowerMatrixBuffer[0],
        &upperMatrixBuffer[0],
        &resultColumnBuffer[0],
        &inputColBuffer[0],
        sideN_in);

    /* Load column buffer into output matrix */
    for (j = 0; j < sideN_in; j++)
    {
      *(p_outputMat_out + j * sideN_in + i) = inputColBuffer[j];
    }

    /* Clear buffer */
    GZero(&inputColBuffer[0], double[sideN_in]);
  }

  return GCONST_TRUE;
}
