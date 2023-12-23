/*
 *   @File:         GParser_StateStruct.h
 *
 *   @ Brief:       State Struct for GParser
 *
 */

#ifndef H_GPARSER_STATESTRUCT_H
#define H_GPARSER_STATESTRUCT_H

#include <stdint.h>

/* Function Includes */

/* Structure Include */

/* Data include */

/* Generic Libraries */

/* ------------------------------ STRUCTURES ------------------------------- */

typedef struct GParser_stateStruct
{
  /* Buffers */
  char sectionBuffer[1024];
  char keyBuffer[1024];
  char valueBuffer[1024];

  /* Index's */
  uint8_t sectionIndex;
  uint8_t keyIndex;
  uint8_t valueIndex;

  uint8_t sizeIndex;

  /* Sizes */
  int sectionSize;
  int keySize[256];
  int valueSize[256];

  /* Counters */
  uint8_t sectionCounter;

  /* Number of Sections */
  uint8_t maxNumberSection;

  /* Flags */
  uint8_t loadDictionaryEnabled;

} GParser_State;

GParser_State GParser_state;

#endif /* H_GPARSER_STATESTRUCT_H */
