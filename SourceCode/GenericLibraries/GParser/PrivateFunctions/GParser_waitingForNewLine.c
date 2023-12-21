/*
 *    @File:         GParser_waitingForNewLine.c
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

int GParser_waitingForNewLine(
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
    *p_state = GPARSER_STATE_WAITING_FOR_COMMAND;
    break;
  case ('#'):
    *p_state = GPARSER_STATE_COMMENT;
    break;
  case (';'):
    *p_state = GPARSER_STATE_COMMENT;
    break;
  default:
    GError("Invalid expression");
  }

  return GCONST_TRUE;
}
