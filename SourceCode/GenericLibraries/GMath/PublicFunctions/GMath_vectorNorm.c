/*
 *    @File:         GMath_vectorNorm3x1.c
 *
 *    @ Brief:       Finds the norm of a 3x1 vector
 *
 *    @ Date:        17/02/2024
 *
 */

#include <math.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"

int GMath_vectorNorm(double *p_outputVector_out,
                     double *p_vector_in,
                     int     vectorSize_in)
{
  /* Declarinng local variables */
  double magnitude;
  int    i;

  /* Find the magnitude of the vector */
  GMath_vectorMag(&magnitude, p_vector_in, vectorSize_in);

  /* Cycle through each element in the input array and normalise */
  for (i = 0; i < vectorSize_in; i++)
  {
    *(p_outputVector_out + i) = *(p_vector_in + i) / magnitude;
  }

  return GCONST_TRUE;
}