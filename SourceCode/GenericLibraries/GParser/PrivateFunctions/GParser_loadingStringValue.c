/*
 *    @File:         GParser_loadingStringValue.c
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

int GParser_loadingStringValue(
    uint8_t       *p_state,
    GParser_State *p_stateStruct,
    const char     cursor)
{
  switch (cursor)
  {
  case ('\n'):
    GError("Can't have a newline before string is closed with \"");
    break;
  case ('\"'):
    p_stateStruct->sizeIndex++;
    *p_state = GPARSER_STATE_WAITING_NEWLINE;
    break;
  default:
    *(p_stateStruct->valueBuffer + p_stateStruct->valueIndex) = cursor;
    p_stateStruct->valueIndex++;
    p_stateStruct->valueSize[p_stateStruct->sizeIndex]++;
    break;
  }

  return GCONST_TRUE;
}