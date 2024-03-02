/*
 *    @File:         GMath_forwardPropogation.c
 *
 *    @ Brief:       Forward propogation to solve a linear matrix of equations.
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
#include "GZero/GZero.h"

int GMath_forwardPropogation(
    double *p_lowerMat_in,
    double *p_inputCol_in,
    double *p_outputCol_out,
    int     sideN_in)
{
  /* Define local variables */
  int i;
  int j;

  /* Find the output column */
  for (i = 0; i < sideN_in; i++)
  {
    /* For each element find value */
    *(p_outputCol_out + i) = *(p_inputCol_in + i);
    for (j = 0; j < i; j++)
    {
      *(p_outputCol_out + i) =
          *(p_outputCol_out + i) -
          (*(p_lowerMat_in + i * sideN_in + j)) * (*(p_outputCol_out + j));
    }
  }

  return GCONST_TRUE;
}
