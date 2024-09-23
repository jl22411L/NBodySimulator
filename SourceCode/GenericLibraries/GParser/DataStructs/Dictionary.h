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
  /*!
   * @brief     Buffer which contains the name of the section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char section[GCONST_BUFFER_32];

  /*!
   * @brief     Array of strings which contain the key names for a section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char key[GCONST_BUFFER_128][GCONST_BUFFER_64];

  /*!
   * @brief     Array of strings which contain the value names for a section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char value[GCONST_BUFFER_128][GCONST_BUFFER_64];

  /*!
   * @brief     Integer which contains the number of keys within a section
   *
   * @frame     N/A
   * @unit      N/A
   */
  int nKeys;

} dictionary;

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_DICTIONARY_H */
