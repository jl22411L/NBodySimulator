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
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_loadingStringValue(
    GParser_State *p_GParser_state,
    const char     cursor)
{
  switch (cursor)
  {
  case ('\n'):
    GError("Can't have a newline before string is closed with \"");
    break;
  case ('\"'):
    /* Incriment size index (Need to incriment for for loop) */
    p_GParser_state->sizeIndex++;

    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_NEWLINE;
    break;
  default:
    /* Load value buffer with cursor */
    *(p_GParser_state->valueBuffer + p_GParser_state->valueIndex) = cursor;

    /* Icnriment value index */
    p_GParser_state->valueIndex++;

    /* Incriment size buffer */
    p_GParser_state->valueSize[p_GParser_state->sizeIndex]++;
    break;
  }

  return GCONST_TRUE;
}