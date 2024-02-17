/*
 *    @File:         GMath_vectorMag.c
 *
 *    @ Brief:       Finds the magnitude of a vector
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

int GMath_vectorMag(
    double *outputValue_out,
    double *vector_in,
    int     vectorSize_in)
{
  /* Declaring local variables */
  int    i;
  double squareSums;

  /* Clearing local variables */
  squareSums = 0;

  /* Iterate through vector input suming the square into squareSums */
  for (i = 0; i < vectorSize_in; i++)
  {
    squareSums += (*(vector_in + i)) * (*(vector_in + i));
  }

  /* Find the square root of the total sum of squares and set to output */
  *outputValue_out = sqrt(squareSums);

  return GCONST_TRUE;
}