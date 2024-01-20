/*
 *   @File:         GParser_loadParams
 *
 *   @ Brief:       Loads Params from ini file into a dictionary
 *
 *   @ Date:        20/12/2023
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

/*
 *  Refer to respective header file for function description
 */
dictionary **
    GParser_loadParams(GParser_State *p_GParser_state, const char *filePath)
{
  /* Defining Local Variables */
  dictionary **p_dic;
  FILE        *file;
  char         cursor;

  /* Clearing Data values */
  GZero(p_GParser_state, GParser_State);
  p_dic = NULL;

  /* Opening file */
  file = fopen(filePath, "r");

  /* Check to make sure that the file was opened corectly */
  if (file == NULL)
  {
    GError("No file was able to open");
  }

  /* Finding number of Sections */
  GParser_findNumberOfSections(file, &p_GParser_state->maxNumberSection);

  /* Assigning Memory to Dictionary */
  p_dic = (dictionary **)calloc(
      p_GParser_state->maxNumberSection,
      sizeof(dictionary *));

  /* Set the initial state */
  p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_FOR_COMMAND;

  /* Run through file */
  while (!(p_GParser_state->loadParamsState == GPARSER_STATE_FINISHED))
  {
    /* Get next cursor*/
    cursor = fgetc(file);

    if (cursor == EOF)
    {
      /* Update state to finidh reading */
      p_GParser_state->loadParamsState = GPARSER_STATE_FINISHED;

      /* Set flag to load dictionary */
      p_GParser_state->loadDictionaryEnabled = GCONST_TRUE;
    }

    /* Check the state */
    switch (p_GParser_state->loadParamsState)
    {
    /* Waiting for next commamnd */
    case (GPARSER_STATE_WAITING_FOR_COMMAND):
      GParser_waitingForCommand(p_GParser_state, cursor);
      break;
    /* Waiting for a new line */
    case (GPARSER_STATE_WAITING_NEWLINE):
      GParser_waitingForNewLine(p_GParser_state, cursor);
      break;
    /* Parsing a comment section */
    case (GPARSER_STATE_COMMENT):
      GParser_comment(p_GParser_state, cursor);
      break;
    /* Loading a section */
    case (GPARSER_STATE_LOADING_SECTION):
      GParser_loadingSection(p_GParser_state, cursor);
      break;
    /* Loading key into buffer */
    case (GPARSER_STATE_LOADING_KEY):
      GParser_loadingKey(p_GParser_state, cursor);
      break;
    /* Waiting for equals after the key */
    case (GPARSER_STATE_KEY_WAITING_FOR_EQUALS):
      GParser_waitingEquals(p_GParser_state, cursor);
      break;
    /* Waiting for value to be loaded */
    case (GPARSER_STATE_WAITING_VALUE):
      GParser_waitingValue(p_GParser_state, cursor);
      break;
    /* Loading value into buffers */
    case (GPARSER_STATE_LOADING_VALUE):
      GParser_loadingValue(p_GParser_state, cursor);
      break;
    /* Loading a string value into buffers */
    case (GPARSER_STATE_LOADING_STRING_VALUE):
      GParser_loadingStringValue(p_GParser_state, cursor);
      break;
    }

    /* If flag enabled, load section into dictionary */
    if (p_GParser_state->loadDictionaryEnabled)
    {
      *(p_dic + p_GParser_state->sectionCounter - 1) =
          GParser_loadDictionary(p_GParser_state);

      /* Clear buffers */
      GParser_clearBuffers(p_GParser_state);

      /* Reset flag */
      p_GParser_state->loadDictionaryEnabled = GCONST_FALSE;
    }
  }

  /* Output dictionary */
  return p_dic;
}
