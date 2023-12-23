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

int main()
{
  GParserTest_Params GParserTest_params;
  dictionary       **p_dic;

  /* Loading Dictionary */
  if ((p_dic = GParser_loadParams("Parameters/test.ini")) == NULL)
  {
    GError("Parameters did not open corrcetly");
  }

  /* Loading params struct */
  GParser_loadString(&GParserTest_params.name, "owner:name", p_dic);
  GParser_loadInt(&GParserTest_params.integer, "owner:integer", p_dic);
  GParser_loadFloat(&GParserTest_params.floatingNumber, "owner:float", p_dic);
  GParser_loadDouble(&GParserTest_params.doubleNumber, "owner:double", p_dic);

  printf("%d \n", GParserTest_params.integer);
  printf("%f \n", GParserTest_params.floatingNumber);
  printf("%lf \n", GParserTest_params.doubleNumber);

  return GCONST_EXIT_SUCCESS;
}