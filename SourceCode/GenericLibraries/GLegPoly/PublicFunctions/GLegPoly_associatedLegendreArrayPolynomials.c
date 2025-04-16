/*
 *    @File:         GLegPoly_associatedLegendreArrayPolynomials.c
 *
 *    @Brief:        Function which finds the assocaited legendre polynomials
 *                   and stores them within an array.
 *
 *    @Date:         19/09/2024
 *
 */

#include <math.h>
#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GLegPoly_associatedLegendreArrayPolynomials(double *p_legPolyArray_out,
                                                double  inputValue_in,
                                                uint8_t maxDegreeN_in)
{
  /* Declare local variables */
  uint8_t n;
  uint8_t m;

  /* Clear array  */
  GZero(p_legPolyArray_out, double[maxDegreeN_in + 1][maxDegreeN_in + 1]);

  /* Set initial values */
  *(p_legPolyArray_out + (maxDegreeN_in + 1) * 0 + 0) = 1;
  *(p_legPolyArray_out + (maxDegreeN_in + 1) * 1 + 0) = inputValue_in;

  /* Fill first column in output array */
  for (n = 2; n <= maxDegreeN_in; n++)
  {
    *(p_legPolyArray_out + (maxDegreeN_in + 1) * n + 0) =
        (((double)(2 * n - 1)) * inputValue_in *
             *(p_legPolyArray_out + (maxDegreeN_in + 1) * (n - 1) + 0) -
         ((double)(n - 1)) *
             *(p_legPolyArray_out + (maxDegreeN_in + 1) * (n - 2) + 0)) /
        ((double)n);
  }

  /* Iterate through columns and find the legendre polynomial coefficients */
  for (m = 1; m <= maxDegreeN_in; m++)
  {
    /* Find the diagnol */
    *(p_legPolyArray_out + (maxDegreeN_in + 1) * m + m) =
        -((double)(2 * m - 1)) * sqrt(1 - inputValue_in * inputValue_in) *
        *(p_legPolyArray_out + (maxDegreeN_in + 1) * (m - 1) + (m - 1));

    /* Find the value below the diagnol */
    if (m != maxDegreeN_in)
    {
      *(p_legPolyArray_out + (maxDegreeN_in + 1) * (m + 1) + (m)) =
          ((double)(2 * m + 1)) * inputValue_in *
          *(p_legPolyArray_out + (maxDegreeN_in + 1) * m + m);
    }

    /* Find the rest of the values in the column */
    for (n = m + 2; n <= maxDegreeN_in; n++)
    {
      *(p_legPolyArray_out + (maxDegreeN_in + 1) * n + m) =
          (((double)(2 * n - 1)) * inputValue_in *
               *(p_legPolyArray_out + (maxDegreeN_in + 1) * (n - 1) + m) -
           ((double)(n + m - 1)) *
               *(p_legPolyArray_out + (maxDegreeN_in + 1) * (n - 2) + m)) /
          ((double)(n - m));
    }
  }

  return GCONST_TRUE;
}
