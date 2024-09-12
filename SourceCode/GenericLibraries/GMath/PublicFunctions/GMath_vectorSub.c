/*
 *    @File:         GMath_vectorSubtraction.c
 *
 *    @Brief:        Subtracts vector b from vector a. Essentially an optimised
 *                   GMath_matSub() but for 3x1 vectors.
 *
 *    @Date:         09/09/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GMath_vectorSub(
    double *p_vectorA_in,
    double *p_vectorB_in,
    double *p_vectorC_out)
{
  /* Declare local variables */
  int8_t i;

  /* Iterate through elements of the vector A and B, finding the difference */
  for (i = 0; i < 3; i++)
  {
    *(p_vectorC_out + i) = *(p_vectorA_in + i) - *(p_vectorB_in + i);
  }

  return GCONST_TRUE;
}
