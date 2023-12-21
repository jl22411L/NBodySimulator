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

// TODO: add error cases for !£$%^&*()-+=?/\<>etc...
int GParser_comment(
    uint8_t       *p_state,
    GParser_State *p_stateStruct,
    const char     cursor)
{
  switch (cursor)
  {
  case ('\n'):
    *p_state = GPARSER_STATE_WAITING_FOR_COMMAND;
    break;
  default:
    break;
  }

  return GCONST_TRUE;
}