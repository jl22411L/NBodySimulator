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

/*
 *  Refer to respective header file for function description
 */
dictionary *GParser_loadDictionary(GParser_State *p_GParser_state)
{
  int         i;
  int         j;
  int         keyIndex;
  int         valueIndex;
  char       *tmpKeyBuffer;
  char       *tmpValueBuffer;
  dictionary *p_dic_section;

  /* Allocating memory */
  p_dic_section = (dictionary *)calloc(1, sizeof(dictionary *));

  p_dic_section->section =
      (char *)calloc(p_GParser_state->sectionSize + 1, sizeof(char));

  p_dic_section->key =
      (char **)calloc(p_GParser_state->sizeIndex, sizeof(char *));

  p_dic_section->value =
      (char **)calloc(p_GParser_state->sizeIndex, sizeof(char *));

  for (i = 0; i < p_GParser_state->sizeIndex; i++)
  {
    *(p_dic_section->key + i) =
        (char *)calloc(p_GParser_state->keySize[i] + 1, sizeof(char));

    *(p_dic_section->value + i) =
        (char *)calloc(p_GParser_state->valueSize[i] + 1, sizeof(char));
  }

  /* Setting the section name to dictionary */
  keyIndex   = 0;
  valueIndex = 0;
  for (i = 0; i < p_GParser_state->sectionIndex; i++)
  {
    *(p_dic_section->section + i) = *(p_GParser_state->sectionBuffer + i);
  }

  /* Loading the keys and values into dictionary */
  for (i = 0; i < p_GParser_state->sizeIndex; i++)
  {
    /* Assign memory for tmp buffers */
    tmpKeyBuffer =
        (char *)calloc(p_GParser_state->keySize[i] + 1, sizeof(char));
    tmpValueBuffer =
        (char *)calloc(p_GParser_state->valueSize[i] + 1, sizeof(char));

    /* Fill tmp Key Buffer */
    for (j = 0; j < p_GParser_state->keySize[i]; j++)
    {
      *(tmpKeyBuffer + j) = p_GParser_state->keyBuffer[keyIndex];
      keyIndex++;
    }

    /* Fill tmp Value Buffer */
    for (j = 0; j < p_GParser_state->valueSize[i]; j++)
    {
      *(tmpValueBuffer + j) = p_GParser_state->valueBuffer[valueIndex];
      valueIndex++;
    }

    /* copy tmp key buffer to the key member*/
    strcpy(*(p_dic_section->key + i), tmpKeyBuffer);

    /* copy tmp key buffer to the key member*/
    strcpy(*(p_dic_section->value + i), tmpValueBuffer);

    /* set number of keys in a section */
    p_dic_section->nKeys = p_GParser_state->sizeIndex;
  }

  /* Freeing Heap Memory */
  // free(p_dic_section);
  // free(p_dic_section->section);
  // free(p_dic_section->key);
  // free(p_dic_section->value);

  // for (i = 0; i < p_GParser_state->sizeIndex; i++)
  // {
  //   free(*(p_dic_section->key + i));
  //   free(*(p_dic_section->value + i));
  //   free(tmpKeyBuffer);
  //   free(tmpValueBuffer);
  // }

  return p_dic_section;
}