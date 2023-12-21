/*
 *    @File:         GParser_waitingValue.c
 *
 *    @ Brief:       //TODO
 *
 *    @ Date:        20/12/2023
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstandDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int GParser_waitingValue(
    uint8_t       *p_state,
    GParser_State *p_stateStruct,
    const char     cursor)
{
  switch (cursor)
  {
  case (' '):
    break;
  case ('\t'):
    break;
  case ('\n'):
    GError("No value inputted before new line");
    break;
  case ('#'):
    GError("No value inputted before #");
    break;
  case (';'):
    GError("No value inputted before ;");
    break;
  case ('\"'):
    *p_state = GPARSER_STATE_LOADING_STRING_VALUE;
    break;
  default:
    *(p_stateStruct->valueBuffer + p_stateStruct->valueIndex) = cursor;
    p_stateStruct->valueIndex++;
    p_stateStruct->valueSize[p_stateStruct->sizeIndex]++;
    *p_state = GPARSER_STATE_LOADING_VALUE;
    break;
  }

  return GCONST_TRUE;
}