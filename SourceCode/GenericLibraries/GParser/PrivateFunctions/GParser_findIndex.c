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

/*
 *  Refer to respective header file for function description
 */
int GParser_findIndex(
    GParser_State *p_GParser_state,
    int           *col_out,
    int           *row_out,
    char          *key,
    int            startPosition)
{
  /* Defining Local Vairables */
  char *colValue;
  char *rowValue;
  int   col;
  int   row;
  int   index;
  int   i;

  /* Decalring Local Variables */
  colValue = (char *)calloc(256, sizeof(char));
  rowValue = (char *)calloc(256, sizeof(char));
  GZero(&index, sizeof(int));

  /* Check to make sure there is an index */
  if (*(key + startPosition) != '[')
  {
    GError("Start  position of key is not a '['.");
  }

  /* Loading colValue and rowValue */
  p_GParser_state->array2D = GCONST_FALSE;
  for (i = startPosition; *(key + i) != '\0'; i++)
  {
    switch (*(key + i))
    {
    case ('['):
      /* Check to see if array is 1D or 2D */
      switch (p_GParser_state->array2D)
      {
      /* If Array is 2D: */
      case (GCONST_TRUE):
        /* Copying col values to row values */
        memcpy(rowValue, colValue, 256 * sizeof(char));

        /* Clearing column values */
        GZero(colValue, char *);
        GZero(&index, int);
        break;
      /* If Array is 1D: */
      case (GCONST_FALSE):
        /* DO NOTHING */
        break;
      }
      break;
    case (']'):
      /* Update array2D flag */
      p_GParser_state->array2D = GCONST_TRUE;
      break;
    case (','):
      /* DO NOTHING */
      break;
    case (' '):
      /* DO NOTHING */
      break;
    case ('\t'):
      /* DO NOTHING */
      break;
    case ('\n'):
      GError("Can't have a new line in index");
      break;
    default:
      /* Loading column */
      *(colValue + index) = *(key + i);
      index++;
      break;
    }
  }

  GConversion_string2int(&col, &colValue);
  GConversion_string2int(&row, &rowValue);

  /* Copying data to output */
  memcpy(col_out, &col, sizeof(int *));
  memcpy(row_out, &row, sizeof(int *));

  p_GParser_state->array2D     = GCONST_FALSE;
  p_GParser_state->indexLoaded = GCONST_TRUE;

  /* Freeing heap memory */
  free(colValue);
  free(rowValue);

  return GCONST_TRUE;
}