/*
 *   @File:         GParser_StateStruct.h
 *
 *   @ Brief:       State Struct for GParser
 *
 */

#ifndef H_GPARSER_STATESTRUCT_H
#define H_GPARSER_STATESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
/* None */

/* ------------------------------ STRUCTURES ------------------------------- */

typedef struct GParser_StateStruct
{
  /*!
   * @brief     Buffer which will contain the name of the section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char sectionBuffer[GPARSER_SECTION_BUFFERSIZE];

  /*!
   * @brief     Buffer which will contain the all the key names within a
   *            section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char keyBuffer[GPARSER_KEY_BUFFERSIZE];

  /*!
   * @brief     Buffer which will contain the all the values from within a
   *            section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  char valueBuffer[GPARSER_VALUE_BUFFERSIZE];

  /*!
   * @brief     Integer which keeps track of the index for filling the section
   *            buffer.
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint32_t sectionIndex;

  /*!
   * @brief     Integer which keeps track of what key within a section is
   *            currently being parsed
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint32_t keyArrayIndex;

  /*!
   * @brief     Integer which keeps track of what value within a section is
   *            currently being parsed
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint32_t valueArrayIndex;

  /*!
   * @brief     Integer which keeps track of the index used for the arrays which
   *            keep track of the size of a key or value.
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint16_t sizeArrayIndex;

  /*!
   * @brief     Integer which keeps track of the size of a section name.
   *
   * @frame     N/A
   * @unit      N/A
   */
  int sectionSize;

  /*!
   * @brief     Array which keeps track of the sizes of all the keys within a
   *            section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  int keySize[GPARSER_DICTIONARY_MAX_KEY_VALUE_PAIRS_NUMBER];

  /*!
   * @brief     Array which keeps track of the sizes of all the values within a
   *            section.
   *
   * @frame     N/A
   * @unit      N/A
   */
  int valueSize[GPARSER_DICTIONARY_MAX_KEY_VALUE_PAIRS_NUMBER];

  /*!
   * @brief     Integer which keeps track of the number of sections within the
   *            parameters file.
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint8_t sectionCounter;

  /*!
   * @brief     Integer which contains the max number of sections within a
   *            parameter file.
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint8_t maxNumberSection;

  /*!
   * @brief     Flag which indicates if a new section should be laoded into a
   *            dictionary. Information about the parameters is loaded into the
   *            GParser_state and then when flag is GCONST_TRUE, it is loaded
   *            into the dictionary.
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint8_t loadDictionaryEnabled;

  /*!
   * @brief     Integer which contains the state of the parser which is used to
   *            manage how to handle the information.
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint8_t loadParamsState;

} GParser_State;

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_STATESTRUCT_H */
