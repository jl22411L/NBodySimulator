/*
 *    @File:         GParser_loadingKey.c
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

int GParser_loadingKey(
    uint8_t       *p_state,
    GParser_State *p_stateStruct,
    const char     cursor)
{
  switch (cursor)
  {
  case (' '):
    *p_state = GPARSER_STATE_KEY_WAITING_FOR_EQUALS;
    break;
  case ('\t'):
    *p_state = GPARSER_STATE_KEY_WAITING_FOR_EQUALS;
    break;
  case ('\n'):
    GError("Value not inputted into key");
    break;
  default:
    *(p_stateStruct->keyBuffer + p_stateStruct->keyIndex) = cursor;
    p_stateStruct->keyIndex++;
    p_stateStruct->keySize[p_stateStruct->sizeIndex]++;
    break;
  }

  return GCONST_TRUE;
}