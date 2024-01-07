/*
 *    @File:         GParser_loadInt.c
 *
 *    @ Brief:       loads a string into a params struct
 *
 *    @ Date:        23/12/2023
 *
 */

#include <stdio.h>
#include <string.h>

/* Function Includes */
#include "GParser/PrivateFunctions/GParser_PrivateFunctions.h"

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstandDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GConversions/GConversions.h"
#include "GLog/GLog.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_loadFloatArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    float         *p_dataDestination,
    char          *p_dataFromIni,
    int            nCols,
    int            nRows)
{
  /* Defining local variables */
  dictionary *p_dic_tmp;
  char        section_buffer[256];
  char        key_inputBuffer[256];
  char        key_iniBuffer[256];
  char        indexBuffer[256];
  int         col;
  int         row;
  int         i;
  int         j;

  /* Clearing Buffers */
  memset(&section_buffer, 0, 256 * sizeof(char));
  memset(&key_inputBuffer, 0, 256 * sizeof(char));
  memset(&key_iniBuffer, 0, 256 * sizeof(char));
  memset(&indexBuffer, 0, 256 * sizeof(char));
  p_dic_tmp = NULL;
  j         = 0;

  /* Parsing data input for section */
  for (i = 0; *(p_dataFromIni + i) != ':'; i++)
  {
    section_buffer[i] = *(p_dataFromIni + i);
  }

  /* Parsing data input for key */
  for (i; *(p_dataFromIni + i + 1) != '\0'; i++)
  {
    key_inputBuffer[j] = *(p_dataFromIni + i + 1);
    j++;
  }

  /* Find dictionary for coresponding section */
  for (i = 0; i < p_GParser_state->maxNumberSection; i++)
  {
    /* load tempory dictionary */
    p_dic_tmp = *(p_dic + i);

    /* check to see if section name matches */
    if (strcmp(p_dic_tmp->section, section_buffer) == 0)
    {
      break;
    }
  }

  if (i == p_GParser_state->maxNumberSection)
  {
    GMsg(p_dataFromIni);
    GError("Section not found");
  }

  /* Cycle through keys */
  for (i = 0; i < p_dic_tmp->nKeys; i++)
  {
    /* Cycle through key characters */
    for (j = 0; *(*(p_dic_tmp->key + i) + j) != '\0'; j++)
    {
      /* If present, find index */
      if (*(*(p_dic_tmp->key + i) + j) == '[')
      {
        GParser_findIndex(
            p_GParser_state,
            &col,
            &row,
            *(p_dic_tmp->key + i),
            j);
        break;
      }

      /* Load key_iniBuffer */
      key_iniBuffer[j] = *(*(p_dic_tmp->key + i) + j);
    }

    /* Compare keyInput and keyIni */
    if (strcmp(key_iniBuffer, key_inputBuffer) == 0 &&
        p_GParser_state->indexLoaded)
    {
      GConversion_string2float(
          (p_dataDestination + col + row * nCols),
          (p_dic_tmp->value + i));
    }

    /* Clear buffer */
    memset(&key_iniBuffer, 0, 256 * sizeof(char));
  }

  return GCONST_TRUE;
}
