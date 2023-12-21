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
#include "GParser/ConstandDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

// TODO: add error cases for !£$%^&*()-+=?/\<>etc...
int GParser_waitingForCommand(
    uint8_t       *p_state,
    GParser_State *p_stateStruct,
    const char     cursor)
{
  switch (cursor)
  {
  case ('\t'):
    break;
  case (' '):
    break;
  case ('\n'):
    break;
  case ('['):
    switch (p_stateStruct->sectionCounter)
    {
    case (0):
      break;
    default:
      p_stateStruct->loadDictionaryEnabled = GCONST_TRUE;
    }
    *p_state = GPARSER_STATE_LOADING_SECTION;
    break;
  case ('#'):
    *p_state = GPARSER_STATE_COMMENT;
    break;
  case (';'):
    *p_state = GPARSER_STATE_COMMENT;
    break;
  case (EOF):
    *p_state = GPARSER_STATE_FINISHED;
    break;
  default:
    switch (p_stateStruct->sectionCounter)
    {
    case (0):
      GError("Can't have a key with no section");
      break;
    default:
      *p_state = GPARSER_STATE_LOADING_KEY;
      *(p_stateStruct->keyBuffer + p_stateStruct->keyIndex) = cursor;
      p_stateStruct->keyIndex++;
      p_stateStruct->keySize[p_stateStruct->sizeIndex]++;
      break;
    }
  }

  return GCONST_TRUE;
}
