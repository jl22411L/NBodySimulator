/*
 *    @File:         GMath_luDecomp.c
 *
 *    @ Brief:       Functions which finds the decomposition matricies of a
 *                   Matrix
 *
 *    @ Date:        29/02/2024
 *
 */

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GMath_luDecomp(
    double *p_array_in,
    double *p_lowerMat_out,
    double *p_upperMat_out,
    int     sideN_in)
{
  /* Defining local variables */
  int i;
  int j;
  int k;

  /* Loading the initial values of lower (L) and upper (U) matrix */
  for (i = 0; i < sideN_in; i++)
  {
    *(p_upperMat_out + i)                = *(p_array_in + i);
    *(p_lowerMat_out + i * sideN_in + i) = 1;
  }

  /* Decomposing input array into lower and upper matricies */
  for (i = 1; i < sideN_in; i++)
  {
    for (j = 0; j < sideN_in; j++)
    {

      /* If below diagnol */
      if (i > j)
      {
        /* Find value for lower matrix element */
        *(p_lowerMat_out + i * sideN_in + j) = *(p_array_in + i * sideN_in + j);
        for (k = 0; k < j; k++)
        {
          *(p_lowerMat_out + i * sideN_in + j) =
              *(p_lowerMat_out + i * sideN_in + j) -
              (*(p_lowerMat_out + i * sideN_in + k) *
               *(p_upperMat_out + k * sideN_in + j));
        }
        *(p_lowerMat_out + i * sideN_in + j) =
            *(p_lowerMat_out + i * sideN_in + j) /
            *(p_upperMat_out + j * sideN_in + j);

        /* Find value for upper matrix */
        *(p_upperMat_out + i * sideN_in + j) = 0;
      }

      /* If equal to diagnol or above */
      else
      {
        /* Find value for upper matrix element */
        *(p_upperMat_out + i * sideN_in + j) = *(p_array_in + i * sideN_in + j);
        for (k = 0; k < i; k++)
        {
          *(p_upperMat_out + i * sideN_in + j) =
              *(p_upperMat_out + i * sideN_in + j) -
              (*(p_lowerMat_out + i * sideN_in + k) *
               *(p_upperMat_out + k * sideN_in + j));
        }

        /* Find value of lower matrix element (which is 1 along the diagnol and
         * was set at the beginning of the function or 0) */
        if (i != j)
        {
          *(p_lowerMat_out + i * sideN_in + j) = 0;
        }
      }
    }
  }

  /* Copy data */
  return GCONST_TRUE;
}
