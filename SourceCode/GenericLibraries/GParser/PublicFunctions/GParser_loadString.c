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
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

/*
 * Refer to respective header file for function description
 */
int GParser_loadString(
    GParser_State *p_GParser_state,
    dictionary    *p_dic,
    char          *p_dataDestination_out,
    char          *p_dataFromIni_in)
{
  /* Declaring local variables */
  char section_buffer[256];
  char key_buffer[256];
  int  numberOfKeys;
  int  dictionaryNumber;
  int  i;
  int  j;

  /* Clearing Buffers */
  GZero(&section_buffer, char[256]);
  GZero(&key_buffer, char[256]);

  /* Defining Local variables */
  dictionaryNumber = -1;
  i                = 0;
  j                = 0;

  /* Parsing data input for section */
  for (i = 0; *(p_dataFromIni_in + i) != ':'; i++)
  {
    section_buffer[i] = *(p_dataFromIni_in + i);
  }

  /* Parsing data input for key */
  for (i; *(p_dataFromIni_in + i + 1) != '\0'; i++)
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
      dictionaryNumber = i;
      break;
    }
  }

  /* Check if section was found */
  if (i == p_GParser_state->maxNumberSection)
  {
    GError("Section not found: %s", section_buffer);
  }

  /* Check dictionary number is valid */
  if (dictionaryNumber < 0)
  {
    GError("Dictionary Number is not valid, %d", dictionaryNumber);
  }

  /* Cycle thorugh keys */
  for (i = 0; i < (p_dic + dictionaryNumber)->nKeys; i++)
  {
    /* See if key matches with key inputted */
    if (strcmp(*((p_dic + dictionaryNumber)->key + i), key_buffer) == 0)
    {
      /* If key matches, store value of key */
      strcpy(p_dataDestination_out, *((p_dic + dictionaryNumber)->value + i));
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
