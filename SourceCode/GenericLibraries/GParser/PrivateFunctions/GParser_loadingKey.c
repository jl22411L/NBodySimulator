/*
 *    @File:         GParser_loadingKey.c
 *
 *    @ Brief:       This loads the key buffer in params struct
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
int GParser_loadingKey(GParser_State *p_GParser_state, const char cursor)
{
  switch (cursor)
  {
  case (' '):
    /* Update state */
    p_GParser_state->loadParamsState = GPARSER_STATE_KEY_WAITING_FOR_EQUALS;
    break;
  case ('='):
    /* Update state */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_VALUE;
    break;
  case ('\t'):
    /* Update state */
    p_GParser_state->loadParamsState = GPARSER_STATE_KEY_WAITING_FOR_EQUALS;
    break;
  case ('\n'):
    GError("Value not inputted into key");
    break;
  default:
    /* Load key buffer with cursor */
    p_GParser_state->keyBuffer[p_GParser_state->keyArrayIndex] = cursor;

    /* Incriment key index */
    p_GParser_state->keyArrayIndex++;

    /* Check to make sure the buffer has not been filled to max */
    if (p_GParser_state->keyArrayIndex > GPARSER_KEY_BUFFERSIZE)
    {
      GError("Key Buffer has reached max capacity for section %s. \n[KeyBuffer "
             "= %s]",
             p_GParser_state->sectionBuffer,
             p_GParser_state->keyBuffer);
    }

    /* Incriment key size */
    p_GParser_state->keySize[p_GParser_state->sizeArrayIndex]++;

    break;
  }

  return GCONST_TRUE;
}
