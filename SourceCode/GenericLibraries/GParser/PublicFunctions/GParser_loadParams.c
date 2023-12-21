/*
 *   @File:         GParser_loadParams
 *
 *   @ Brief:       Loads Params from ini file into a dictionary
 *
 *   @ Description: //TODO
 *
 */

#include <stdint.h>
#include <stdio.h>

/* Function Includes */
#include "GParser/PrivateFunctions/GParser_PrivateFunctions.h"
#include "GParser/PublicFunctions/GParser_PublicFunctions.h"

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstandDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

int GParser_loadParams(const char *filePath, dictionary **p_dic)
{
  /* Defining Local Variables */
  FILE         *file;
  GParser_State GParser_state;
  uint8_t       state;

  char cursor;

  /* Clearing Data values */
  GZero(&GParser_state, GParser_State);

  /* Initializing Values */
  GParser_state.sectionCounter = 0;
  GParser_state.keyIndex       = 0;
  GParser_state.valueIndex     = 0;
  GParser_state.sizeIndex      = 0;

  /* Opening file */
  file = fopen(filePath, "r");

  if (file == NULL)
  {
    GError("No file was able to open");
  }

  /* Finding number of Sections */
  GParser_findNumberOfSections(file, &GParser_state.maxNumberSection);

  /* Assigning Memory to Dictionary */
  p_dic = (dictionary **)calloc(
      GParser_state.maxNumberSection,
      sizeof(dictionary *));

  /* Run through file */
  state = GPARSER_STATE_WAITING_FOR_COMMAND;
  while (!(state == GPARSER_STATE_FINISHED))
  {
    /* Get next cursor*/
    cursor = fgetc(file);
    printf("%c", cursor);

    if (cursor == EOF)
    {
      state = GPARSER_STATE_FINISHED;

      GParser_state.loadDictionaryEnabled = GCONST_TRUE;
    }

    /* Check the state */
    switch (state)
    {
    case (GPARSER_STATE_WAITING_FOR_COMMAND):
      GParser_waitingForCommand(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_WAITING_NEWLINE):
      GParser_waitingForNewLine(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_COMMENT):
      GParser_comment(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_SECTION):
      GParser_loadingSection(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_KEY):
      GParser_loadingKey(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_KEY_WAITING_FOR_EQUALS):
      GParser_waitingEquals(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_WAITING_VALUE):
      GParser_waitingValue(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_VALUE):
      GParser_loadingValue(&state, &GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_STRING_VALUE):
      GParser_loadingStringValue(&state, &GParser_state, cursor);
      break;
    }
    char a = cursor;

    if (GParser_state.loadDictionaryEnabled)
    {
      *(p_dic + GParser_state.sectionCounter - 1) =
          GParser_loadDictionary(&GParser_state);

      GParser_clearBuffers(&GParser_state);

      GParser_state.loadDictionaryEnabled = GCONST_FALSE;
    }
  }

  return GCONST_TRUE;
}
