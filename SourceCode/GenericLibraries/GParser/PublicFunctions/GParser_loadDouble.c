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
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GConversions/GConversions.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_loadDouble(
    GParser_State *p_GParser_state,
    dictionary    *p_dic,
    double        *p_dataDestination_out,
    char          *p_dataFromIni_in)
{
  /* Defining local variables */
  char section_buffer[256];
  char key_buffer[256];
  int  dictionaryNumber;
  int  i;
  int  j;

  /* Clearing Buffers */
  GZero(&section_buffer, char[256]);
  GZero(&key_buffer, char[256]);

  /* Declaring local variables */
  dictionaryNumber = -1;
  i                = 0;
  j                = 0;

  /* Parsing data input for section */
  for (i = 0; *(p_dataFromIni_in + i) != ':'; i++)
  {
    section_buffer[i] = *(p_dataFromIni_in + i);
  }

  /* Parsing data input for key */
  for (i; *(p_dataFromIni_in + i) != '\0'; i++)
  {
    key_buffer[j] = *(p_dataFromIni_in + i + 1);
    j++;
  }

  /* Cycling through sections in dictionary */
  for (i = 0; i < p_GParser_state->maxNumberSection; i++)
  {
    /* check to see if section name matches */
    if (strcmp((p_dic + i)->section, section_buffer) == 0)
    {
      /* if key was found, break main for loop */
      dictionaryNumber = i;
      break;
    }
  }

  /* Check to see if section was found */
  if (i == p_GParser_state->maxNumberSection)
  {
    GError("Section not found: %s", section_buffer);
  }

  /* Check to make sure dictionary number was assigned correctly */
  if (dictionaryNumber < 0)
  {
    GError("Invalid dictionaryNumber: %d", dictionaryNumber);
  }

  /* Cycle thorugh keys */
  for (i = 0; i < (p_dic + dictionaryNumber)->nKeys; i++)
  {
    /* See if key matches with key inputted */
    if (strcmp(((p_dic + dictionaryNumber)->key[i]), key_buffer) == 0)
    {
      /* If key matches, store convert value to int and store in member */
      GConversion_string2double(
          p_dataDestination_out,
          &((p_dic + dictionaryNumber)->value[i][0]));
      break;
    }
  }

  /* Throw an error if no key was found */
  if (i == (p_dic + dictionaryNumber)->nKeys)
  {
    GError("Key not found in section: %s", key_buffer);
  }

  return GCONST_TRUE;
}
