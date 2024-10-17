/*
 *    @File:         GMath_factorial.c
 *
 *    @Brief:        Finds the factorial for a particular inputted integer.
 *
 *    @Date:         29/09/2024
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

int GMath_factorial(uint16_t inputInteger_in, uint16_t *p_outputValue_out)
{
  /* Declare local variables */
  uint16_t i;

  /* Set initial value of factorial */
  *(p_outputValue_out) = 1;

  /* Multiply by all the integers less then inputInteger greater then 0 */
  for (i = 1; i <= inputInteger_in; i++)
  {
    *(p_outputValue_out) *= i;
  }

  return GCONST_TRUE;
}
