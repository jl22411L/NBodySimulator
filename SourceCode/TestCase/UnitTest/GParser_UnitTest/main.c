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

int main()
{
  GParser_State      GParser_state;
  GParserTest_Params GParserTest_params;
  dictionary       **p_dic;

  printf("-1");

  GZero(&GParser_state, GParser_State);
  GZero(&GParserTest_params, GParserTest_Params);

  printf("0");

  /* Loading Dictionary */
  if ((p_dic = GParser_loadParams(&GParser_state, "Parameters/test.ini")) ==
      NULL)
  {
    GError("Parameters did not open corrcetly");
  }

  printf("1");

  /* Loading params struct */
  GParser_loadDouble(
      &GParser_state,
      p_dic,
      &GParserTest_params.doubleNumber,
      "owner:double");

  printf("2");

  GParser_loadFloat(
      &GParser_state,
      p_dic,
      &GParserTest_params.floatingNumber,
      "owner:float");

  printf("3");

  GParser_loadInt(
      &GParser_state,
      p_dic,
      &GParserTest_params.integer,
      "owner:integer");

  printf("4");

  GParser_loadIntArray(
      &GParser_state,
      p_dic,
      &GParserTest_params.dcm[0][0],
      "Test:dcm",
      3,
      3);

  printf("5");

  GParser_loadFloatArray(
      &GParser_state,
      p_dic,
      &GParserTest_params.dcm2[0][0],
      "Test:dcm2",
      3,
      3);

  printf("6");

  GParser_loadIntArray(
      &GParser_state,
      p_dic,
      &GParserTest_params.row[0],
      "Test:row",
      3,
      1);

  printf("7");

  GParser_loadInt8(
      &GParser_state,
      p_dic,
      &GParserTest_params.integer_8,
      "owner:integer");

  printf("8");

  GParser_loadString(
      &GParser_state,
      p_dic,
      &GParserTest_params.name,
      "owner:name");

  printf("9");

  GParser_loadUInt(
      &GParser_state,
      p_dic,
      &GParserTest_params.unsignedInt,
      "Test:int8");

  return GCONST_EXIT_SUCCESS;
}