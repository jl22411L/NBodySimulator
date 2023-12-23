/*
 *    @File:         GParser_loadingValue.c
 *
 *    @ Brief:       This loads the valude buffer of a params struct
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
int GParser_loadingValue(
    uint8_t       *p_state,
    GParser_State *p_stateStruct,
    const char     cursor)
{
  switch (cursor)
  {
  case (' '):
    p_stateStruct->sizeIndex++;
    *p_state = GPARSER_STATE_WAITING_NEWLINE;
    break;
  case ('\t'):
    p_stateStruct->sizeIndex++;
    *p_state = GPARSER_STATE_WAITING_NEWLINE;
    break;
  case ('\n'):
    p_stateStruct->sizeIndex++;
    *p_state = GPARSER_STATE_WAITING_FOR_COMMAND;
    break;
  case ('#'):
    p_stateStruct->sizeIndex++;
    *p_state = GPARSER_STATE_COMMENT;
    break;
  case (';'):
    p_stateStruct->sizeIndex++;
    *p_state = GPARSER_STATE_COMMENT;
    break;
  default:
    *(p_stateStruct->valueBuffer + p_stateStruct->valueIndex) = cursor;
    p_stateStruct->valueIndex++;
    p_stateStruct->valueSize[p_stateStruct->sizeIndex]++;
    break;
  }

  return GCONST_TRUE;
}