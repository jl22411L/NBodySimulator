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
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_waitingValue(GParser_State *p_GParser_state, const char cursor)
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
    GError("No value inputted before new line");
    break;
  case ('#'):
    GError("No value inputted before #");
    break;
  case (';'):
    GError("No value inputted before ;");
    break;
  case ('\"'):
    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_LOADING_STRING_VALUE;
    break;
  default:
    /* Load value buffer with cursor */
    *(p_GParser_state->valueBuffer + p_GParser_state->valueArrayIndex) = cursor;

    /* Incriment value index */
    p_GParser_state->valueArrayIndex++;

    /* Incriment value size */
    p_GParser_state->valueSize[p_GParser_state->sizeArrayIndex]++;

    /* Update state */
    p_GParser_state->loadParamsState = GPARSER_STATE_LOADING_VALUE;
    break;
  }

  return GCONST_TRUE;
}
