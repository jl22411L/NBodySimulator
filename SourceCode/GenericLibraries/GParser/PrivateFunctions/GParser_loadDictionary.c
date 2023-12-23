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

dictionary *GParser_loadDictionary(GParser_State *p_stateStruct)
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
      (char *)calloc(p_stateStruct->sectionSize + 1, sizeof(char));

  p_dic_section->key =
      (char **)calloc(p_stateStruct->sizeIndex, sizeof(char *));

  p_dic_section->value =
      (char **)calloc(p_stateStruct->sizeIndex, sizeof(char *));

  for (i = 0; i < p_stateStruct->sizeIndex; i++)
  {
    *(p_dic_section->key + i) =
        (char *)calloc(p_stateStruct->keySize[i] + 1, sizeof(char));

    *(p_dic_section->value + i) =
        (char *)calloc(p_stateStruct->valueSize[i] + 1, sizeof(char));
  }

  /* Setting the section name to dictionary */
  keyIndex   = 0;
  valueIndex = 0;
  for (i = 0; i < p_stateStruct->sectionIndex; i++)
  {
    *(p_dic_section->section + i) = *(p_stateStruct->sectionBuffer + i);
  }

  /* Loading the keys and values into dictionary */
  for (i = 0; i < p_stateStruct->sizeIndex; i++)
  {
    /* Assign memory for tmp buffers */
    tmpKeyBuffer = (char *)calloc(p_stateStruct->keySize[i] + 1, sizeof(char));
    tmpValueBuffer =
        (char *)calloc(p_stateStruct->valueSize[i] + 1, sizeof(char));

    /* Fill tmp Key Buffer */
    for (j = 0; j < p_stateStruct->keySize[i]; j++)
    {
      *(tmpKeyBuffer + j) = p_stateStruct->keyBuffer[keyIndex];
      keyIndex++;
    }

    /* Fill tmp Value Buffer */
    for (j = 0; j < p_stateStruct->valueSize[i]; j++)
    {
      *(tmpValueBuffer + j) = p_stateStruct->valueBuffer[valueIndex];
      valueIndex++;
    }

    /* copy tmp key buffer to the key member*/
    strcpy(*(p_dic_section->key + i), tmpKeyBuffer);

    /* copy tmp key buffer to the key member*/
    strcpy(*(p_dic_section->value + i), tmpValueBuffer);

    /* set number of keys in a section */
    p_dic_section->nKeys = p_stateStruct->sizeIndex;
  }

  return p_dic_section;
}