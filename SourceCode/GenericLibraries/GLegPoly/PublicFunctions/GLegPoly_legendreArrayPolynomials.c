/*
 *    @File:         GLegPoly_legendreArrayPolynomials.c
 *
 *    @Brief:        Function which finds the output of a Legendre Polynomial
 *                   for a particular degree and stores in an array.
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

int GLegPoly_legendreArrayPolynomials(
    double *p_outputArray_out,
    double  inputValue_in,
    int     degreeN_in)
{
  /* Declare local variables */
  double currentValue;
  double previousValue1;
  double previousValue2;
  int    n;

  for (n = 0; n <= degreeN_in; n++)
  {
    if (n == 0)
    {
      *(p_outputArray_out + n) = 1;
    }
    else if (n == 1)
    {
      *(p_outputArray_out + n) = inputValue_in;
    }
    else
    {
      *(p_outputArray_out + n) =
          (((double)2 * n - 1) * inputValue_in * *(p_outputArray_out + n - 1) -
           ((double)n - 1) * *(p_outputArray_out + n - 2)) /
          ((double)n);
    }
  }

  return GCONST_TRUE;
}
