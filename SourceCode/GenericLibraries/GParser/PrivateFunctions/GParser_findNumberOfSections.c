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
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_findNumberOfSections(FILE *file, uint8_t *p_maxNumberSection_out)
{
  /* Defining Local Variables */
  char    cursor;
  char    cursor_prev;
  uint8_t sectionCounter;
  uint8_t sectionCounterEnabled;
  uint8_t state;

  /* Declaring Local Variables */
  cursor_prev           = '\0';
  sectionCounter        = 0;
  sectionCounterEnabled = GCONST_FALSE;
  state                 = GPARSER_STATE_WAITING_FOR_COMMAND;

  /* Run through file */
  while ((cursor = fgetc(file)) != EOF)
  {
    switch (state)
    {
    case (GPARSER_STATE_WAITING_FOR_COMMAND):
      switch (cursor)
      {
      case ('['):
        /* If previous cursor is a space or a new line, section is assumed */
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
      /* Ignores [ in comments */
      case (';'):
        state = GPARSER_STATE_COMMENT;
        break;
      case ('#'):
        state = GPARSER_STATE_COMMENT;
        break;
      }
    case (GPARSER_STATE_COMMENT):
      switch (cursor)
      {
      case ('\n'):
        /* Update State */
        state = GPARSER_STATE_WAITING_FOR_COMMAND;
        break;
      }
    }

    /* Add to section counter if section is to be counted */
    switch (sectionCounterEnabled)
    {
    case (GCONST_TRUE):
      sectionCounter++;
      sectionCounterEnabled = GCONST_FALSE;
      break;
    }

    /* Incriment cursor */
    cursor_prev = cursor;
  }

  /* Set file back to beginning */
  rewind(file);

  /* Output max number of sections */
  *p_maxNumberSection_out = sectionCounter;

  return GCONST_TRUE;
}
