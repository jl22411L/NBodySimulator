/*
 *    @File:         GConversion_string2uint8.c
 *
 *    @ Brief:       Converts strings to unsigned 8 bit integers
 *
 *    @ Date:        29/04/2024
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
#include "GLog/GLog.h"

GConversion_string2uint8(uint8_t *p_dataDestination_out, char *p_dataSource_in)
{
  /* Defining local variables */
  uint8_t outputNumber;
  char    cursor;
  int8_t  i;

  /* Checking the sign of the input */
  cursor = *(p_dataSource_in + 0);
  switch (cursor)
  {
  case ('-'):
    GError("Can't have a '-' when trying to convert to unsigned int");
    break;
  case ('+'):
    i = 1;
    break;
  default:
    i = 0;
    break;
  }

  /* Finding the integer value and shifting left */
  outputNumber = 0;
  for (i; cursor = *(p_dataSource_in + i) != '\0'; i++)
  {
    outputNumber = outputNumber * 10 + (uint8_t)(cursor - '0');
  }

  /* Outputting result */
  *p_dataDestination_out = outputNumber;

  return GCONST_TRUE;
}
