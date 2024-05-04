/*
 *    @File:         GConversions_string2int8.c
 *
 *    @ Brief:       Converts strings to 8 bit integers
 *
 *    @ Date:        23/12/2023
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

GConversions_string2int8(int8_t *p_dataDestination_out, char *p_dataSource_in)
{
  /* Defining local variables */
  int8_t number;
  char   cursor;
  int8_t sign;
  int8_t i;

  /* Checking the sign of the input */
  cursor = *(p_dataSource_in + 0);
  switch (cursor)
  {
  case ('-'):
    sign = -1;
    i    = 1;
    break;
  case ('+'):
    sign = 1;
    i    = 1;
    break;
  default:
    sign = 1;
    i    = 0;
    break;
  }

  /* Finding the integer value and shifting left */
  number = 0;
  for (i; cursor = *(p_dataSource_in + i) != '\0'; i++)
  {
    number = number * 10 + (int)(cursor - '0');
  }

  /* Outputting result */
  *p_dataDestination_out = sign * number;

  return GCONST_TRUE;
}
