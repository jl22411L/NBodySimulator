/*
 *    @File:         GParser_loadDictionary.c
 *
 *    @ Brief:       Loads dictionary with information from a section.
 *
 *    @ Date:        18/12/2023
 *
 */

#include <stdlib.h>
#include <string.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

/*
 *  Refer to respective header file for function description
 */
dictionary GParser_loadDictionary(GParser_State *p_GParser_state)
{
  /* Defining local variables */
  dictionary dic_section;
  int        keyIndex;
  int        valueIndex;
  int        i;
  int        j;

  /* Clear Dictionary */
  GZero(&dic_section, dictionary);

  /* Set indexes to 0 */
  keyIndex   = 0;
  valueIndex = 0;

  /* Assign memory for dictionary */
  dic_section.section =
      (char *)calloc(p_GParser_state->sectionSize + 1, sizeof(char));

  /* Setting the section name to dictionary */
  for (i = 0; i < p_GParser_state->sectionIndex; i++)
  {
    dic_section.section[i] = *(p_GParser_state->sectionBuffer + i);
  }

  /* Loading the keys and values into dictionary */
  for (i = 0; i < p_GParser_state->sizeIndex; i++)
  {
    /* Fill tmp Key Buffer */
    for (j = 0; j < p_GParser_state->keySize[i]; j++)
    {
      dic_section.key[i][j] = p_GParser_state->keyBuffer[keyIndex];
      keyIndex++;
    }

    /* Fill tmp Value Buffer */
    for (j = 0; j < p_GParser_state->valueSize[i]; j++)
    {
      dic_section.value[i][j] = p_GParser_state->valueBuffer[valueIndex];
      valueIndex++;
    }

    /* set number of keys in a section */
    dic_section.nKeys = p_GParser_state->sizeIndex;
  }

  return dic_section;
}
