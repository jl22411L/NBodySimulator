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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

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

  int dcm[3][3];

  float dcm2[3][3];

  int row[3];

  unsigned int unsignedInt;

  int8_t integer_8;

} GParserTest_Params;

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_UNITTEST_PARAMSSTRUCT_H */
