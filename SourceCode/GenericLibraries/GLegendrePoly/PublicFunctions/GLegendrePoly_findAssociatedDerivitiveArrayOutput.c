/*
 *    @File:         GLegendrePoly_findAssociatedDerivitiveArrayOutput.c
 *
 *    @Brief:        Finds the derivitives of the associated legendre
 *                   polynomials.
 *
 *    @Date:         23/09/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "GLegendrePoly/ConstantDefs/GLegendrePoly_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int GLegendrePoly_findAssociatedDerivitiveArrayOutput(
    double *p_legendrePolyDerivitiveArray_out,
    double *p_legendrePolyArray_in,
    double  inputValue_in,
    int     nDegreeMax_in)
{
  /* Declare local variables */
  double absDenominator;
  int    n;
  int    m;

  /* Finds the absolute value of the denominator for the recursive formula */
  GMath_abs(inputValue_in * inputValue_in - 1.0, &absDenominator);

  if (absDenominator < GLEGENDREPOLY_SINGULARITY_TOLERANCE)
  {
    GError(
        "Input value breaches singularity tolerance. inputValue*inputValue - 1 "
        "= 0. (inputValue = %lf, inputValue*inputValue = %lf)",
        inputValue_in,
        inputValue_in * inputValue_in);
  }

  /* Clear array  */
  GZero(
      p_legendrePolyDerivitiveArray_out,
      double[nDegreeMax_in + 1][nDegreeMax_in + 1]);

  /* Set initial value */
  *(p_legendrePolyDerivitiveArray_out + (nDegreeMax_in + 1) * 0 + 0) = 0;

  /* Fill the first column */
  for (n = 1; n <= nDegreeMax_in; n++)
  {
    *(p_legendrePolyDerivitiveArray_out + (nDegreeMax_in + 1) * n + 0) =
        -(((double)n) * inputValue_in *
              *(p_legendrePolyArray_in + (nDegreeMax_in + 1) * n + 0) -
          ((double)n) *
              *(p_legendrePolyArray_in + (nDegreeMax_in + 1) * (n - 1) + 0)) /
        (inputValue_in * inputValue_in - 1.0);
  }

  /* Iterate columns, filling the lower half of the array with coefficients */
  for (m = 1; m <= nDegreeMax_in; m++)
  {
    for (n = m; n <= nDegreeMax_in; n++)
    {
      *(p_legendrePolyDerivitiveArray_out + (nDegreeMax_in + 1) * n + m) =
          -(((double)n) * inputValue_in *
                *(p_legendrePolyArray_in + (nDegreeMax_in + 1) * n + m) -
            ((double)(n + m)) *
                *(p_legendrePolyArray_in + (nDegreeMax_in + 1) * (n - 1) + m)) /
          (inputValue_in * inputValue_in - 1.0);
    }
  }

  return GCONST_TRUE;
}
