/*
 *    @File:         GLegPoly_legendrePolynomial.c
 *
 *    @Brief:        Function which finds the single output of a Legendre
 *                   Polynomial for a particular degree.
 *
 *    @Date:         19/09/2024
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

int GLegPoly_legendrePolynomial(
    double *p_outputValue_out,
    double  inputValue_in,
    int     nDegree_in)
{
  /* Declare local variables */
  double currentValue;
  double previousValue1;
  double previousValue2;
  int    n;

  if (nDegree_in == 0)
  {
    *(p_outputValue_out) = 1;
  }
  else if (nDegree_in == 1)
  {
    *(p_outputValue_out) = inputValue_in;
  }
  else
  {
    previousValue1 = 1;
    previousValue2 = inputValue_in;

    for (n = 2; n <= nDegree_in; n++)
    {
      /* Find the current value */
      currentValue = (((double)2 * n - 1) * inputValue_in * previousValue1 -
                      ((double)n - 1) * previousValue2) /
                     ((double)n);

      /* Update the previous  */
      previousValue1 = currentValue;
      previousValue2 = previousValue1;
    }

    /* Output the value */
    *(p_outputValue_out) = currentValue;
  }

  return GCONST_TRUE;
}
