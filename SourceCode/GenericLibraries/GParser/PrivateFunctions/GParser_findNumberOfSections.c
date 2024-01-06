/*
 *    @File:         GParser_findNumberOfSections.c
 *
 *    @ Brief:       Finds the number of sections within a file
 *
 *    @ Date:        19/12/2023
 *
 */

#include <stdio.h>

/* Function Includes */
#include "GParser/PrivateFunctions/GParser_PrivateFunctions.h"

/* Structure Include */
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstandDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int GParser_findNumberOfSections(FILE *file, uint8_t *p_maxNumberSection_out)
{
  char    cursor;
  char    cursor_prev;
  uint8_t sectionCounter;
  uint8_t sectionCounterEnabled;
  uint8_t state;

  cursor_prev           = '\0';
  sectionCounter        = 0;
  sectionCounterEnabled = GCONST_FALSE;
  state                 = GPARSER_STATE_WAITING_FOR_COMMAND;
  while ((cursor = fgetc(file)) != EOF)
  {
    // switch (cursor)
    // {
    // case ('['):
    //   switch (cursor_prev)
    //   {
    //   case (' '):
    //     sectionCounterEnabled = GCONST_TRUE;
    //     break;
    //   case ('\n'):
    //     sectionCounterEnabled = GCONST_TRUE;
    //     break;
    //   }
    //   break;
    // }

    switch (state)
    {
    case (GPARSER_STATE_WAITING_FOR_COMMAND):
      switch (cursor)
      {
      case ('['):
        switch (cursor_prev)
        {
        case (' '):
          sectionCounterEnabled = GCONST_TRUE;
          break;
        case ('\n'):
          sectionCounterEnabled = GCONST_TRUE;
          break;
        }
        break;
      case (';'):
        state = GPARSER_STATE_WAITING_NEWLINE;
        break;
      case ('#'):
        state = GPARSER_STATE_WAITING_NEWLINE;
        break;
      }
    case (GPARSER_STATE_WAITING_NEWLINE):
      switch (cursor)
      {
      case ('\n'):
        state = GPARSER_STATE_WAITING_FOR_COMMAND;
        break;
      }
    }

    switch (sectionCounterEnabled)
    {
    case (GCONST_TRUE):
      sectionCounter++;
      sectionCounterEnabled = GCONST_FALSE;
      break;
    }

    cursor_prev = cursor;
  }

  rewind(file);

  *p_maxNumberSection_out = sectionCounter;

  return GCONST_TRUE;
}
