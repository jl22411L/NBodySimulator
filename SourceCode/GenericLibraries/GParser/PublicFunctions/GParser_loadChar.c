/*
 *    @File:         GParser_loadString.c
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
#include "GLog/GLog.h"

int GParser_loadChar(char *p_dataDestination, char *p_dataFromIni, dictionary **p_dic)
{
  /* Defining local variables */
  dictionary *p_dic_tmp;
  char        section_buffer[256];
  char        key_buffer[256];
  int         numberOfKeys;
  int         i;
  int         j;

  /* Clearing Buffers */
  memset(&section_buffer, 0, 256 * sizeof(char));
  memset(&key_buffer, 0, 256 * sizeof(char));
  p_dic_tmp = NULL;

  /* Declaring local variables */
  *p_dataDestination = '\0';
  i                  = 0;
  j                  = 0;

  /* Parsing data input for section */
  while (!(*(p_dataFromIni + i) == ':'))
  {
    section_buffer[i] = *(p_dataFromIni + i);
    i++;
  }

  /* Parsing data input for key */
  while (!(*(p_dataFromIni + i + 1) == '\0'))
  {
    key_buffer[j] = *(p_dataFromIni + i + 1);
    j++;
    i++;
  }

  /* Cycling through sections in dictionary */
  for (i = 0; i < GParser_state.maxNumberSection; i++)
  {
    /* load tempory dictionary */
    p_dic_tmp = *(p_dic + i);

    /* check to see if section name matches */
    if (strcmp(p_dic_tmp->section, section_buffer) == 0)
    {
      /* If section was found break for loop */
      break;
    }
  }

  /* If section was not found throw an error */
  if (i == GParser_state.maxNumberSection)
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
      /* If key matches, store value of key */
      *p_dataDestination = (char)*(p_dic_tmp->value + i);
      break;
    }
  }

  /* Throw an error if no key was found */
  if (i == p_dic_tmp->nKeys)
  {
    GMsg(p_dataFromIni);
    GError("Key not found in section");
  }

  /* Check that parameter was loaded and if not return GCONST_FALSE */
  if (*p_dataDestination == '\0')
  {
    GError("Data was not loaded in corrcetly");
  }

  return GCONST_TRUE;
}
