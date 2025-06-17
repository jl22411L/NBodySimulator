/*
 *    @File:         GMath_matMul.c
 *
 *    @ Brief:       Does matrix multiplication of two matricies of any size.
 *                   Follows the form [A]*[B] = [C]
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
#include "GZero/GZero.h"

int GMath_matMul(double *p_matrixA_in,
                 int     rowsA_in,
                 int     colsA_in,
                 double *p_matrixB_in,
                 int     rowsB_in,
                 int     colsB_in,
                 double *p_matrixC_out)
{
  /* Declaring local variables */
  int i;
  int j;
  int k;

  /* Clear output matrix */
  GZero(p_matrixC_out, double[rowsA_in][colsB_in]);

  /* Check dimensions of matrix are valid */
  if (colsA_in != rowsB_in)
  {
    GError("Matrix dimensions are not valid\n"
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
      /* Find the sum for the element in matrix c */
      for (k = 0; k < colsA_in; k++)
      {
        *(p_matrixC_out + colsB_in * i + j) +=
            (*(p_matrixA_in + i * colsA_in + k)) *
            (*(p_matrixB_in + k * colsB_in + j));
      }
    }
  }

  return GCONST_TRUE;
}
