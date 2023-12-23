/*
 *    @File:         GParser_loadFloat.c
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

int GParser_loadDouble(
    double      *p_dataDestination,
    char        *p_dataFromIni,
    dictionary **p_dic)
{
  /* Defining local variables */
  dictionary *p_dic_tmp;
  char        section_buffer[256];
  char        key_buffer[256];
  int         numberOfKeys;
  float       integerPart;
  float       decimalPart;
  int         currentLoadingInteger;
  int         i;
  int         j;
  int         k;

  /* Clearing Buffers */
  memset(&section_buffer, 0, 256 * sizeof(char));
  memset(&key_buffer, 0, 256 * sizeof(char));
  p_dic_tmp = NULL;

  /* Declaring local variables */
  i                     = 0;
  j                     = 0;
  k                     = 0;
  integerPart           = 0;
  decimalPart           = 0;
  currentLoadingInteger = 1;

  /* Parsing data input for section */
  for (i = 0; *(p_dataFromIni + i) != ':'; i++)
  {
    section_buffer[i] = *(p_dataFromIni + i);
  }

  /* Parsing data input for key */
  for (i = i; *(p_dataFromIni + i) != '\0'; i++)
  {
    key_buffer[j] = *(p_dataFromIni + i + 1);
    j++;
  }

  /* Cycling through sections in dictionary */
  for (i = 0; i < GParser_state.maxNumberSection; i++)
  {
    /* load tempory dictionary */
    p_dic_tmp = *(p_dic + i);

    /* check to see if section name matches */
    if (strcmp(p_dic_tmp->section, section_buffer) == 0)
    {

      /* Cycle thorugh keys */
      for (j = 0; j < p_dic_tmp->nKeys; j++)
      {
        /* See if key matches with key inputted */
        if (strcmp(*(p_dic_tmp->key + j), key_buffer) == 0)
        {
          /* If key matches, store convert value to int and store in member */
          GConversion_string2double(p_dataDestination, (p_dic_tmp->value + j));
          break;
        }
      }

      /* Throw an error if no key was found */
      if (j == p_dic_tmp->nKeys)
      {
        GMsg(p_dataFromIni);
        GError("Key not found in section");
      }

      /* if key was found, break main for loop */
      break;
    }
  }

  if (i == GParser_state.maxNumberSection)
  {
    GMsg(p_dataFromIni);
    GError("Section not found");
  }

  return GCONST_TRUE;
}
