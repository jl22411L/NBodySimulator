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
/* None */

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstandDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GConversions/GConversions.h"
#include "GLog/GLog.h"

int GParser_loadInt(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination,
    char          *p_dataFromIni)
{
  /* Defining local variables */
  dictionary *p_dic_tmp;
  char        section_buffer[256];
  char        key_buffer[256];
  int         numberOfKeys;
  int         i;
  int         j;
  int         k;

  /* Clearing Buffers */
  memset(&section_buffer, 0, 256 * sizeof(char));
  memset(&key_buffer, 0, 256 * sizeof(char));
  *p_dataDestination = 0;
  p_dic_tmp          = NULL;
  j                  = 0;

  /* Parsing data input for section */
  for (i = 0; *(p_dataFromIni + i) != ':'; i++)
  {
    section_buffer[i] = *(p_dataFromIni + i);
  }

  /* Parsing data input for key */
  for (i; *(p_dataFromIni + i) != '\0'; i++)
  {
    key_buffer[j] = *(p_dataFromIni + i + 1);
    j++;
  }

  /* Cycling through sections in dictionary */
  for (i = 0; i < p_GParser_state->maxNumberSection; i++)
  {
    /* load tempory dictionary */
    p_dic_tmp = *(p_dic + i);

    /* If section if found break for loop */
    if (strcmp(p_dic_tmp->section, section_buffer) == 0)
    {
      break;
    }
  }

  /* Check to see if a section was found */
  if (i == p_GParser_state->maxNumberSection)
  {
    GMsg(p_dataFromIni);
    GError("Section not found");
  }

  /* Cycle thorugh keys */
  for (i = 0; i < p_dic_tmp->nKeys; i++)
  {
    /* See if key matches with key inputted */
    if (strcmp(*(p_dic_tmp->key + i), key_buffer) == 0)
    {
      /* If key matches, store convert value to int and store in member */
      GConversion_string2int(p_dataDestination, (p_dic_tmp->value + i));
      break;
    }
  }

  /* Throw an error if no key was found */
  if (i == p_dic_tmp->nKeys)
  {
    GMsg(p_dataFromIni);
    GError("Key not found in section");
  }

  return GCONST_TRUE;
}
