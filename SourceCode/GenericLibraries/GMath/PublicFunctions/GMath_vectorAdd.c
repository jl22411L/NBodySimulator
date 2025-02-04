/*!
 *    @File:         GMath_vectorAdd.c
 *
 *    @Brief:        Function which adds elements of two 3x1 vectors together.
 *
 *    @Date:         04/02/2025
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

int GMath_vectorAdd(double *p_vectorA_in,
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