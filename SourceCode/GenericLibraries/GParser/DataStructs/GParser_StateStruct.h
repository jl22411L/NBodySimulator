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

/* Structure Include */

/* Data include */
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */

/* ------------------------------ STRUCTURES ------------------------------- */

typedef struct GParser_stateStruct
{
  /* Buffers used for loading data */
  char sectionBuffer[2048];
  char keyBuffer[2048];
  char valueBuffer[2048];

  /* Variables to keep track of index's for array's */
  uint32_t sectionIndex;
  uint32_t keyIndex;
  uint32_t valueIndex;
  uint16_t sizeIndex;

  /* Variables to keep track of sizes */
  int sectionSize;
  int keySize[256];
  int valueSize[256];

  /* Variable to keep track of Sections */
  uint8_t sectionCounter;

  /* Variable to keep track of the total Number of Sections */
  uint8_t maxNumberSection;

  /* Flags */
  uint8_t loadDictionaryEnabled;
  uint8_t indexLoaded;
  uint8_t array2D;

  /* State Variable */
  uint8_t loadParamsState;

} GParser_State;

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_STATESTRUCT_H */
