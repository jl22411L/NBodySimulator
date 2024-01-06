/*
 *    @File:         GParser_loadingStringValue.c
 *
 *    @ Brief:       This loads the value buffer of the params struct
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
int GParser_loadingStringValue(GParser_State *p_GParser_state, uint8_t *p_state, const char cursor)
{
  switch (cursor)
  {
  case ('\n'):
    GError("Can't have a newline before string is closed with \"");
    break;
  case ('\"'):
    p_GParser_state->sizeIndex++;
    *p_state = GPARSER_STATE_WAITING_NEWLINE;
    break;
  default:
    *(p_GParser_state->valueBuffer + p_GParser_state->valueIndex) = cursor;
    p_GParser_state->valueIndex++;
    p_GParser_state->valueSize[p_GParser_state->sizeIndex]++;
    break;
  }

  return GCONST_TRUE;
}