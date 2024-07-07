/*
 *    @File:         GMath_matMul3x3by3x3.c
 *
 *    @Brief:        Performs a matrix multiplication of a 3x3 by a 3x3 matrix.
 *                   Follows the form [A]*[B] = [C]
 *
 *    @Date:         06/07/2024
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
#include "GZero/GZero.h"

int GMath_matMul3x3by3x3(
    double *p_matrixA_in,
    double *p_matrixB_in,
    double *p_matrixC_out)
{
  /* Declare Local Variables */
  int i;
  int j;
  int k;

  /* Clearing output matrix */
  GZero(p_matrixC_out, double[3][3]);

  /* Iterate through rows for matrix c */
  for (i = 0; i < 3; i++)
  {
    /* Iterate through columns for matrix c */
    for (j = 0; j < 3; j++)
    {
      /* Find the sum for the element in matrix c */
      for (k = 0; k < 3; k++)
      {
        *(p_matrixC_out + 3 * i + j) +=
            (*(p_matrixA_in + 3 * i + k)) * (*(p_matrixB_in + 3 * k + j));
      }
    }
  }

  return GCONST_TRUE;
}
