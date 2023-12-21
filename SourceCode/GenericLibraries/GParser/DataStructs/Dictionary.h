/*
 *   @File:         Dictionary.h
 *
 *   @ Brief:       Contains Structure of Dictionary
 *
 */

#ifndef H_GPARSER_DICTIONARY_H
#define H_GPARSER_DICTIONARY_H

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
  int   *size;
} dictionary;

#endif /* H_GPARSER_DICTIONARY_H */
