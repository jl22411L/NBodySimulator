/*
 *    @File:         GIntegral_3x1Double.c
 *
 *    @ Brief:       Function to integrate a double array that has dimensions
 * 3x1
 *
 *    @ Date:        29/01/2024
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

int GIntegral_3x1Double(
    double *p_array_out,
    double *p_arrayDerivitive_in,
    double  timeStep_in)
{

  /* Applying Eulers Method */
  *(p_array_out + 0) += *(p_arrayDerivitive_in + 0) * timeStep_in;
  *(p_array_out + 1) += *(p_arrayDerivitive_in + 1) * timeStep_in;
  *(p_array_out + 2) += *(p_arrayDerivitive_in + 2) * timeStep_in;
  *(p_array_out + 3) += *(p_arrayDerivitive_in + 3) * timeStep_in;

  return GCONST_TRUE;
}