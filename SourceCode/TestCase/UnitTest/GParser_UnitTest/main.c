/*
 *   @File:         main.c
 *
 *   @ Brief:       Unit test of GParser Library
 *
 *   @ Description:
 *
 */

/* Function Includes */
#include "GParser/PublicFunctions/GParser_PublicFunctions.h"

/* Structure Include */
#include "GParser_UnitTest/DataStructs/GParserTest_paramsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int main(void)
{
  /* Defining Local Variables */
  dictionary  **p_dic;
  GParser_State GParser_state;

  /* Zero local variables */
  GZero(&GParser_state, GParser_State);

  /* Load Params into dictionary */
  p_dic = GParser_loadParams(&GParser_state, "Parameters/test.ini");

  return GCONST_EXIT_SUCCESS;
}