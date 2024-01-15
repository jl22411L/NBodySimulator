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
  GParserTest_Params GParserTest_params;
  GParser_State      GParser_state;
  dictionary       **p_dic;

  GZero(&GParserTest_params, GParserTest_Params);
  GZero(&GParser_state, GParser_State);

  /* Loading Dictionary */
  if ((p_dic = GParser_loadParams(&GParser_state, "Parameters/test.ini")) ==
      NULL)
  {
    GError("Parameters did not open corrcetly");
  }

  printf("lllll");

  /* Loading params struct */
  GParser_loadDouble(
      &GParser_state,
      p_dic,
      &GParserTest_params.doubleNumber,
      "owner:double");
  GParser_loadFloat(
      &GParser_state,
      p_dic,
      &GParserTest_params.floatingNumber,
      "owner:float");
  GParser_loadInt(
      &GParser_state,
      p_dic,
      &GParserTest_params.integer,
      "owner:integer");
  GParser_loadIntArray(
      &GParser_state,
      p_dic,
      &GParserTest_params.dcm[0][0],
      "Test:dcm",
      3,
      3);
  GParser_loadFloatArray(
      &GParser_state,
      p_dic,
      &GParserTest_params.dcm2[0][0],
      "Test:dcm2",
      3,
      3);
  GParser_loadIntArray(
      &GParser_state,
      p_dic,
      &GParserTest_params.row[0],
      "Test:row",
      3,
      1);
  GParser_loadInt_8(
      &GParser_state,
      p_dic,
      &GParserTest_params.integer_8,
      "owner:integer");
  GParser_loadString(
      &GParser_state,
      p_dic,
      &GParserTest_params.organisation,
      "owner:organization");
  GParser_loadString(
      &GParser_state,
      p_dic,
      &GParserTest_params.name,
      "owner:name");
  GParser_loadUInt(
      &GParser_state,
      p_dic,
      &GParserTest_params.unsignedInt,
      "Test:int8");

  printf("%d \n", GParserTest_params.integer);
  printf("%f \n", GParserTest_params.floatingNumber);
  printf("%lf \n", GParserTest_params.doubleNumber);

  GParser_closeParams(&GParser_state, p_dic);

  return GCONST_EXIT_SUCCESS;
}