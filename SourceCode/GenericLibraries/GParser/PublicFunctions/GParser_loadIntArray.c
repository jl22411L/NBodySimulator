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
#include "GParser/PrivateInlineFunctions/GParser_findIndex.h"

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstandDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GConversions/GConversions.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_loadIntArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination_out,
    char          *p_dataFromIni_in,
    int            nCols,
    int            nRows)
{
  /* Declaring local variables */
  dictionary *p_dic_tmp;
  char        section_buffer[256];
  char        key_inputBuffer[256];
  char        key_iniBuffer[256];
  char        indexBuffer[256];
  int16_t     col;
  int16_t     row;
  int16_t     i;
  int16_t     j;

  /* Clearing Buffers */
  GZero(&section_buffer, char[256]);
  GZero(&key_inputBuffer, char[256]);
  GZero(&key_iniBuffer, char[256]);
  GZero(&indexBuffer, char[256]);
  p_dic_tmp = NULL;

  /* Defining local variables */
  i = 0;
  j = 0;

  /* Parsing data input for section */
  for (i = 0; *(p_dataFromIni_in + i) != ':'; i++)
  {
    section_buffer[i] = *(p_dataFromIni_in + i);
  }

  /* Parsing data input for key */
  for (i; *(p_dataFromIni_in + i + 1) != '\0'; i++)
  {
    key_inputBuffer[j] = *(p_dataFromIni_in + i + 1);
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

  /* Check to see if section exists */
  if (i == p_GParser_state->maxNumberSection)
  {
    GError("Section not found: %s", section_buffer);
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
            *(p_dic_tmp->key + i),
            j,
            &col,
            &row);
        break;
      }

      /* Load key_iniBuffer */
      key_iniBuffer[j] = *(*(p_dic_tmp->key + i) + j);
    }

    /* Compare keyInput and keyIni */
    if (strcmp(key_iniBuffer, key_inputBuffer) == 0 &&
        p_GParser_state->indexLoaded)
    {
      GConversion_string2int(
          (p_dataDestination_out + col + row * nCols),
          (p_dic_tmp->value + i));
    }

    /* Clear buffer */
    GZero(&key_iniBuffer, char[256]);
  }

  return GCONST_TRUE;
}
