/*
 *    @File:         GArchive_checkFileExists.c
 *
 *    @Brief:        Checks if a file exists.
 *
 *    @Date:         01/06/2024
 *
 */

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GArchive_checkFileExists(const char *p_filename_in)
{
  /* Declaring local variables */
  FILE *file;

  /* Open file in read mode */
  file = fopen(p_filename_in, "r");

  /* If file is NULL then file does not exist, and hence return false */
  if (file == NULL)
  {
    return GCONST_FALSE;
  }

  return GCONST_TRUE;
}
