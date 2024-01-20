/*
 *    @File:         GParser_waitingEquals.c
 *
 *    @ Brief:       This waits for the cursor to be equals
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
int GParser_waitingEquals(GParser_State *p_GParser_state, const char cursor)
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
    GError("No value inputted to key before new line");
    break;
  case ('='):
    /* Update State */
    p_GParser_state->loadParamsState = GPARSER_STATE_WAITING_VALUE;
    break;
  default:
    GError("Unkown Input");
    break;
  }

  return GCONST_TRUE;
}