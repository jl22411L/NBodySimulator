/*
 *    @File:         GParser_findIndex.c
 *
 *    @ Description: Finds the index from the ini file for an array
 *
 *    @ Date:        02/01/24
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/DataStructs/Dictionary.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GConversions/GConversions.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

int GParser_findIndex(int *col_out, int *row_out, char *key, int startPosition)
{
  /* Defining Local Vairables */
  char *colValue;
  char *rowValue;
  int   col;
  int   row;
  int   colIndex;
  int   rowIndex;
  int   i;

  /* Decalring Local Variables */
  colValue = (char *)calloc(256, sizeof(char));
  rowValue = (char *)calloc(256, sizeof(char));
  GZero(&colIndex, sizeof(int));
  GZero(&rowIndex, sizeof(int));

  /* Check to make sure there is an index */
  if (*(key + startPosition) != '[')
  {
    GError("Start  position of key is not a '['.");
  }

  /* Loading colValue and rowValue */
  GParser_state.array2D = GCONST_FALSE;
  for (i = startPosition; *(key + i) != '\0'; i++)
  {
    switch (*(key + i))
    {
    case ('['):
      switch (GParser_state.array2D)
      {
      case (GCONST_TRUE):
        /* Setting row values */
        memcpy(rowValue, colValue, 256 * sizeof(char));
        rowIndex = colIndex;

        /* Clearing column values */
        GZero(colValue, char *);
        GZero(&colIndex, int);
        break;
      case (GCONST_FALSE):
        break;
      }
      break;
    case (']'):
      GParser_state.array2D = GCONST_TRUE;
      break;
    case (','):
      break;
    case (' '):
      break;
    case ('\t'):
      break;
    case ('\n'):
      GError("Can't have a new line in index");
      break;
    default:
      switch (GParser_state.array2D)
      {
      case (GCONST_TRUE):
        *(colValue + colIndex) = *(key + i);
        rowIndex++;
        break;
      case (GCONST_FALSE):
        *(colValue + colIndex) = *(key + i);
        colIndex++;
        break;
      }
      break;
    }
  }

  GConversion_string2int(&col, &colValue);
  GConversion_string2int(&row, &rowValue);

  /* Copying data to output */
  memcpy(col_out, &col, sizeof(int *));
  memcpy(row_out, &row, sizeof(int *));

  GParser_state.array2D     = GCONST_FALSE;
  GParser_state.indexLoaded = GCONST_TRUE;

  return GCONST_TRUE;
}