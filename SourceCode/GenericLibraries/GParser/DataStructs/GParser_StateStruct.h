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

typedef struct GParser_stateStruct
{
  // TODO: GIve each member a doxygen comment description

  /* Buffers used for loading data */
  char sectionBuffer[GPARSER_SECTION_BUFFERSIZE];
  char keyBuffer[GPARSER_KEY_BUFFERSIZE];
  char valueBuffer[GPARSER_VALUE_BUFFERSIZE];

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
