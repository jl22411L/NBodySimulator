/*
 *    @File:         GLegendrePoly_findAssociatedArrayOutput.c
 *
 *    @Brief:        Function which finds the assocaited legendre polynomials
 *                   and stores them within an array.
 *
 *    @Date:         19/09/2024
 *
 */

#include <math.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GLegendrePoly_findAssociatedArrayOutput(
    double *p_legendrePolyArray_out,
    double  inputValue_in,
    int     nDegreeMax_in)
{
  /* Declare local variables */
  int n;
  int m;

  /* Clear array  */
  GZero(p_legendrePolyArray_out, double[nDegreeMax_in + 1][nDegreeMax_in + 1]);

  /* Set initial values */
  *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * 0 + 0) = 1;
  *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * 1 + 0) = inputValue_in;

  /* Fill first column in output array */
  for (n = 2; n <= nDegreeMax_in; n++)
  {
    *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * n + 0) =
        (((double)(2 * n - 1)) * inputValue_in *
             *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * (n - 1) + 0) -
         ((double)(n - 1)) *
             *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * (n - 2) + 0)) /
        ((double)n);
  }

  /* Iterate through columns and find the legendre polynomial coefficients */
  for (m = 1; m <= nDegreeMax_in; m++)
  {
    /* Find the diagnol */
    *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * m + m) =
        -((double)(2 * m - 1)) * sqrt(1 - inputValue_in * inputValue_in) *
        *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * (m - 1) + (m - 1));

    /* Find the value below the diagnol */
    *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * (m + 1) + (m)) =
        ((double)(2 * m + 1)) * inputValue_in *
        *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * m + m);

    /* Find the rest of the values in the column */
    for (n = m + 2; n <= nDegreeMax_in; n++)
    {
      *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * n + m) =
          (((double)(2 * n - 1)) * inputValue_in *
               *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * (n - 1) + m) -
           ((double)(n + m - 1)) *
               *(p_legendrePolyArray_out + (nDegreeMax_in + 1) * (n - 2) + m)) /
          ((double)(n - m));
    }
  }

  return GCONST_TRUE;
}
