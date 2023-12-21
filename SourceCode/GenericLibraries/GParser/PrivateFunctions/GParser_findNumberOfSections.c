/*
 *    @File:         GParser_findNumberOfSections.c
 *
 *    @ Brief:       Finds the number of sections within a file
 *
 *    @ Date:        19/12/2023
 *
 */

#include <stdio.h>

/* Function Includes */
#include "GParser/PrivateFunctions/GParser_PrivateFunctions.h"

/* Structure Include */
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int GParser_findNumberOfSections(FILE *file, uint8_t *p_maxNumberSection_out)
{
  char    cursor;
  uint8_t sectionOpenCounter;
  uint8_t sectionCloseCounter;

  sectionOpenCounter  = 0;
  sectionCloseCounter = 0;
  while ((cursor = fgetc(file)) != EOF)
  {
    switch (cursor)
    {
    case ('['):
      sectionOpenCounter++;
      break;
    case (']'):
      sectionCloseCounter++;
      break;
    }
  }

  if (sectionOpenCounter != sectionCloseCounter)
  {
    GError("The amount of [ does not match the amount of ] in ini file");
  }

  rewind(file);

  *p_maxNumberSection_out = sectionOpenCounter;

  return GCONST_TRUE;
}
