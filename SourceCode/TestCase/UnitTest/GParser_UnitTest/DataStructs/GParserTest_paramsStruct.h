/*
 *    @File:         GParser_paramsStruct.c
 *
 *    @ Brief:       Containts definition of parameters struct
 *
 *    @ Date:        23/12/2023
 *
 */

#ifndef H_GPARSER_UNITTEST_PARAMSSTRUCT_H
#define H_GPARSER_UNITTEST_PARAMSSTRUCT_H

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct GParserTest_ParamsStruct
{
  char *name;

  char *organisation;

  int integer;

  float floatingNumber;

  double doubleNumber;

} GParserTest_Params;

#endif /* H_GPARSER_UNITTEST_PARAMSSTRUCT_H */
