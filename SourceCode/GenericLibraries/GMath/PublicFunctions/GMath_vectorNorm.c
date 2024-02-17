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

int GMath_vectorNorm(
    double *outputVector_out,
    double *vector_in,
    int     vectorSize_in)
{
  /* Declarinng local variables */
  double magnitude;
  int    i;

  /* Find the magnitude of the vector */
  GMath_vectorMag(&magnitude, vector_in, vectorSize_in);

  /* Cycle through each element in the input array and normalise */
  for (i = 0; i < vectorSize_in; i++)
  {
    *(outputVector_out + i) = *(vector_in + i) / magnitude;
  }

  return GCONST_TRUE;
}