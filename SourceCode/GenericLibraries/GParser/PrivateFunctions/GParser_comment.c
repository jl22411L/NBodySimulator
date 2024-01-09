/*
 *   @File:         GParser_comment.c
 *
 *   @ Brief:       Function to determine how to change state depending on
 *                  cursor input
 *
 */

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

/*
 *  Refer to respective header file for function description
 */
int GParser_comment(GParser_State *p_GParser_state, const char cursor_in)
{
  switch (cursor_in)
  {
  case ('\n'):
    /* Updating the state */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_FOR_COMMAND;
    break;
  default:
    /* DO NOTHING */
    break;
  }

  return GCONST_TRUE;
}