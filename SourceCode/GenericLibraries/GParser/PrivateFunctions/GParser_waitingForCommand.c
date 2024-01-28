/*
 *   @File:         GParser_waitingForCommand.c
 *
 *   @ Brief:       Function to determine how to change state depending on
 *                  cursor input
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Function Includes */
#include "GParser/PrivateFunctions/GParser_PrivateFunctions.h"

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

// TODO: add error cases for !£$%^&*()-+=?/\<>etc...
/*
 *  Refer to respective header file for function description
 */
int GParser_waitingForCommand(GParser_State *p_GParser_state, const char cursor)
{
  switch (cursor)
  {
  case ('\t'):
    /* DO NOTHING */
    break;
  case (' '):
    /* DO NOTHING */
    break;
  case ('\n'):
    /* DO NOTHING */
    break;
  case ('['):
    /* Check to see if dictionary should be loaded */
    switch (p_GParser_state->sectionCounter)
    {
    case (GCONST_FALSE):
      /* DO NOTHING */
      break;
    default:
      /* set load dictionary flag to True */
      p_GParser_state->loadDictionaryEnabled = GCONST_TRUE;
    }

    /* Updating State */
    p_GParser_state->loadParamsState = GPARSER_STATE_LOADING_SECTION;
    break;
  case ('#'):
    /* Updating State */
    p_GParser_state->loadParamsState = GPARSER_STATE_COMMENT;
    break;
  case (';'):
    /* Updating State */
    p_GParser_state->loadParamsState = GPARSER_STATE_COMMENT;
    break;
  case (EOF):
    /* Updating State */
    p_GParser_state->loadParamsState = GPARSER_STATE_FINISHED;
    break;
  default:
    /* Cursor must be representing key, check to make sure there is a section */
    switch (p_GParser_state->sectionCounter)
    {
      /* If no section has been loaded throw an error */
    case (GCONST_FALSE):
      GError("Can't have a key with no section");
      break;
    default:
      /* Setting the State */
      p_GParser_state->loadParamsState = GPARSER_STATE_LOADING_KEY;

      /* Loading the key with the cursor */
      *(p_GParser_state->keyBuffer + p_GParser_state->keyIndex) = cursor;

      /* Incrimenting the key index */
      p_GParser_state->keyIndex++;

      /* Incrimenting the key size*/
      p_GParser_state->keySize[p_GParser_state->sizeIndex]++;
      break;
    }
  }

  return GCONST_TRUE;
}
