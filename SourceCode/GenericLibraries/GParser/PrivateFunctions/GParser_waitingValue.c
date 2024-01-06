/*
 *    @File:         GParser_waitingValue.c
 *
 *    @ Brief:       Waiting for value to be inputted in parsing
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

/*
 *  Refer to respective header file for function description
 */
int GParser_waitingValue(GParser_State *p_GParser_state, uint8_t *p_state, const char cursor)
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
    *(p_GParser_state->valueBuffer + p_GParser_state->valueIndex) = cursor;
    p_GParser_state->valueIndex++;
    p_GParser_state->valueSize[p_GParser_state->sizeIndex]++;
    *p_state = GPARSER_STATE_LOADING_VALUE;
    break;
  }

  return GCONST_TRUE;
}