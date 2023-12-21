/*
 *    @File:         GParser_loadingSection.c
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

int GParser_loadingSection(
    uint8_t       *p_state,
    GParser_State *p_stateStruct,
    const char     cursor)
{
  switch (cursor)
  {
  case (' '):
    GError("Can't have an error in section name");
    break;
  case ('\t'):
    GError("Can't have a tab in section name");
    break;
  case ('\n'):
    GError("Section not finished before new line");
    break;
  case ('#'):
    GError("Can't have # in section name");
    break;
  case (';'):
    GError("Can't have ; in section name");
    break;
  case (']'):
    p_stateStruct->sectionCounter++;
    *p_state = GPARSER_STATE_WAITING_NEWLINE;
    break;
  default:
    *(p_stateStruct->sectionBuffer + p_stateStruct->sectionIndex) = cursor;
    p_stateStruct->sectionIndex++;
    p_stateStruct->sectionSize++;
  }

  return GCONST_TRUE;
}
