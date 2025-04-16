/*
 *    @File:         GLegPoly_associatedLegendreArrayPolynomialsDerivitive.c
 *
 *    @Brief:        Finds the derivitives of the associated legendre
 *                   polynomials.
 *
 *    @Date:         23/09/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "GLegPoly/ConstantDefs/GLegPoly_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int GLegPoly_associatedLegendreArrayPolynomialsDerivitive(
    double *p_legPolyDerivitiveArray_out,
    double *p_legPolyArray_in,
    double  inputValue_in,
    uint8_t maxDegreeN_in)
{
  /* Declare local variables */
  double  absDenominator;
  uint8_t n;
  uint8_t m;

  /* Finds the absolute value of the denominator for the recursive formula */
  GMath_abs(inputValue_in * inputValue_in - 1.0, &absDenominator);

  /* If denominaror is too close to 0, throw an error to avoid singularity */
  if (absDenominator < GLEGPOLY_SINGULARITY_TOLERANCE)
  {
    GError(
        "Input value breaches singularity tolerance. inputValue*inputValue - 1 "
        "= 0. (inputValue = %lf, inputValue*inputValue = %lf)",
        inputValue_in,
        inputValue_in * inputValue_in);
  }

  /* Clear array */
  GZero(p_legPolyDerivitiveArray_out,
        double[maxDegreeN_in + 1][maxDegreeN_in + 1]);

  /* Set initial value */
  *(p_legPolyDerivitiveArray_out + (maxDegreeN_in + 1) * 0 + 0) = 0;

  /* Fill the first column */
  for (n = 1; n <= maxDegreeN_in; n++)
  {
    *(p_legPolyDerivitiveArray_out + (maxDegreeN_in + 1) * n + 0) =
        -(((double)n) * inputValue_in *
              *(p_legPolyArray_in + (maxDegreeN_in + 1) * n + 0) -
          ((double)n) *
              *(p_legPolyArray_in + (maxDegreeN_in + 1) * (n - 1) + 0)) /
        (inputValue_in * inputValue_in - 1.0);
  }

  /* Iterate columns, filling the lower half of the array with coefficients */
  for (m = 1; m <= maxDegreeN_in; m++)
  {
    for (n = m; n <= maxDegreeN_in; n++)
    {
      *(p_legPolyDerivitiveArray_out + (maxDegreeN_in + 1) * n + m) =
          -(((double)n) * inputValue_in *
                *(p_legPolyArray_in + (maxDegreeN_in + 1) * n + m) -
            ((double)(n + m)) *
                *(p_legPolyArray_in + (maxDegreeN_in + 1) * (n - 1) + m)) /
          (inputValue_in * inputValue_in - 1.0);
    }
  }

  return GCONST_TRUE;
}
