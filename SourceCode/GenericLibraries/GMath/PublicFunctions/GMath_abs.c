/*
 *    @File:         GMath_abs.c
 *
 *    @Brief:        Finds the absolute value of an input value.
 *
 *    @Date:         23/09/2024
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

int GMath_abs(double inputValue_in, double *p_outputValue_out)
{
  /* Declare local variables */
  /* None */

  /* Always output postiive value. */
  if (inputValue_in < 0)
  {
    *(p_outputValue_out) = -1.0 * inputValue_in;
  }
  else
  {
    *(p_outputValue_out) = inputValue_in;
  }

  return GCONST_TRUE;
}
