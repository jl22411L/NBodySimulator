/*
 *    @File:         GMath_matSub.c
 *
 *    @ Brief:       Subtracts two matricies together of the same size
 *
 *    @ Date:        08/03/2024
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

int GMath_matSub(
    double *p_matrixA_in,
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

  /* Check to make sure sizes are compatiable */
  if (rowsA_in != rowsB_in || colsA_in != colsB_in)
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

  /*
   * Iterate through each element and find the difference of the respective
   * elmeent in matrix A and B
   */
  for (i = 0; i < rowsA_in; i++)
  {
    for (j = 0; j < colsA_in; j++)
    {
      *(p_matrixC_out + i * colsA_in + j) = *(p_matrixA_in + i * colsA_in + j) -
                                            *(p_matrixB_in + i * colsA_in + j);
    }
  }

  return GCONST_TRUE;
}
