/*
 *    @File:         GConversion_string2float.c
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
#include "GLog/GLog.h"

GConversion_string2uint(int *p_dataDestination, char **p_dataSource)
{
  /* Defining local variables */
  int  number;
  char cursor;
  int  sign;
  int  i;

  /* Checking the sign of the input */
  cursor = *(*(p_dataSource) + 0);
  switch (cursor)
  {
  case ('-'):
    GError("Unsigned int can not have a negative sign");
    break;
  }

  /* Finding the integer value and shifting left */
  number = 0;
  for (i; (cursor = *(*(p_dataSource) + i)) != '\0'; i++)
  {

    number = number * 10 + (int)(cursor - '0');
  }

  /* Outputting result */
  *p_dataDestination = number;

  return GCONST_TRUE;
}