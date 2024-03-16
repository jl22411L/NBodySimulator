/*
 *   @File:         Dictionary.h
 *
 *   @ Brief:       Contains Structure of Dictionary
 *
 */

#ifndef H_GPARSER_DICTIONARY_H
#define H_GPARSER_DICTIONARY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

/* ------------------------------ STRUCTURES ------------------------------- */

typedef struct dictionaryStruct
{
  char *section;
  char  key[GCONST_BUFFER_128][GCONST_BUFFER_64];
  char  value[GCONST_BUFFER_128][GCONST_BUFFER_64];
  int   nKeys;
} dictionary;

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_DICTIONARY_H */
