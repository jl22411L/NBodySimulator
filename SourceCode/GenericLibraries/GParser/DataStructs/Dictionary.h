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

/* Structure Include */

/* Data include */

/* Generic Libraries */

/* ------------------------------ STRUCTURES ------------------------------- */

typedef struct dictionaryStruct
{
  char  *section;
  char **key;
  char **value;
  int    nKeys;
} dictionary;

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_DICTIONARY_H */
