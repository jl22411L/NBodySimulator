/*
 *    @File:         GMath_backwardPropogation.c
 *
 *    @ Brief:       Backward propogation to solve a linear matrix of equations.
 *
 *    @ Date:        02/03/2024
 *
 */

#include <string.h>

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

int GMath_backwardPropogation(
    double *p_upperMat_in,
    double *p_inputCol_in,
    double *p_outputCol_out,
    int     sideN_in)
{
  /* Define local variables */
  int i;
  int j;

  /* Find the output column */
  for (i = sideN_in - 1; i >= 0; i--)
  {
    /* For each element find value */
    *(p_outputCol_out + i) = *(p_inputCol_in + i);
    for (j = i + 1; j <= sideN_in; j++)
    {
      *(p_outputCol_out + i) =
          *(p_outputCol_out + i) -
          (*(p_upperMat_in + i * sideN_in + j)) * (*(p_outputCol_out + j));
    }
    *(p_outputCol_out + i) =
        *(p_outputCol_out + i) / *(p_upperMat_in + i * sideN_in + i);

    /* Check to make sure dividing by a suitable tolerance */
    if (*(p_upperMat_in + i * sideN_in + i) < GCONST_NM_TOLERANCE &&
        *(p_upperMat_in + i * sideN_in + i) > -GCONST_NM_TOLERANCE)
    {
      GError(
          "Backpropogation failure. (divide by zero)\n"
          "Value is not within tolerance \n"
          "*(p_outputCol_out + i) ="
          "*(p_outputCol_out + i) / *(p_upperMat_in + i * sideN_in + i);"
          "*(p_upperMat_in + i * sideN_in + i) = %lf\n",
          *(p_upperMat_in + i * sideN_in + i));
    }
  }

  return GCONST_TRUE;
}
