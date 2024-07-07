/*
 *    @File:         GMath_findUnitVector.c
 *
 *    @Brief:        Finds the unit vector of a vector
 *
 *    @Date:         05/07/2024
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

int GMath_findUnitVector(double *p_vector_in, double *p_vector_out)
{
  /* Define local variables */
  double  vectorMag;
  uint8_t i;

  /* Clear Variables */
  vectorMag = 0;

  /* Iterate through the elements and find the sum of the squares */
  for (i = 0; i < 3; i++)
  {
    /* Sum the square of the input vector elementes */
    vectorMag += *(p_vector_in + i) * *(p_vector_in + i);
  }

  /* Find the square root of the input vector */
  vectorMag = sqrt(vectorMag);

  /* Iterate through the elements and find the output unit vector */
  for (i = 0; i < 3; i++)
  {
    *(p_vector_out + i) = *(p_vector_in + i) / vectorMag;
  }

  return GCONST_TRUE;
}
