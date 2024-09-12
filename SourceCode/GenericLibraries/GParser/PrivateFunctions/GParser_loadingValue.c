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
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_loadingValue(GParser_State *p_GParser_state, const char cursor)
{
  switch (cursor)
  {
  case (' '):
    /* Incriment size Index */
    p_GParser_state->sizeIndex++;

    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_NEWLINE;
    break;
  case ('\t'):
    /* Incriment size Index */
    p_GParser_state->sizeIndex++;

    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_NEWLINE;
    break;
  case ('\n'):
    /* Incriment size Index */
    p_GParser_state->sizeIndex++;

    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_FOR_COMMAND;
    break;
  case ('#'):
    /* Incriment size Index */
    p_GParser_state->sizeIndex++;

    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_COMMENT;
    break;
  case (';'):
    /* Incriment size Index */
    p_GParser_state->sizeIndex++;

    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_COMMENT;
    break;
  default:
    /* Load value buffer with cursor */
    *(p_GParser_state->valueBuffer + p_GParser_state->valueIndex) = cursor;

    /* Incriment value index */
    p_GParser_state->valueIndex++;

    /* Check to make sure the buffer has not been filled to max */
    if (p_GParser_state->keyIndex > GPARSER_VALUE_BUFFERSIZE)
    {
      GError(
          "Value Buffer has reached max capacity for section '%s'",
          p_GParser_state->sectionBuffer);
    }

    /* incriment value size value */
    p_GParser_state->valueSize[p_GParser_state->sizeIndex]++;
    break;
  }

  return GCONST_TRUE;
}
