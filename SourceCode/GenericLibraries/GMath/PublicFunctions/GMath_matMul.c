/*
 *    @File:         GMath_matMul.c
 *
 *    @ Brief:       Does matrix multiplication of two matricies of any size.
 *
 *    @ Date:        07/03/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int GMath_matMul(
    double *p_matrixA_in,
    int     rowsA_in,
    int     colsA_in,
    double *p_matrixB_in,
    int     rowsB_in,
    int     colsB_in,
    double *p_matrixC_out)
{
  /* Declaring local variables */
  double elementTotal;
  int    i;
  int    j;
  int    k;

  /* Check dimensions of matrix are valid */
  if (colsA_in != rowsB_in)
  {
    GError(
        "Matrix dimensions are not valid\n"
        "Matrix A (NxM): %dx%d\n"
        "Matrix b (NxM): %dx%d\n",
        rowsA_in,
        colsA_in,
        rowsB_in,
        colsB_in);
  }

  /* Iterate through rows for matrix c */
  for (i = 0; i < rowsA_in; i++)
  {
    /* Iterate through columns for matrix c */
    for (j = 0; j < colsB_in; j++)
    {
      /* Set total for element to Zero before */
      elementTotal = 0;

      /* Find the sum for the element in matrix c */
      for (k = 0; k < colsA_in; k++)
      {
        elementTotal += (*(p_matrixA_in + i * colsA_in + k)) *
                        (*(p_matrixB_in + k * colsB_in + j));
      }

      /* Set the element of the output matrix */
      *(p_matrixC_out + i * colsB_in + j) = elementTotal;
    }
  }

  return GCONST_TRUE;
}
