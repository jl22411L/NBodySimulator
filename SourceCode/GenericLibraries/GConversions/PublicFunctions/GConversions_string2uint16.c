/*
 *    @File:         GConversions_string2uint8.c
 *
 *    @ Brief:       Converts strings to unsigned 8 bit integers
 *
 *    @ Date:        29/04/2024
 *
 */

#include <stdint.h>
#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

GConversions_string2uint16(
    uint16_t *p_dataDestination_out,
    char     *p_dataSource_in)
{
  /* Defining local variables */
  uint16_t outputNumber;
  char     cursor;
  int16_t  i;

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
  for (i; *(p_dataSource_in + i) != '\0'; i++)
  {
    /* Move cursor */
    cursor = *(p_dataSource_in + i);

    /* If floating point detected break */
    if (cursor == ".")
    {
      break;
    }

    /* Subtract the '0' charecter to get value as integer */
    outputNumber = outputNumber * 10 + (uint16_t)(cursor - '0');
  }

  /* Outputting result */
  *p_dataDestination_out = (uint16_t)outputNumber;

  return GCONST_TRUE;
}
