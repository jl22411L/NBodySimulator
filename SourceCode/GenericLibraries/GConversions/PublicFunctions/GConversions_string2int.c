/*
 *    @File:         GConversions_string2float.c
 *
 *    @ Brief:       Converts strings to floats
 *
 *    @ Date:        23/12/2023
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

GConversions_string2int(int *p_dataDestination_out, char *p_dataSource_in)
{
  /* Defining local variables */
  int  number;
  char cursor;
  int  sign;
  int  i;

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
  for (i; (cursor = *(p_dataSource_in + i)) != '\0'; i++)
  {
    number = number * 10 + (int)(cursor - '0');
  }

  /* Outputting result */
  *p_dataDestination_out = sign * number;

  return GCONST_TRUE;
}
