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
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

/*
 *  Refer to respective header file for function description
 */
dictionary *
    GParser_loadParams(GParser_State *p_GParser_state, const char *filePath)
{
  /* Defining Local Variables */
  dictionary *p_dic;
  FILE       *file;
  char        cursor;

  /* Clearing Data values */
  GZero(p_GParser_state, GParser_State);
  p_dic = NULL;

  /* Opening file */
  file = fopen(filePath, "r");

  /* Check to make sure that the file was opened corectly */
  if (file == NULL)
  {
    GError("No file was able to open, filePath = %s", filePath);
  }

  /* Finding number of Sections */
  GParser_findNumberOfSections(file, &p_GParser_state->maxNumberSection);

  /* Assigning Memory to Dictionary */
  p_dic = (dictionary *)calloc(
      p_GParser_state->maxNumberSection,
      sizeof(dictionary));

  /* Set the initial state */
  p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_FOR_COMMAND;

  /* Run through file */
  while (!(p_GParser_state->loadParamsState == GPARSER_STATE_FINISHED))
  {
    /* Get next cursor*/
    cursor = fgetc(file);

    if (cursor == EOF)
    {
      /* Check to see if file ends on a key, incriment size index */
      switch (p_GParser_state->loadParamsState)
      {
      case (GPARSER_STATE_LOADING_VALUE):
        p_GParser_state->sizeIndex++;
        break;
      case (GPARSER_STATE_LOADING_STRING_VALUE):
        p_GParser_state->sizeIndex++;
        break;
      }
      /* Update state to finish reading */
      p_GParser_state->loadParamsState = GPARSER_STATE_FINISHED;

      /* Set flag to load dictionary */
      p_GParser_state->loadDictionaryEnabled = GCONST_TRUE;
    }

    /* Check the state */
    switch (p_GParser_state->loadParamsState)
    {
    case (GPARSER_STATE_WAITING_FOR_COMMAND):
      /* Waiting for next commamnd */
      GParser_waitingForCommand(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_WAITING_NEWLINE):
      /* Waiting for a new line */
      GParser_waitingForNewLine(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_COMMENT):
      /* Parsing a comment section */
      GParser_comment(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_SECTION):
      /* Loading a section */
      GParser_loadingSection(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_KEY):
      /* Loading key into buffer */
      GParser_loadingKey(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_KEY_WAITING_FOR_EQUALS):
      /* Waiting for equals after the key */
      GParser_waitingEquals(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_WAITING_VALUE):
      /* Waiting for value to be loaded */
      GParser_waitingValue(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_VALUE):
      /* Loading value into buffers */
      GParser_loadingValue(p_GParser_state, cursor);
      break;
    case (GPARSER_STATE_LOADING_STRING_VALUE):
      /* Loading a string value into buffers */
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

  /* Clost the file */
  fclose(file);

  /* Output dictionary */
  return p_dic;
}
