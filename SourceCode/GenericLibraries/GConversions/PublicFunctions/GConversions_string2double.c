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

int GConversions_string2double(
    double *p_dataDestination_out,
    char   *p_dataSource_in)
{
  /* Defining local variables */
  double integer;
  double decimal;
  char   cursor;
  int    sign;
  int    endOfString;
  int    decimalPosition;
  int    sizeString;
  int    i;

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

  /* Find position of decimal and number of elements in string */
  decimalPosition = -1;
  for (sizeString = 0; (cursor = *(p_dataSource_in + sizeString)) != '\0';
       sizeString++)
  {
    if (cursor == '.')
    {
      decimalPosition = sizeString;
    }
  }

  /* It is assumed that if there is no decimal point that it is a float */
  if (decimalPosition == -1)
  {
    decimalPosition = sizeString;
  }

  /* Finding the integer value and shifting left */
  integer = 0;
  for (i; i < decimalPosition; i++)
  {
    cursor  = *(p_dataSource_in + i);
    integer = integer * 10 + (cursor - '0');
  }

  /* Finding the decimal value and shifting right */
  decimal = 0;
  for (i = sizeString - 1; i > decimalPosition; i--)
  {
    cursor  = *(p_dataSource_in + i);
    decimal = decimal / 10.0 + (float)(cursor - '0');
  }

  /* Outputting result */
  *p_dataDestination_out = sign * (integer + decimal / 10);

  return GCONST_TRUE;
}
