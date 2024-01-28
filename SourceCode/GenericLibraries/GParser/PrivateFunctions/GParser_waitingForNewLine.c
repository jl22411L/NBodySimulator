/*
 *    @File:         GParser_waitingForNewLine.c
 *
 *    @ Brief:       Waits for a new line when parsing
 *
 *    @ Date:        20/12/2023
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_waitingForNewLine(GParser_State *p_GParser_state, const char cursor)
{
  switch (cursor)
  {
  case (' '):
    /* DO NOTHING */
    break;
  case ('\t'):
    /* DO NOTHING */
    break;
  case ('\n'):
    /* Update the state */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_FOR_COMMAND;
    break;
  case ('#'):
    /* Update the state */
    p_GParser_state->loadParamsState = GPARSER_STATE_COMMENT;
    break;
  case (';'):
    /* Update the state */
    p_GParser_state->loadParamsState = GPARSER_STATE_COMMENT;
    break;
  default:
    GError("Invalid expression");
  }

  return GCONST_TRUE;
}
