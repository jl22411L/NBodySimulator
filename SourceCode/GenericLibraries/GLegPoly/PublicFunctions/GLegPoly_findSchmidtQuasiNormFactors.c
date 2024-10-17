/*
 *    @File:         GLegPoly_findSchmidtQuasiNormFactors.c
 *
 *    @Brief:        Finds the coefficients to apply the schmidt quasi norm
 *                   factors.
 *
 *    @Date:         30/09/2024
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
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int GLegPoly_findSchmidtQuasiNormFactors(
    double *p_schmidtQuasiNormFactors_out,
    uint8_t maxDegreeN_in)
{
  /* Declare local variables */
  uint16_t factoraialValue;
  double   factorialRatio;
  double   sign;
  int      n;
  int      m;
  int      i;

  /* Clear array  */
  GZero(
      p_schmidtQuasiNormFactors_out,
      double[maxDegreeN_in + 1][maxDegreeN_in + 1]);

  /* Fill first column */
  for (n = 0; n <= maxDegreeN_in; n++)
  {
    *(p_schmidtQuasiNormFactors_out + (maxDegreeN_in + 1) * n + 0) = 1;
  }

  /*!
   * Fill in the rest of the array with the coefficients for the schmidt quasi
   * normalisation.
   *
   * The equation for each coefficient is:
   *
   *    coefficient = (-1.0)^m * sqrt(
   *        (2 * (n - m)!) / (n + m)!
   *    )
   *
   *    [Ref:https://academic.oup.com/gji/article/160/2/487/659348?login=false]
   *
   * There is an issue that factorial of the larger numbers causes a buffer
   * overflow. Hence a ratio of factorials technique was implemented.
   *
   * Hence, the equation was as follows:
   *
   *    coefficient = sign * sqrt(
   *        factorialRatio
   *    )
   *
   * Where 'sign' is found based on if m is even or odd.
   *
   *
   * [Ref:https://www.chilimath.com/lessons/intermediate-algebra/simplifying-factorials-with-variables/]
   */
  for (m = 1; m <= maxDegreeN_in; m++)
  {
    for (n = m; n <= maxDegreeN_in; n++)
    {
      /* Find the factorial ratio */
      factorialRatio = 2.0;
      for (i = n - m + 1; i <= n + m; i++)
      {
        factorialRatio /= ((double)i);
      }

      /* Find the sign of the coefficient based on if m is even or odd */
      if (m % 2 == 0)
      {
        /* m is even and hence sign is positive */
        sign = 1.0;
      }
      else
      {
        /* m is odd and hence sign is negative */
        sign = -1.0;
      }

      /* Find the schmidt quasi norm coefficient */
      *(p_schmidtQuasiNormFactors_out + (maxDegreeN_in + 1) * n + m) =
          sign * sqrt(factorialRatio);
    }
  }

  return GCONST_TRUE;
}
