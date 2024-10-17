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
#include "GParser/ConstantDefs/GParser_Const.h"

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
  char section[GPARSER_SECTION_BUFFERSIZE];

  /*!
   * @brief     Array of strings which contain the key names for a section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char key[GPARSER_DICTIONARY_MAX_KEY_VALUE_PAIRS_NUMBER]
          [GPARSER_DICTIONARY_MAX_KEY_LENGTH];

  /*!
   * @brief     Array of strings which contain the value names for a section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char value[GPARSER_DICTIONARY_MAX_KEY_VALUE_PAIRS_NUMBER]
            [GPARSER_DICTIONARY_MAX_VALUE_LENGTH];

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
