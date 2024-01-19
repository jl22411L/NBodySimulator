/*
 *    @File:         GParser_findIndex.h
 *
 *    @ Description: Finds the index from the ini file for an array
 *
 *    @ Date:        02/01/24
 *
 */

#ifndef H_GPARSER_FIND_INDEX_H
#define H_GPARSER_FIND_INDEX_H

#ifdef __cplusplus
extern "C" {
#endif

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

/*!
 *
 * @description: This functionb finds the index from a key in an ini file. This
 *               is called once the key from the correct section has been
 *               found. It first assumes that the array is 1D and finds its
 *               column position. If there are two '[', it is assumed that the
 *               array is 2D. Hence the column value is moved to the row value,
 *               and cleared to make way for the 2D column value. Once this is
 *               done, the values are converted from there respective string
 *               values to in values.
 *
 *               If the array is 1D, the row value is set to 0. Currently, can
 *               not do arrays with dimensions greater then 2D.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    p_key_in
 *               pointer to the key value for which the index is trying to be
 *               found.
 *
 * @param[in]    startPosition
 *               Integer which indicated where the first '[' is located in the
 *               key. This is so that only the index part of the key is parsed.
 *
 * @param[out]   p_col_out
 *               pointer to where the output value for the column index should
 *               be stored.
 *
 * @param[out]   p_row_out
 *               pointer to where the output value for the row index should be
 *               stored.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 */
static inline int GParser_findIndex(
    GParser_State *p_GParser_state,
    char          *p_key_in,
    int16_t        startPosition_in,
    int16_t       *p_col_out,
    int16_t       *p_row_out)
{
  /* Defining Local Vairables */
  char   *colValue;
  char   *rowValue;
  int     col;
  int     row;
  int32_t index;
  int     i;

  /* Decalring Local Variables */
  colValue = (char *)calloc(256, sizeof(char));
  rowValue = (char *)calloc(256, sizeof(char));
  GZero(&index, sizeof(int));

  /* Check to make sure there is an index */
  if (*(p_key_in + startPosition_in) != '[')
  {
    GError("Start  position of key is not a '['.");
  }

  /* Loading colValue and rowValue */
  p_GParser_state->array2D = GCONST_FALSE;
  for (i = startPosition_in; *(p_key_in + i) != '\0'; i++)
  {
    switch (*(p_key_in + i))
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
      *(colValue + index) = *(p_key_in + i);
      index++;
      break;
    }
  }

  /* Take the string values and output to integer values*/
  GConversion_string2int(&col, &colValue);
  GConversion_string2int(&row, &rowValue);

  /* Copying data to output */
  memcpy(p_col_out, &col, sizeof(int *));
  memcpy(p_row_out, &row, sizeof(int *));

  p_GParser_state->array2D     = GCONST_FALSE;
  p_GParser_state->indexLoaded = GCONST_TRUE;

  /* Freeing heap memory */
  free(colValue);
  free(rowValue);

  return GCONST_TRUE;
}

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_FIND_INDEX_H */